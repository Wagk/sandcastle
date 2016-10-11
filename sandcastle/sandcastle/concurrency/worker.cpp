#include "worker.h"

#include <cassert>
#include <thread>

namespace sandcastle::concurrency
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
			if (run_one() == false)
			{
				std::unique_lock<std::mutex> lock(*_data._sleeplock);
				_data._sleep->wait(lock);
			}
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

		if (task->affinity() == GRAPHICS)
		{
			_data._graphics->push(task);
			_data._sleepgraphics->notify_one();
		}
		else
		{
			_data._work->push(task);
			_data._sleep->notify_one();
		}

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

}