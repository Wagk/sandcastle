/*!************************************************************
  Created:	2016/03/02
  Intent:
      Time to write a scheduler
  Usage:

  Note: 
      We probably have to roll inside the hazard pointer
      implementations, since it's tightly bound to the 
      lockless queue implementation.

      With the way we store hazard pointers per thread, at the
      time of writing we can effectively only have one lockless
      queue performing dequeuing or enqueueing operations per
      thread at any one time.

      We have no idea how to solve it so that we can treat the
      lockless queue as an object.

      The current proposed solution is to roll everything into
      the scheduler. The scheduler will manage the number of
      threads, the enqueueing and dequeue interface for 
      all those threads, and the hazard ptr memory management
      for those queues.

      We still need a way to effectively label each thread with
      some ID

      Another concern is the generation of a graph
**************************************************************/
#ifndef multicore_scheduler_h__
#define multicore_scheduler_h__

#include "concurrent_queue.h"
#include "concurrent_job.h"

#include "include_std.h"
#include "interface_singleton.h"
#include "export_macros.h"

namespace Concurrent
{

  class Scheduler : public Interface::Singleton
  {
  public:

    SANDCASTLE_API Scheduler();
    SANDCASTLE_API ~Scheduler();

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::Init
    	Returns  :	void
    	Brief    :		
    			sets up the thread info so we can toss in jobs, 
          otherwise it will be uninitialized and bad things happen
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    SANDCASTLE_API void Init();

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::Run
    	Returns  :	void
    	Brief    :		
    			this blocks (spawns all workers including the main thread
          worker), toss in the starter job first.

    	Expect   :		there's at least one job inside already
    	Ensure   :
    	Usage    :		
    **************************************************************/
    SANDCASTLE_API void Run();

    /*!************************************************************
    FullName :	Concurrent::Scheduler::AddJob
    Returns  :	void
    Parameter:	Job * job
    Brief    :
    Adds a single job to the main job queue (or whatever
    work stealing requires us to do in the future). The
    priority and affinity of the job is decided when the
    job was constructed
    Expect   :
    Ensure   :
    Usage    :
    **************************************************************/
    SANDCASTLE_API void AddJob(Job* job);

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::KillWorkers
    	Returns  :	void
    	Brief    :		
    			Terminates all workers, or rather tells them all to stop
          and then joins them
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void KillWorkers();

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::GetStopFlag
    	Returns  :	bool
    	Brief    :		
    			Worker threads use this to check on if they should stop
          working
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    bool GetStopFlag() const;

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::GetJob
    	Returns  :	Job*, the job to execute, nullptr if no jobs exist
    	Parameter:	JobAffinity affinity, which will dictate what 
                                        sort of jobs you can run
    	Brief    :		
    			Priority is settled internally
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    Job* GetJob(JobAffinity affinity);

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::CompleteJob
    	Returns  :	void
    	Parameter:	JobAffinity affinity
    	Brief    :		
    			Signals that a job of this particular affinity has been
          completed.

          Actually updates an internal counter so we can have 
          functioning condition variables.
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void CompleteJob(JobAffinity affinity);

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::GetJobCount
    	Returns  :	int
    	Parameter:	JobAffinity affinity
    	Brief    :		
    			Gets the number of jobs currently available for this
          particular affinity. Used mainly for workers to check
          if they should sleep
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    int GetJobCount(JobAffinity affinity) const;

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::GetAffinityMutex
    	Returns  :	Mutex&
    	Parameter:	JobAffinity affinity
    	Brief    :		
    			Gets the mutex associated to this affinity. Used for the
          condition variables
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    std::mutex& GetAffinityMutex(JobAffinity affinity);

    /*!************************************************************
    	FullName :	Concurrent::Scheduler::GetAffinityCondVar
    	Returns  :	ConditionVariable&
    	Parameter:	JobAffinity affinity
    	Brief    :		
    			Gets the condition variable for this affinity. Used so
          the worker threads dont spin and the application doesnt
          melt the system waiting
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    ConditionVariable& GetAffinityCondVar(JobAffinity affinity);

  private:

    void InitWorkers();
    void MainThreadWorker(); //main thread runs this so it can do graphics

    std::atomic<bool> m_stop = false; //flag to stop working
    std::vector<std::thread> m_workers;

    LockFreeQueue<Job*> m_jobqueue[AFFINITY_NUM][PRIORITY_NUM];

    Atomic<int>         m_jobcounter[AFFINITY_NUM];
    std::mutex          m_jobmutex[AFFINITY_NUM];
    ConditionVariable   m_jobcondvar[AFFINITY_NUM];

  };

} //namespace Concurrent

#endif // multicore_scheduler_h__
/*!************************************************************
  Todo:
    
  References:
    
**************************************************************/


