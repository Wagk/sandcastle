#include "thread.h"

#include <limits>

namespace sandcastle::concurrency::this_thread
{
	thread_local size_t thread_id = std::numeric_limits<size_t>::max();
	thread_local worker this_worker;
}