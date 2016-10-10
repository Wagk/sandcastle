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
				run_one();
			}
		}

		bool worker::run_one()
		{
			job* task = nullptr;

			if (task = collect_job())
			{
				task->run();

				return true;
			}

			return false;
		}

		void worker::submit_job(job* task)
		{
			if (task == nullptr)
				return;

			_data._work->push(task);
		}

		job * worker::collect_job()
		{
			job* task = _data._work->pop();

			if (task)
				return task;
			else
			{
				for (deque* elem : _data._steal)
				{
					if (task = elem->steal())
						return task;
				}
			}

			return nullptr;
		}

	} //namespace concurrency
}