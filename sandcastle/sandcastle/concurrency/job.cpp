#include "job.h"

namespace sandcastle::concurrency
{
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