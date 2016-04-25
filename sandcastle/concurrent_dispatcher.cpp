/*!************************************************************
	Created	:	2016/03/14
	Note	:
		
**************************************************************/
#include "concurrent_dispatcher.h"
#include "concurrent_scheduler.h"
#include "concurrent_worker.h"
#include "include_assert.h"

namespace Concurrent
{

  /*!***************************************O*********************

  **************************************************************/
  SimpleDispatcher::SimpleDispatcher(const Vector<Job*>& jobs)
    : m_dispatched(false)
    , m_jobs(jobs)
    , m_trigger()
  {

  }

  /*!************************************************************
    This might be thread-unsafe, and we must be wary.

    Will we ever copy construct in a thread-unsafe way?
  **************************************************************/
  SimpleDispatcher::SimpleDispatcher(const SimpleDispatcher& rhs)
    : m_dispatched(rhs.m_dispatched)
    , m_jobs(rhs.m_jobs)
    , m_trigger(rhs.m_trigger)
  {
    
  }

  /*!************************************************************
  want this to work while the block is dispatched? It won't be
  immediately appended, of course,
  **************************************************************/
  void SimpleDispatcher::Insert(Job* job)
  {
    EXPECT(m_dispatched == false);
    if (job)
    {
      m_jobs.push_back(job);
    }
  }

  /*!************************************************************

  **************************************************************/
  void SimpleDispatcher::AssignBlock(const Vector<Job*>& jobs)
  {
    m_jobs = jobs;
  }

  /*!************************************************************

  **************************************************************/
  void SimpleDispatcher::Dispatch()
  {
    if (m_dispatched == true) return;
    else
    {
      for (Job* elem : m_jobs)
      {
        elem->AddTrigger(&m_trigger);
        ++m_trigger;

        elem->Job::Schedule();
      }

      m_dispatched = true;
    }
  }

  /*!************************************************************
  We assume that once this is done we are immediately
  ready to dispatch again
  **************************************************************/
  void SimpleDispatcher::Wait()
  {
    if (m_dispatched == false) return;
    else
    {
      while (m_trigger.Done() == false)
      {
        WorkSingleJob(); //do jobs while waiting for things to settle
      }

      for (Job* elem : m_jobs)
      {
        elem->RemoveTrigger(&m_trigger);
      }

      //reset state
      m_trigger = 0;
      m_dispatched = false;
    }
  }

  /*!************************************************************

  **************************************************************/
  void SimpleDispatcher::Clear()
  {
    EXPECT(m_dispatched == false);

    m_jobs.clear();
    m_trigger = 0;
  }

  /*!************************************************************

  **************************************************************/
  void SimpleDispatcher::JobDefinition()
  {
    Dispatch();
    Wait();
  }

  /*!************************************************************

  **************************************************************/
  SimpleDispatcher& SimpleDispatcher::operator=(const SimpleDispatcher& rhs)
  {
    EXPECT(m_dispatched == false);
    
    m_jobs = rhs.m_jobs;
    m_trigger = rhs.m_trigger;
    
    return *this;
  }

} //namespace Concurrent


/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/
