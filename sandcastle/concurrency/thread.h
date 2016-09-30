#ifndef concurrency_thread_h
#define concurrency_thread_h

#include <vector>

#include "worker.h"
#include "deque.h"

namespace sandcastle 
{
	namespace concurrency
	{

		namespace this_thread
		{
			extern thread_local worker this_worker;
		}

	} //namespace concurrency
}

#endif