#include "concurrent_worker.h"
#include "include_std.h"

namespace Concurrent
{

  /*!************************************************************
  We assume that whoever calls this is a worker, since they are
  the only ones that will actually consume jobs and run code,
  hence, the info's are initialized
  **************************************************************/
  void WorkSingleJob()
  {
    JobAffinity affinity = Thread::GetInfo().GetAffinity();
    Scheduler& scheduler = *Thread::GetInfo().GetScheduler();

    //grab a job (priority to be decided)
    Job* job = scheduler.GetJob(affinity);

    if (job == nullptr) return;
    else
    {
      job->Run();
    }

    scheduler.CompleteJob(affinity);
  }

  /*!************************************************************

  **************************************************************/
  void WorkerThread(ThreadInitInfo init)
  {
    //set up preliminary stuff for the lifetime of the thread
    Thread::SetInfo(init);

    JobAffinity affinity = Thread::GetInfo().GetAffinity();
    Scheduler& scheduler = *Thread::GetInfo().GetScheduler();

    //start looping forever
    while (scheduler.GetStopFlag() == false)
    {
      while (scheduler.GetJobCount(affinity) <= 0)
      {
        std::unique_lock<std::mutex> lock(scheduler.GetAffinityMutex(affinity));
        scheduler.GetAffinityCondVar(affinity).wait(lock);
      }

      WorkSingleJob();
    }
  }

} //namespace Concurrent

