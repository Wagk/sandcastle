#include "concurrent_thread.h"

namespace Concurrent
{
  namespace Thread
  {

    thread_local ThreadInfo info; //initialization
    thread_local HazardPackage<LOCKLESS_QUEUE_HAZARD_ALLOC, SCHEDULING> hazardous;

    /*!************************************************************

    **************************************************************/
    ThreadInfo GetInfo()
    {
      return info;
    }

  }


  /*!************************************************************

  **************************************************************/
  ThreadInitInfo::ThreadInitInfo(ThreadID tid, Scheduler* sptr, JobAffinity jaffin)
    : id(tid)
    , scheduler(sptr)
    , affinity(jaffin)
  {

  }

  /*!************************************************************

  **************************************************************/
  Concurrent::ThreadID ThreadInfo::GetID() const
  {
    return m_id;
  }

  /*!************************************************************

  **************************************************************/
  Scheduler* ThreadInfo::GetScheduler()
  {
    return m_scheduler;
  }

  /*!************************************************************

  **************************************************************/
  Concurrent::JobAffinity ThreadInfo::GetAffinity() const
  {
    return m_affinity;
  }

  /*!************************************************************

  **************************************************************/
  ThreadInfo& ThreadInfo::operator=(const ThreadInitInfo& rhs)
  {
    m_id = rhs.id;
    m_scheduler = rhs.scheduler;
    m_affinity = rhs.affinity;

    return *this;
  }

} //namespace multicore

