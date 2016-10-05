#ifndef concurrency_job_h__
#define concurrency_job_h__

#include "export.h"

namespace sandcastle 
{
	namespace concurrency
	{

		class SANDCASTLE_CONCURRENCY_API job
		{
		public:

			void run();

		protected:

			virtual void func() = 0;

		};

	}
} 

#endif