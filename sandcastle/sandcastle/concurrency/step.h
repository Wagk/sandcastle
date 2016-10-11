#ifndef concurrent_step_h__
#define concurrent_step_h__

#include "job.h"
#include "batch.h"

namespace sandcastle::concurrency
{
	class step : public job
	{
	public:

		step(job*, size_t size = 1);

		void next(job*);

	private:

		virtual void func() override;

		job* _next;
		batch _jobs;

	};
}

#endif