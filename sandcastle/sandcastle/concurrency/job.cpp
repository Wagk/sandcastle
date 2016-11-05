#include "job.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	job::job(worker_affinity affinity)
		: _running(false)
		, _affinity(affinity)
		, _ctrs(0)
	{
	}

	void job::detach()
	{
		_running = true;
		_done = false;

		this_thread::this_worker.submit_job(this);
	}

	worker_affinity job::affinity() const
	{
		return _affinity;
	}

	void job::run()
	{
		_running = true;
		_done = false;

		func();

		for (counter* ctr : _ctrs)
		{
			--(*ctr);
		}

		_running = false;
		_done = true;
	}

	bool job::done() const
	{
		return _done;
	}

	void job::notify(counter * ctr)
	{
		if (ctr)
			_ctrs.push_back(ctr);
	}

	void job::reset_notify_list()
	{
		_ctrs.clear();
	}
}