#pragma once
#ifndef __EVENTENGINE_H__
#define __EVENTENGINE_H__

#include "ckdef.h"
#include "cktypes.h"
#include "HandlePool.h"
#include "blockingconcurrentqueue.h"
#include "IOServicePool.h"

#include <thread>
#include <atomic>
#include <memory>

class CK_EXPORTS EventEngine
{
public:
	EventEngine();
	~EventEngine();

	ID RegisterHandler(std::string type, Handle f, bool isBlocking = false);
	bool UnRegisterHandler(std::string type, ID regID);
	void Post(Task &t);

	bool startEngine();
	bool stopEngine();

	ID GetID();
private:
	void processTask();
	void trigerTimer();

private:	
	std::atomic<bool> active;

	//std::shared_ptr<std::thread> taskThread;
	std::thread* taskThread = nullptr;

	//std::shared_ptr<std::thread> timerThread;
	std::thread* timerThread = nullptr;

	std::shared_ptr<HandlePool> handlePool;

	std::shared_ptr<moodycamel::BlockingConcurrentQueue<Task>> taskQueue;

	std::shared_ptr<IOServicePool> servicePool;

	ID idCounter;
	std::mutex idMutex;
};

#endif

