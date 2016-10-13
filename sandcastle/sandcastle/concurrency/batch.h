#ifndef concurrency_batch_h__
#define concurrency_batch_h__

#include "export.h"

#include <vector>
#include <atomic>
#include "job.h"
#include "counter.h"

namespace sandcastle::concurrency
{
	class SANDCASTLE_CONCURRENCY_API batch : public job
	{
	public:

		batch();
		batch(job* job, size_t size = 1);

		void wait();

		void add(job* job, size_t size = 1);

	private:

		virtual void func() override;

		counter _ctr;
		std::vector<job*> _jobs;

	};
}

#endif