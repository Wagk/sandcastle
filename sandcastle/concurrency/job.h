#ifndef concurrency_job_h__
#define concurrency_job_h__

namespace sandcastle {
	namespace concurrency
	{

		class job
		{
		public:

			void run();

		protected:

			virtual void func() = 0;

		};

	}
} 

#endif