/*!************************************************************
  Created	:	2016/03/03
  Intent	:

  Usage	:

  Note	:
          Jobs, on completion, should tell all the triggers
          that they are done. This is so that JobBlocks can
          know when every job they are responsible for is
          complete, and they can move on with their lives
**************************************************************/
#ifndef multicore_job_h__
#define multicore_job_h__

#include <vector>
#include "concurrent_trigger.h"

#include "export_macros.h"

namespace Concurrent
{
  enum JobPriority
  {
    PRIORITY_LIGHT,
    PRIORITY_NORMAL,
    PRIORITY_NUM
  };

  enum JobAffinity
  {
    AFFINITY_WORKER,
    AFFINITY_MAIN,
    AFFINITY_NUM
  };

  //the base class, which interface we will use
  class Job
  {
  public:

    /*!************************************************************
      FullName :	Concurrent::Job::Job
      Returns  :
      Parameter:	JobAffinity affinity
      Parameter:	JobPriority priority
      Brief    :
          Constructor. The nature of the job is determined from
          the very beginning
      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    SANDCASTLE_API Job(JobAffinity affinity = AFFINITY_MAIN,
      JobPriority priority = PRIORITY_NORMAL);

    virtual ~Job() = default;

    /*!************************************************************
      FullName :	Concurrent::Job::Schedule
      Returns  :	void
      Brief    :
          Throws this job into the scheduler

          This is an **ASYNCHRONOUS** call
          
      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    void Schedule();

    /*!************************************************************
      FullName :	Concurrent::Job::Run
      Returns  :	void
      Brief    :
          Called when the job is being performed/called

          This is a **BLOCKING** call

      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    SANDCASTLE_API void Run();

    /*!************************************************************
      FullName :	Concurrent::Job::Done
      Returns  :	bool, true if done, false otherwise
      Brief    :
          Checks to see if the job is done
      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    bool Done() const;

    /*!************************************************************
      FullName :	Concurrent::Job::GetAffinity
      Returns  :	Concurrent::JobAffinity
      Brief    :
          Returns the affinity of this job
      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    JobAffinity GetAffinity() const;

    /*!************************************************************
      FullName :	Concurrent::Job::GetPriority
      Returns  :	Concurrent::JobPriority
      Brief    :
          Returns the priority of this job
      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    JobPriority GetPriority() const;

    /*!************************************************************
      FullName :	Concurrent::Job::AddTrigger
      Returns  :	void
      Parameter:	Trigger * to_notify
      Brief    :
          Adds a trigger to be notified once the job is finished
      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    void AddTrigger(Trigger* to_notify);

    /*!************************************************************
    	FullName :	Concurrent::Job::RemoveTrigger
    	Returns  :	void
    	Parameter:	Trigger * stop_notify
    	Brief    :		
    			Removes a trigger from the pool of triggers that will be
          notified when the job finishes executing.

          I'm suspecting that each job will only have up to 1 
          trigger anyway, but who knows.

    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void RemoveTrigger(Trigger* stop_notify);

  protected:

    /*!************************************************************
      FullName :	Concurrent::Job::JobDefinition
      Returns  :	void
      Brief    :
          The definition of the job itself, defined by base classes
      Expect   :
      Ensure   :
      Usage    :
    **************************************************************/
    virtual void JobDefinition() = 0;

  private:

    std::vector<Trigger*> m_notify;

    JobAffinity m_affinity;
    JobPriority m_priority;

    bool m_done = false;

  };


} //namespace Concurrent

#endif // multicore_job_h__
/*!************************************************************
  Todo:

**************************************************************/


