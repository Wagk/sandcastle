/*!************************************************************
  Created	:	2016/03/14
  Note	:

**************************************************************/
#include "concurrent_job.h"
#include "include_assert.h"
#include "concurrent_thread.h"

namespace Concurrent
{

  /*!************************************************************

  **************************************************************/
  Job::Job(JobAffinity affinity, JobPriority priority)
    : m_affinity(affinity)
    , m_priority(priority)
  {

  }

  /*!************************************************************

  **************************************************************/
  void Job::Schedule()
  {
    m_done = false;

    Thread::info.GetScheduler()->AddJob(this);
  }

  /*!************************************************************

  **************************************************************/
  void Job::Run()
  {
    JobDefinition();

    //decrement every trigger, they'll know when they're done
    for (auto& trigger : m_notify)
    {
      --(*trigger);
    }

    m_done = true;
  }

  /*!************************************************************

  **************************************************************/
  bool Job::Done() const
  {
    return m_done; //should this be atomic?
  }

  /*!************************************************************

  **************************************************************/
  JobAffinity Job::GetAffinity() const
  {
    return m_affinity;
  }

  /*!************************************************************

  **************************************************************/
  JobPriority Job::GetPriority() const
  {
    return m_priority;
  }

  /*!************************************************************

  **************************************************************/
  void Job::AddTrigger(Trigger* to_notify)
  {
    if (to_notify == nullptr) return;

    m_notify.emplace_back(to_notify);
  }


  /*!************************************************************

  **************************************************************/
  void Job::RemoveTrigger(Trigger* stop_notify)
  {
    if (stop_notify == nullptr) return;

    m_notify.erase(std::find(m_notify.begin(), m_notify.end(), stop_notify));
  }

} //namespace Concurrent

/*!************************************************************
  Todo:

  References:

**************************************************************/
