#include "deque.h"

namespace sandcastle::concurrency
{
	deque::deque()
	{

	}

	deque::deque(const deque & rhs)
		: _queue(rhs._queue)
	{

	}

	bool deque::empty() const
	{
		std::lock_guard<std::mutex> lock(_lock);

		return _queue.empty();
	}

	void deque::push(job* task)
	{
		if (task == nullptr)
			return;

		std::lock_guard<std::mutex> lock(_lock);

		_queue.push_front(task);
	}

	job * deque::pop()
	{
		std::lock_guard<std::mutex> lock(_lock);

		if (_queue.empty() == true)
			return nullptr;

		job* task = _queue.front();
		_queue.pop_front();

		return task;
	}

	job * deque::steal()
	{
		std::lock_guard<std::mutex> lock(_lock);

		if (_queue.empty() == true)
			return nullptr;

		job* task = _queue.back();
		_queue.pop_back();

		return task;
	}
}