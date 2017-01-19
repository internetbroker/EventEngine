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

	asio::io_service& GetIOService();
	asio::strand& GetStrand();

private:
	typedef std::shared_ptr<asio::io_service> IOServicePtr;
	typedef std::shared_ptr<asio::strand> StrandPtr;
	typedef std::shared_ptr<asio::io_service::work> WorkPtr;

	/// The pool of io_services.   
	IOServicePtr ioService;

	/// The pool of strand.   
	StrandPtr strand;

	/// The work that keeps the io_services running.   
	WorkPtr work;

	//thread pool of service run
	std::vector<std::shared_ptr<std::thread> > threadPool;

	//flag the io service if started
	std::atomic<bool> start_;

};

#endif

