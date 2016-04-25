/*!************************************************************
  Created	:	2016/03/13
  Intent	:

  Usage	:

  Note	:

**************************************************************/
#ifndef concurrent_dispatcher_h__
#define concurrent_dispatcher_h__

#include "concurrent_job.h"
#include "concurrent_trigger.h"
#include "include_std.h"

namespace Concurrent
{

  /*
    We'll eventually decide if we should

    MAKE THIS A POLICY CLASS?

    Dispatcher<Unmanaged> //simple dispatcher, no management of jobs
    DIspatcher<Manages<T>> //

  */

  //when the dispatcher is fully policy-ready, we'll typedef it and make
  //the change
  class SimpleDispatcher : public Job
  {
  public:

    //mind the affinities
    SimpleDispatcher(const Vector<Job*>& jobs = Vector<Job*>());
    SimpleDispatcher(const SimpleDispatcher& rhs);

    //remember that this dispatcher is also a Job, meaning it has
    //its own run and schedule functions

    /*!************************************************************
    	FullName :	Concurrent::SimpleDispatcher::Insert
    	Returns  :	void
    	Parameter:	Job * job
    	Brief    :		
    			Adds a job to the block, to be dispatched
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void Insert(Job* job);

    /*!************************************************************
    	FullName :	Concurrent::SimpleDispatcher::AssignBlock
    	Returns  :	void
    	Parameter:	const Vector<Job * > & jobs
    	Brief    :		
    			
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void AssignBlock(const Vector<Job*>& jobs);

    /*!************************************************************
    	FullName :	Concurrent::SimpleDispatcher::Clear
    	Returns  :	void
    	Brief    :		
    			Removes all jobs from the block. DOES NOT DELETE
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void Clear();

    SimpleDispatcher& operator=(const SimpleDispatcher& rhs);

  private:

    /*!************************************************************
    FullName :	Concurrent::SimpleDispatcher::Dispatch
    Returns  :	void
    Brief    :
    Dispatches all jobs currently within the block
    Expect   :
    Ensure   :
    Usage    :
    **************************************************************/
    void Dispatch();

    /*!************************************************************
    FullName :	Concurrent::SimpleDispatcher::Wait
    Returns  :	void
    Brief    :
    Wait for all dispatched jobs to return. Blocking
    Expect   :
    Ensure   :
    Usage    :
    **************************************************************/
    void Wait();

    virtual void JobDefinition() override;

    bool          m_dispatched;
    Vector<Job*>  m_jobs;
    Trigger       m_trigger;

  };

  /*
    Experimenting with policy classes. Want to make a dispatcher that 
    can be fit with modular things
  */
  template<template<typename> class MemoryManagementPolicy>
  class Dispatcher : public MemoryManagementPolicy
  {
  public:

    //MemoryManagementPolicy interface right here

    void Dispatch();

  private:

    bool m_dispatched = false;
    Trigger m_trigger;

  };

  template<typename JobType = Job>
  class Unmanaged
  {
    //this class will be mostly about pointers, since we won't delete anything
  };

  template<typename JobType = Job>
  class UnmanagedDemo
  {

  };

  template<typename JobType>
  class Managed
  {
  public:

    //this class will be mostly about concrete objects, since the lifespan
    //of the JobTypes will be held within this Dispatcher

  private:


  };


} //namespace Concurrent

#include "concurrent_dispatcher.inl"

#endif // concurrent_dispatcher_h__
/*!************************************************************
  Todo:

  References:

**************************************************************/


