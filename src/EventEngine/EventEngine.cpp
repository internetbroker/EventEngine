#include "EventEngine/EventEngine.h"

#include <chrono>

EventEngine::EventEngine()
	:active(false)
	, handlePool(new HandlePool)
	, idCounter(1)
	, taskQueue(new moodycamel::BlockingConcurrentQueue<Task>)
	, servicePool(new IOServicePool)
{
	mTimerHandler = [&](const asio::error_code& ec)
	{
		Task task = Task();
		task.type = EVENT_TIMER;
		task.task_data = Datablk(1);
		Post(task);
		mTimer->expires_from_now(std::chrono::seconds(1));
		mTimer->async_wait(mTimerHandler);
	};
}

EventEngine::~EventEngine()
{
	if (active)
	{
		stopEngine();
	}
}

ID EventEngine::RegisterHandler(std::string type, Handle f, bool isBlocking)
{
	ID inerID = GetID();
	HandlePool::Handler h;
	h.id = inerID;
	h.h = f;
	h.blocking = isBlocking;

	handlePool->WriteHandler(type,h);

	return inerID;
}

bool EventEngine::UnRegisterHandler(std::string type, ID regID)
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

	mTimer.reset(new asio::steady_timer(servicePool->GetIOService()));
	mTimer->expires_from_now(std::chrono::seconds(1));
	mTimer->async_wait(mTimerHandler);

	//timerThread = new std::thread(std::bind(&EventEngine::trigerTimer, this));

	return true;
}

bool EventEngine::stopEngine()
{
	if (!active)
	{
		return false;
	}

	active = false;

	mTimer->cancel();

	/*timerThread->join();
	delete timerThread;
	timerThread = nullptr;*/

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

ID EventEngine::GetID()
{
	std::lock_guard<std::mutex> lock(idMutex);
	ID id = idCounter;
	idCounter++;
	return id;
}
