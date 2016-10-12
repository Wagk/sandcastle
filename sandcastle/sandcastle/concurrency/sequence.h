#ifndef concurrency_sequence_h__
#define concurrency_sequence_h__

#include <vector>

#include "job.h"

/*
	A batch is a lot of jobs done in parallel
	a sequence is an ordering of jobs done in sequence

	I think they are perpendicular to each other,
	you can have a batch of sequences and a sequence of batches
*/

namespace sandcastle::concurrency
{
	class sequence : public job
	{
	public:

		sequence();

	private:

		virtual void func() override;
		
		std::vector<job*> _seq;

	};
}

#endif