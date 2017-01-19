#include "EventEngine/EventEngine.h"

EventEngine::EventEngine()
	:active(false)
	, handlePool(new HandlePool)
	, idCounter(1)
	, taskQueue(new moodycamel::BlockingConcurrentQueue<Task>)
	, servicePool(new IOServicePool)
{
}

EventEngine::~EventEngine()
{
	if (active)
	{
		stopEngine();
	}
}

Id EventEngine::RegisterHandler(std::string type, Handle f, bool isBlocking)
{
	Id inerID = GetID();
	HandlePool::Handler h;
	h.id = inerID;
	h.h = f;
	h.blocking = isBlocking;

	handlePool->WriteHandler(type,h);

	return inerID;
}

bool EventEngine::UnRegisterHandler(std::string type, Id regID)
{
	return handlePool->DeleteHandler(type, regID);
}

void EventEngine::Post(Task &t)
{
	taskQueue->enqueue(t);
}

bool EventEngine::startEngine()
{
	if (active)
	{
		return false;
	}

	active = true;

	servicePool->Start();

	//taskThread.reset(new std::thread(std::bind(&EventEngine::processTask, this)));
	//timerThread.reset(new std::thread(std::bind(&EventEngine::trigerTimer, this)));

	taskThread = new std::thread(std::bind(&EventEngine::processTask, this));
	timerThread = new std::thread(std::bind(&EventEngine::trigerTimer, this));

	return true;
}

bool EventEngine::stopEngine()
{
	if (!active)
	{
		return false;
	}

	active = false;

	timerThread->join();
	delete timerThread;
	timerThread = nullptr;

	if (taskQueue->size_approx())
	{
		taskThread->join();

		delete taskThread;
		taskThread = nullptr;
	}
	else
	{
		taskThread->detach();

		//delete taskThread;
		//taskThread = nullptr;
	}

	servicePool->Stop();

	return true;
}

void EventEngine::processTask()
{
	while(active)
	{
		Task t;
		taskQueue->wait_dequeue(t);

		HandlePool::Ret ret = handlePool->ReadHandler(t.type);

		for (auto it = ret.first; it != ret.second; it++)
		{
			auto f = [=] {it->second.h(t.task_data); };

			if (it->second.blocking)
			{
				asio::strand& strand_ = servicePool->GetStrand(it->second.id);
				strand_.post(f);
			}
			else
			{
				asio::io_service& ioService_ = servicePool->GetIOService(it->second.id);
				ioService_.post(f);
			}
		}
	}
}

Id EventEngine::GetID()
{
	std::lock_guard<std::mutex> lock(idMutex);
	Id id = idCounter;
	idCounter++;
	return id;
}

void EventEngine::trigerTimer()
{
	while (active)
	{
		Task task = Task();
		task.type = EVENT_TIMER;
		task.task_data = Datablk(1);
		Post(task);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//std::this_thread::sleep_for(std::chrono::microseconds(1));
		//std::this_thread::sleep_for(std::chrono::nanoseconds(1));
	}
}
