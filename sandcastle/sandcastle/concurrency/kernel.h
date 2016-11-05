#ifndef concurrency_kernel_h__
#define concurrency_kernel_h__

/*
	- spawns workers
	- informs them of the queues of other workers to steal from
*/

#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>

#include "deque.h"
#include "thread.h"
#include "worker.h"

#include "export.h"

namespace sandcastle::concurrency
{

	struct thread_info
	{
		size_t _thread_id;
		worker_data _data;
	};

	class SANDCASTLE_CONCURRENCY_API kernel
	{
	public:

		static kernel& get()
		{
			static kernel singleton;
			return singleton;
		}

		void init(job* begin);
		void shutdown();

	private:

		static void launch_worker(thread_info data);

		unsigned int _numthreads; //including main thread

		std::atomic<bool> _stop;

		worker_data _main_data;

		std::vector < std::thread > _threadpool;
		std::vector < deque > _queuepool;

		std::mutex _sleeplock;
		std::mutex _sleeplock_graphics;

		std::condition_variable _sleep;
		std::condition_variable _sleep_graphics;

	};

}

#endif