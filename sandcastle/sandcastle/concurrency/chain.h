#ifndef concurrency_sequence_h__
#define concurrency_sequence_h__

#include <vector>

#include "job.h"

/*
	A batch is a lot of jobs done in parallel
	a chain is an ordering of jobs done in sequence

	I think they are perpendicular to each other,
	you can have a batch of chains and a chain of batches
*/

namespace sandcastle::concurrency
{
	class chain : public job
	{
	public:

		chain();

		void push_back(job*);
		void clear();

	private:

		virtual void func() override;
		
		std::vector<job*> _jobs;

	};
}

#endif