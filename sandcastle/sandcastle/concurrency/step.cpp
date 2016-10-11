#include "step.h"

namespace sandcastle::concurrency
{
	step::step(job * jobs, size_t size)
		: _jobs(jobs, size)
	{

	}

	void step::next(job * next)
	{
		_next = next;
	}

	void step::func()
	{
	}
}