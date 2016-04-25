/*!************************************************************
	Created:	2016/03/02
	Intent:		
			stores all the per-thread information
	Usage:
			
**************************************************************/
#ifndef multicore_thread_h__
#define multicore_thread_h__

#include <thread>
#include <limits>
#include "concurrent_hazard.h"
#include "concurrent_scheduler.h"
#include "concurrent_job.h"

#define LOCKLESS_QUEUE_HAZARD_ALLOC 2

//safe to set this to 1, leaving only the main thread working
//const size_t HARDWARE_CONCURRENCY = 1;
const size_t HARDWARE_CONCURRENCY = std::thread::hardware_concurrency();

namespace Concurrent
{

  using ThreadID = size_t;
  class Scheduler;

  struct ThreadInitInfo
  {
    ThreadInitInfo(ThreadID tid, Scheduler* sptr, JobAffinity jaffin);

    ThreadID   id = std::numeric_limits<ThreadID>::max();
    Scheduler* scheduler = nullptr;
    JobAffinity affinity;     //the type of jobs that are allowed to run
  };

  class ThreadInfo
  {
  public:

    ThreadInfo() = default;
    ThreadInfo& operator=(const ThreadInitInfo& rhs);

    ThreadID GetID() const;
    Scheduler* GetScheduler();
    JobAffinity GetAffinity() const;

  private:

    ThreadID m_id = -1;               //this thread's ID, relative to its hazard alloc
    Scheduler* m_scheduler = nullptr; //the scheduler assigned to this thread
    JobAffinity m_affinity = AFFINITY_WORKER; //this thread's affinity

  };

  /*
   _______ _    _ _____  ______          _____
  |__   __| |  | |  __ \|  ____|   /\   |  __ \
     | |  | |__| | |__) | |__     /  \  | |  | |
     | |  |  __  |  _  /|  __|   / /\ \ | |  | |
     | |  | |  | | | \ \| |____ / ____ \| |__| |
    _|_|_ |_|  |_|_|_ \_\______/_/   _\_\_____/___
   / ____| |    / __ \|  _ \   /\   | |     / ____|
  | |  __| |   | |  | | |_) | /  \  | |    | (___
  | | |_ | |   | |  | |  _ < / /\ \ | |     \___ \
  | |__| | |___| |__| | |_) / ____ \| |____ ____) |
   \_____|______\____/|____/_/    \_\______|_____/
  */
  namespace Thread
  {
    extern thread_local ThreadInfo info; //initialization
    extern thread_local HazardPackage<LOCKLESS_QUEUE_HAZARD_ALLOC, SCHEDULING> hazardous;
  }

} //namespace Concurrent

#endif // multicore_thread_h__
/*!************************************************************
	Todo:
			
**************************************************************/


