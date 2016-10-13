#ifndef concurrency_job_h__
#define concurrency_job_h__

#include "export.h"
#include "counter.h"

#include <vector>

namespace sandcastle::concurrency
{
	enum worker_affinity
	{
		AFFINITY_GRAPHICS,
		AFFINITY_NONE
	};

	class SANDCASTLE_CONCURRENCY_API job
	{
	public:

		job(worker_affinity = AFFINITY_NONE);

		void run();		//blocks
		void detach();	//does not block

		worker_affinity affinity() const;
		bool done() const;

		void notify(counter*);
		void reset_notify_list();

	protected:

		virtual void func() = 0;

		bool _running = false;
		bool _done = false;
		worker_affinity _affinity;
		std::vector<counter*> _ctrs;

	};
}

#endif