#include "EventEngine/IOServicePool.h"

#include <functional>

IOServicePool::IOServicePool()
	:start_(false)
{
	// Give all the io_services work to do so that their run() functions will not   
	// exit until they are explicitly stopped.   
	for (std::size_t i = 0; i < std::thread::hardware_concurrency()*2; ++i)
	{
		IOServicePtr service(new asio::io_service);
		StrandPtr strand_(new asio::strand(*service));
		WorkPtr work(new asio::io_service::work(*service));

		//save above var
		ioServicePool.push_back(service);
		strandPool.push_back(strand_);
		workPool.push_back(work);
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
		for (std::size_t i = 0; i < ioServicePool.size(); ++i)
		{
			auto func = [&]{ ioServicePool[i]->run(); };
			
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
		for (std::size_t i = 0; i < ioServicePool.size(); ++i)
		{
			ioServicePool[i]->stop();
		}

		// Wait for all threads in the pool to exit.   
		for (std::size_t i = 0; i < threadPool.size(); ++i)
		{
			threadPool[i]->join();
		}

		start_ = false;
	}
}

asio::io_service& IOServicePool::GetIOService(Id id)
{
	// Use a round-robin scheme to choose the next io_service to use. 

	Id i = id%ioServicePool.size();

	asio::io_service& io_service = *ioServicePool[i];
	
	return io_service;
}

asio::strand& IOServicePool::GetStrand(Id id)
{
	// Use a round-robin scheme to choose the next strand to use.

	Id i = id%ioServicePool.size();
	asio::strand& _strand_ = *strandPool[i];
		
	return _strand_;
}
