#include "EventEngine/HandlePool.h"

HandlePool::HandlePool():handlers(new HandlerPool)
{
}

HandlePool::~HandlePool()
{
}


void HandlePool::WriteHandler(std::string type, Handler const& h)
{
	std::lock_guard<std::recursive_mutex> lock(mutexOfMap);

	handlers->insert(std::make_pair(type,h));
}

HandlePool::Ret HandlePool::ReadHandler(std::string type)
{
	std::lock_guard<std::recursive_mutex> lock(mutexOfMap);
	return handlers->equal_range(type);
}

bool HandlePool::DeleteHandler(std::string type, Id id)
{
	std::lock_guard<std::recursive_mutex> lock(mutexOfMap);

	Ret ret = ReadHandler(type);
	for (auto it = ret.first; it != ret.second; it++)
	{
		if (it->second.id == id)
		{
			if (ret.first == handlers->begin())
			{
				handlers->erase(handlers->begin());
			}
			else
			{
				auto temp = it;
				temp--;
				handlers->erase(it);				
				it = temp;
			}

			return true;
		}
	}
	return false;
}
