#include <iostream>

#include <concurrency/kernel.h>
#include <concurrency/chain.h>
#include <concurrency/batch.h>
#include <atomic>
#include <mutex>
#include <string>
#include <sstream>

/*
	Each thread has a worker object
*/

void thread_print(const std::ostringstream& str)
{
	static std::mutex spin;

	std::lock_guard<std::mutex> lock(spin);

	std::cout << str.str() << std::endl;
}

struct test_job : public sandcastle::concurrency::job
{
public:

	test_job(std::atomic<int>& ref) : _ctr(ref) {}

private:

	virtual void func() override
	{
		int i = ++_ctr;

		std::ostringstream str;

		str << "_ctr: " << i << " thread: " << sandcastle::concurrency::this_thread::thread_id;

		thread_print(str);
	}

	std::atomic<int>& _ctr;

};

template<typename T, typename ...Args>
sandcastle::concurrency::job* create_jobs(size_t num, Args&&... params)
{
	return new T[num](params);
}

int main(int argc, char* argv[])
{
	std::atomic<int> counter(0);

	using sandcastle::concurrency::chain;
	using sandcastle::concurrency::batch;
	using sandcastle::concurrency::job;

	batch b1;
	job* jobs = create_jobs<test_job>(10, counter);
	b1.add(jobs, 10);

	chain c1;
	c1.push_back(&b1);
	c1.push_back(&b1);

	sandcastle::concurrency::kernel::get().init(&c1);

	delete[] jobs;
}