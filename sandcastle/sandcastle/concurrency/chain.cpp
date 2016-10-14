#include "chain.h"
#include "thread.h"

namespace sandcastle::concurrency
{
	chain::chain()
	{
	}

	void chain::push_back(job * j)
	{
		if (j)
		{
			_jobs.push_back(j);
		}
	}

	void chain::clear()
	{
		_jobs.clear();
	}

	void chain::func()
	{
		for (job* const j : _jobs)
		{
			j->run();
		}
	}
}