#ifndef concurrency_worker_h__
#define concurrency_worker_h__

#include <atomic>
#include <vector>
#include <condition_variable>

#include "job.h"
#include "deque.h"

namespace sandcastle::concurrency
{
	struct worker_data
	{
		deque* _work;
		std::vector<deque*> _steal;
		std::atomic<bool>* _stop;
		std::condition_variable* _sleep;
		std::mutex* _sleeplock;
	};

	class worker
	{
	public:

		void init(const worker_data& info);

		void run();
		bool run_one();

		void submit_job(job* job);

	private:

		job* collect_job();

		worker_data _data;

	};

}

#endif