#include <thread>
#include <utility>

#include "kernel.h"

namespace sandcastle::concurrency
{
	void kernel::init(job* startjob)
	{
		_numthreads = std::thread::hardware_concurrency();

		_threadpool.resize(_numthreads - 1);
		_queuepool.resize(_numthreads);

		//_queuepool[0] is ALWAYS graphics thread
		_main_data._stop		= &_stop;
		_main_data._sleeplock	= &_sleeplock_graphics;
		_main_data._graphics	= _main_data._work			= &_queuepool[0];
		_main_data._sleep		= _main_data._sleepgraphics	= &_sleep_graphics;

		for (auto& elem : _queuepool)
		{
			if (&elem == _main_data._work)
				continue;

			_main_data._steal.push_back(&elem);
		}

		//other workers
		for (size_t i = 1; i < _queuepool.size(); ++i)
		{
			worker_data data;
			data._stop			= &_stop;
			data._work			= &_queuepool[i];
			data._sleep			= &_sleep;
			data._sleeplock		= &_sleeplock;
			data._graphics		= _main_data._graphics;
			data._sleepgraphics	= _main_data._sleepgraphics;

			for (size_t j = 0; j < _queuepool.size(); ++j)
			{
				if (data._work == &_queuepool[j])
					continue;

				data._steal.push_back(&_queuepool[j]);
			}

			thread_info info;
			info._data = data;
			info._thread_id = i;

			_threadpool[i - 1] = std::move(std::thread(&kernel::launch_worker, info));
		}

		//main worker info
		this_thread::thread_id = 0;
		this_thread::this_worker.init(_main_data);
		this_thread::this_worker.submit_job(startjob);
		this_thread::this_worker.run();
	}

	void kernel::shutdown()
	{
		_stop.store(true);

		for (auto& thread : _threadpool)
		{
			thread.join();
		}
	}

	void kernel::launch_worker(thread_info data)
	{
		this_thread::thread_id = data._thread_id;
		this_thread::this_worker.init(data._data);

		this_thread::this_worker.run();
	}

}