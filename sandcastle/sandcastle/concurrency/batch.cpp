#include "batch.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	batch::batch()
	{

	}

	void batch::func()
	{
		for (job* job : _jobs)
		{
			job->notify(&_ctr);
			++_ctr;
			this_thread::this_worker.submit_job(job);
		}

		while (_ctr > 0)
		{
			this_thread::this_worker.run_one();
		}
	}
}