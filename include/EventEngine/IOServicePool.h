#pragma once
#ifndef __IOServicePool_H__
#define __IOServicePool_H__

#include "asio.hpp"
#include "ckdef.h"

#include <vector>
#include <memory>
#include <thread>
#include <atomic>

/*
*io service pool to manage io service\strand and keep service work
*/

class IOServicePool
{
public:
	//constructor
	IOServicePool();
	virtual ~IOServicePool();

	//start the io service
	void Start();

	//stop the io service
	void Stop();

	asio::io_service& GetIOService(ID id);
	asio::strand& GetStrand(ID id);

	asio::io_service& GetIOService();
	asio::strand& GetStrand();

private:
	typedef std::shared_ptr<asio::io_service> IOServicePtr;
	typedef std::shared_ptr<asio::strand> StrandPtr;
	typedef std::shared_ptr<asio::io_service::work> WorkPtr;

	/// The pool of io_services.   
	std::vector<IOServicePtr> mIOServicePool;

	/// The pool of strand.   
	std::vector<StrandPtr> mStrandPool;

	/// The work that keeps the io_services running.   
	std::vector<WorkPtr> mWorkPool;

	//thread pool of service run
	std::vector<std::shared_ptr<std::thread> > threadPool;

	//flag the io service if started
	std::atomic<bool> start_;

	std::size_t mServiceSize;

	std::atomic<std::size_t> mNextSerive;

};

#endif

