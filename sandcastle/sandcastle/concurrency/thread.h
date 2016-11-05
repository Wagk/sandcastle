#ifndef concurrency_thread_h
#define concurrency_thread_h

#include <vector>

#include "worker.h"
#include "deque.h"

namespace sandcastle::concurrency::this_thread
{
	extern thread_local size_t thread_id;
	extern thread_local worker this_worker;
}

#endif