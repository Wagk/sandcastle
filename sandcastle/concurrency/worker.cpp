#include "worker.h"

#include <cassert>

namespace sandcastle
{
	namespace concurrency
	{

		void worker::init(const worker_data& info)
		{
			assert(info._work);
			assert(info._stop);

			_data = info;
		}

		void worker::run()
		{
			while (_data._stop->load() == false)
			{
				job* task = nullptr;

				if (task = _data._work->pop())
				{
					task->run();
				}
				else
				{
					for (deque* elem : _data._steal)
					{
						if (task = elem->steal())
							break;
					}

					if (task)
						task->run();
					else
					{
						//sleep
					}
				}
			}
		}

		void worker::submit_job(job* task)
		{
			if (task == nullptr)
				return;

			_data._work->push(task);
		}

	} //namespace concurrency
}