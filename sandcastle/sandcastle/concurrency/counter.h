#ifndef concurrency_counter_h__
#define concurrency_counter_h__

#include <atomic>

namespace sandcastle::concurrency
{
	class counter
	{
	public:

		counter(int = 0);
		counter(const counter&);

		counter& operator=(int);
		counter& operator++();
		counter& operator--();

		operator int() const;
		bool operator==(const counter&) const;
		bool operator!=(const counter&) const;

	private:

		std::atomic<int> _ctr;

	};
}


#endif