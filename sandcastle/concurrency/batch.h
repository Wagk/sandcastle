#ifndef concurrency_batch_h__
#define concurrency_batch_h__

#include "export.h"

#include <vector>
#include <atomic>
#include "job.h"

namespace sandcastle
{
	namespace concurrency
	{
		class SANDCASTLE_CONCURRENCY_API batch : public job
		{
		public:

			batch();

		private:

			virtual void func() override;

			std::vector<job*> _jobs;

		};
	}
}

#endif