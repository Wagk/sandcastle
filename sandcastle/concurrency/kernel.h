#ifndef concurrency_kernel_h__
#define concurrency_kernel_h__

/*
	- spawns workers
	- informs them of the queues of other workers to steal from
*/

#include <thread>
#include <vector>
#include <atomic>

#include "deque.h"
#include "thread.h"
#include "worker.h"

#include "export.h"

namespace sandcastle
{
	namespace concurrency
	{
		class SANDCASTLE_CONCURRENCY_API kernel
		{
		public:

			static kernel& get()
			{
				static kernel singleton;
				return singleton;
			}

			void init();
			void shutdown();

			void launch_main_worker();

		private:

			static void launch_worker(worker_data data);

			unsigned int _numthreads; //including main thread

			std::atomic<bool> _stop;

			worker_data _main_data;

			std::vector < std::thread > _threadpool;
			std::vector < deque > _queuepool;

		};

	} //namespace concurrency
}

#endif