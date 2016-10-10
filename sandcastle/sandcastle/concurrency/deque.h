#ifndef concurrency_deque_h__
#define concurrency_deque_h__

#include <mutex>
#include <deque>

#include "job.h"

/*
	TODO:
		- Make this lockfree
*/

namespace sandcastle::concurrency
{
	class deque
	{
	public:

		deque();
		deque(const deque& rhs);

		bool empty() const;

		void push(job* task);
		job* pop();
		job* steal();

	private:

		mutable std::mutex _lock;
		std::deque<job*> _queue;

	};
}


#endif