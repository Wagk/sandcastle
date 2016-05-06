#include "concurrent_scheduler.h"
#include "concurrent_worker.h"

#include "include_assert.h"


namespace Concurrent
{

  /*!************************************************************

  **************************************************************/
  Scheduler::~Scheduler()
  {
    KillWorkers();
  }

  /*!************************************************************
    This only inits the non-affinity workers. Remember that
    the main thread needs to be turned into a worker
  **************************************************************/
  void Scheduler::InitWorkers()
  {
    for (size_t i = 0; i < HARDWARE_CONCURRENCY - 1; ++i)
    {
      ThreadInitInfo info = { i, this, AFFINITY_WORKER };

      //it's minus 1 because main thread isn't handled by the scheduler
      m_workers[i] = std::move(std::thread(WorkerThread, info));
    }
  }

  /*!************************************************************

  **************************************************************/
  void Scheduler::KillWorkers()
  {
    m_stop = true;

    for (size_t i = 0; i < HARDWARE_CONCURRENCY - 1; ++i)
    {
      if (m_workers[i].joinable())
      {
        m_workers[i].join();
      }
    }
  }

  /*!************************************************************

  **************************************************************/
  void Scheduler::AddJob(Job* job)
  {
    if (job == nullptr) return;

    JobAffinity jobaffin = job->GetAffinity();

    ++m_jobcounter[jobaffin];

    m_jobqueue[jobaffin][job->GetPriority()].Enqueue(job);

    m_jobcondvar[jobaffin].notify_one();
  }

  /*!************************************************************

  **************************************************************/
  bool Scheduler::GetStopFlag() const
  {
    return m_stop.load(); //consider using some of those fancy atomic flags
  }

  /*!************************************************************
  other affinities need to pick up some slack sometimes
  **************************************************************/
  Job* Scheduler::GetJob(JobAffinity affinity)
  {
    //pop light jobs first
    Job* job = nullptr;

    //here we rely on short-circuit evaluation to make sure that light jobs
    //get priority
    if (m_jobqueue[affinity][PRIORITY_LIGHT].Dequeue(job) == true ||
      m_jobqueue[affinity][PRIORITY_NORMAL].Dequeue(job) == true)
    {
      return job;
    }
    else
    {

      //special dispensation for main thread to process graphics stuff
      //so they have already processed graphics, time to pick up other things
      if (affinity == AFFINITY_MAIN)
      {
        if (m_jobqueue[AFFINITY_WORKER][PRIORITY_LIGHT].Dequeue(job) == true ||
          m_jobqueue[AFFINITY_WORKER][PRIORITY_NORMAL].Dequeue(job) == true)
        {
          return job;
        }
      }

      return nullptr;
    }
  }

  /*!************************************************************

  **************************************************************/
  Scheduler::Scheduler()
    : m_stop(false)
    , m_workers(HARDWARE_CONCURRENCY - 1) //scheduler doesn't handle main thread
    , m_jobqueue{}
    , m_jobcounter{ 0, 0 }
    , m_jobmutex{}
    , m_jobcondvar{}
  {

  }

  /*!************************************************************

  **************************************************************/
  void Scheduler::MainThreadWorker()
  {
    ThreadInitInfo info = { HARDWARE_CONCURRENCY - 1 , this, AFFINITY_MAIN };
    //refer to InitWorker about the ID;

    WorkerThread(info);
  }

  /*!************************************************************

  **************************************************************/
  void Scheduler::Run()
  {
    InitWorkers();
    MainThreadWorker();
  }

  /*!************************************************************

  **************************************************************/
  void Scheduler::Init()
  {
    ThreadInitInfo info = { HARDWARE_CONCURRENCY - 1 , this, AFFINITY_MAIN };

    Thread::GetInfo() = info;
  }

  /*!************************************************************

  **************************************************************/
  int Scheduler::GetJobCount(JobAffinity affinity) const
  {
    return m_jobcounter[affinity].load();
  }

  /*!************************************************************

  **************************************************************/
  std::mutex& Scheduler::GetAffinityMutex(JobAffinity affinity)
  {
    return m_jobmutex[affinity];
  }

  /*!************************************************************

  **************************************************************/
  ConditionVariable& Scheduler::GetAffinityCondVar(JobAffinity affinity)
  {
    return m_jobcondvar[affinity];
  }

  /*!************************************************************

  **************************************************************/
  void Scheduler::CompleteJob(JobAffinity affinity)
  {
    ++m_jobcounter[affinity];
  }

} //namespace Concurrent

