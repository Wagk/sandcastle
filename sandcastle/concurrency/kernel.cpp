#include <thread>
#include <utility>

#include "kernel.h"

namespace sandcastle
{
	namespace concurrency
	{

		void kernel::init()
		{
			_numthreads = std::thread::hardware_concurrency();

			_threadpool.resize(_numthreads - 1);
			_queuepool.resize(_numthreads);

			//_queuepool[0] is ALWAYS graphics thread
			_main_data._stop = &_stop;
			_main_data._work = &_queuepool[0];

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

				data._stop = &_stop;
				data._work = &_queuepool[i];

				for (size_t j = 1; j < _queuepool.size(); ++j)
				{
					if (data._work == &_queuepool[j])
						continue;

					data._steal.push_back(&_queuepool[j]);
				}

				_threadpool[i - 1] = std::move(std::thread(&kernel::launch_worker, data));
			}

		}

		void kernel::shutdown()
		{
			_stop.store(true);

			for (auto& thread : _threadpool)
			{
				thread.join();
			}
		}

		void kernel::launch_main_worker()
		{
			launch_worker(_main_data);
		}

		void kernel::launch_worker(worker_data data)
		{
			this_thread::this_worker.init(data);

			this_thread::this_worker.run();
		}

	} //namespace concurrency
}