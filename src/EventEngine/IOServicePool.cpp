#include "EventEngine/IOServicePool.h"

#include <functional>

IOServicePool::IOServicePool()
	:start_(false)
	, ioService(new asio::io_service)
	, strand(new asio::strand(*ioService))
	, work(new asio::io_service::work(*ioService))
{
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
		for (std::size_t i = 0; i < std::thread::hardware_concurrency() * 2; ++i)
		{
			auto func = [&]{ ioService->run(); };
			
			std::shared_ptr<std::thread> thread(new std::thread(func));
			threadPool.push_back(thread);
		}
		start_ = true;
	}
}

void IOServicePool::Stop()
{
	if (start_)
	{
		// Explicitly stop all io_services.   
		ioService->stop();

		// Wait for all threads in the pool to exit.   
		for (std::size_t i = 0; i < threadPool.size(); ++i)
		{
			threadPool[i]->join();
		}

		start_ = false;
	}
}

asio::io_service& IOServicePool::GetIOService()
{	
	return *ioService;
}

asio::strand& IOServicePool::GetStrand()
{		
	return *strand;
}
