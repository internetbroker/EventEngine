#include "EventEngine/IOServicePool.h"

#include <functional>

IOServicePool::IOServicePool()
	:start_(false)	
	, mServiceSize(std::thread::hardware_concurrency())
	, mNextSerive(0)
{
	for (std::size_t i = 0; i < mServiceSize; i++)
	{
		IOServicePtr ioService(new asio::io_service);
		StrandPtr strand(new asio::strand(*ioService));
		WorkPtr work(new asio::io_service::work(*ioService));

		mIOServicePool.push_back(ioService);
		mStrandPool.push_back(strand);
		mWorkPool.push_back(work);
	}
}


IOServicePool::~IOServicePool()
{
	if (start_)
	{
		Stop();
	}
}

void IOServicePool::Start()
{
	if (!start_)
	{
		// Create a pool of threads to run all of the io_services.   
		for (auto item : mIOServicePool)
		{
			auto func = [=]{item->run(); };
			
			std::shared_ptr<std::thread> thread1(new std::thread(func));
			std::shared_ptr<std::thread> thread2(new std::thread(func));
			threadPool.push_back(thread1);
			threadPool.push_back(thread2);
		}
		start_ = true;
	}
}

void IOServicePool::Stop()
{
	if (start_)
	{
		// Explicitly stop all io_services.   
		for (auto item: mIOServicePool)
		{
			item->stop();
		}
		

		// Wait for all threads in the pool to exit.   
		for (auto item: threadPool)
		{
			item->join();
		}

		start_ = false;
	}
}

asio::io_service& IOServicePool::GetIOService(ID id)
{	
	mNextSerive = id%mServiceSize;
	asio::io_service& ioService = *mIOServicePool[mNextSerive];

	++mNextSerive;
	if (mNextSerive == mServiceSize)
	{
		mNextSerive = 0;
	}
		
	return ioService;
}

asio::strand& IOServicePool::GetStrand(ID id)
{		
	mNextSerive = id%mServiceSize;
	asio::strand& strand = *mStrandPool[mNextSerive];

	++mNextSerive;
	if (mNextSerive == mServiceSize)
	{
		mNextSerive = 0;
	}

	return strand;
}

asio::io_service& IOServicePool::GetIOService()
{
	asio::io_service& ioService = *mIOServicePool[mNextSerive];

	++mNextSerive;
	if (mNextSerive == mServiceSize)
	{
		mNextSerive = 0;
	}

	return ioService;
}

asio::strand& IOServicePool::GetStrand()
{
	asio::strand& strand = *mStrandPool[mNextSerive];

	++mNextSerive;
	if (mNextSerive == mServiceSize)
	{
		mNextSerive = 0;
	}

	return strand;
}
