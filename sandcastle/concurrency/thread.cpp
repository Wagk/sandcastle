#include "thread.h"

namespace sandcastle
{
	namespace concurrency
	{
		namespace this_thread
		{
			thread_local worker this_worker;
		}
	} //namespace concurrency
}