/*!************************************************************
	Created	:	2016/04/05
	Intent	:		
		Create a mutex that satisfies `basiclockable` and `lockable`
    std requirements, that doesn't block, *but works jobs from
    the scheduler while waiting*

    [Lockable](http://en.cppreference.com/w/cpp/concept/Lockable)
    [BasicLockable](http://en.cppreference.com/w/cpp/concept/BasicLockable)

	Usage	:
		
	Note	:
		
    2 hours later we conclude that just using std::mutex is faster
    and doesnt somehow cause a stackoverflow (no seriously, I have
    no idea why too, when we use this we suddenly get a bad_alloc
    in the retire list in the hazard zone.

**************************************************************/
#ifndef concurrent_mutex_h__
#define concurrent_mutex_h__

#include <mutex>

namespace Concurrent
{

  //we're kinda downgrading, since what we are doing is 
  //re purposing the try_lock mechanism for our own nefarious ends
  class WorkerMutex
  {
  public:

    WorkerMutex();

    /*!************************************************************
    	FullName :	Concurrent::WorkerMutex<Mutex>::lock
    	Returns  :	void
    	Brief    :		
    			Continually tries to lock, and everytime it fails to, 
          works a single job before trying again
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void lock();

    /*!************************************************************
    	FullName :	Concurrent::WorkerMutex<Mutex>::unlock
    	Returns  :	void
    	Brief    :		
    			unlocks the mutex
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    void unlock();

    /*!************************************************************
    	FullName :	Concurrent::WorkerMutex<Mutex>::try_lock
    	Returns  :	bool, true if the lock is attained, false otherwise
    	Brief    :		
    			tries to lock it once, and returns the result.,
          Does not attempt to perform work, use with caution and try
          not to deadlock yourself
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    bool try_lock();

  private:

    std::mutex m_mutex; //of course we still have a mutex

  };

} //namespace Concurrent


#endif // concurrent_mutex_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


