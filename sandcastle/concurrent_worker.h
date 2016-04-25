/*!************************************************************
	Created	:	2016/03/05
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef multicore_worker_h__
#define multicore_worker_h__

#include "concurrent_thread.h"
#include "concurrent_job.h"
#include "concurrent_scheduler.h"

namespace Concurrent
{

  /*!************************************************************
  	FullName :	Concurrent::WorkSingleJob
  	Returns  :	void
  	Brief    :		
  			
  	Expect   :		
  	Ensure   :
  	Usage    :		
  **************************************************************/
  void WorkSingleJob();
  /*!************************************************************
  	FullName :	Concurrent::WorkerThread
  	Returns  :	void
  	Parameter:	ThreadInitInfo info
  	Brief    :		

  	Expect   :		
  	Ensure   :
  	Usage    :		
  **************************************************************/
  void WorkerThread(ThreadInitInfo info); 

} //namespace Concurrent

#endif // multicore_worker_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


