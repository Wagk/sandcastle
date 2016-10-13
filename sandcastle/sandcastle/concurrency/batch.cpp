#include "batch.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	batch::batch()
		: job(AFFINITY_NONE)
	{

	}

	batch::batch(job * job, size_t size)
		: job(AFFINITY_NONE)
	{
		add(job, size);
	}

	void batch::wait()
	{
		while (_ctr > 0)
		{
			this_thread::this_worker.run_one();
		}
	}

	void batch::add(job * j, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			job* t = j + i;

			t->notify(&_ctr);
			++_ctr;

			_jobs.push_back(t);
		}
	}

	void batch::func()
	{
		//assume that the jobs are already registered
		for (job* job : _jobs)
		{
			this_thread::this_worker.submit_job(job);
		}
	}
}