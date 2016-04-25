/*!************************************************************
  Created	:	2016/04/05
  Intent	:

  Usage	:

  Note	:

**************************************************************/
#include "concurrent_worker_mutex.h"
#include "concurrent_worker.h"

namespace Concurrent
{
  /*!************************************************************

  **************************************************************/
  void WorkerMutex::unlock()
  {
    m_mutex.unlock();
  }

  /*!************************************************************

  **************************************************************/
  void WorkerMutex::lock()
  {
    bool has_lock = false;

    while (has_lock == false)
    {
      if (has_lock = m_mutex.try_lock()) return;
      else if (Thread::info.GetScheduler()->GetJobCount(Thread::info.GetAffinity()) > 0)
      {
        WorkSingleJob();
      }
      else
      {
        m_mutex.lock();
        has_lock = true;
      }

    }
  }

  /*!************************************************************

  **************************************************************/
  bool WorkerMutex::try_lock()
  {
    return m_mutex.try_lock();
  }

  /*!************************************************************

  **************************************************************/
  WorkerMutex::WorkerMutex()
    : m_mutex()
  {

  }

} //namespace Concurrent

/*!************************************************************
  Todo:

  References:

**************************************************************/


