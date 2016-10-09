#ifndef concurrency_job_h__
#define concurrency_job_h__

#include "export.h"
#include "counter.h"

#include <vector>

namespace sandcastle 
{
	namespace concurrency
	{

		class SANDCASTLE_CONCURRENCY_API job
		{
		public:

			void run();

			void notify(counter*);

			void reset_notify_list();

		protected:

			virtual void func() = 0;

			std::vector<counter*> _ctrs;

		};

	}
} 

#endif