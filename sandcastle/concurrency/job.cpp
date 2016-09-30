#include "job.h"

namespace sandcastle
{
	namespace concurrency
	{

		void job::run()
		{
			func();
		}

	} //namespace concurrency
}