#pragma once
#ifndef __HANDLEPOOL_H__
#define __HANDLEPOOL_H__

#include "ckdef.h"
#include "cktypes.h"

#include <mutex>
#include <map>
#include <memory>

class HandlePool
{
public:

	struct Handler
	{
		//handler number
		Id id;

		//handler
		Handle h;

		//flag of handler if block
		bool blocking;
	};

	typedef std::multimap<std::string, Handler> HandlerPool;
	typedef std::pair <HandlerPool::iterator, HandlerPool::iterator> Ret;

	HandlePool();
	virtual ~HandlePool();

	void WriteHandler(std::string type, Handler const& h);
	Ret ReadHandler(std::string type);

	bool DeleteHandler(std::string type, Id id);

private:

	std::recursive_mutex mutexOfMap;

	std::shared_ptr<HandlerPool> handlers;
};

#endif

