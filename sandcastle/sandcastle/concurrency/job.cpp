#include "job.h"

namespace sandcastle::concurrency
{
	job::job(worker_affinity affinity)
		: _affinity(affinity)
		, _ctrs(0)
	{
	}

	worker_affinity job::affinity() const
	{
		return _affinity;
	}

	void job::run()
	{
		func();

		for (counter* ctr : _ctrs)
		{
			--(*ctr);
		}
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