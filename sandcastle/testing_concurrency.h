/*!************************************************************
	Created	:	2016/03/24
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef testing_concurrency_h__
#define testing_concurrency_h__

#include "include_std.h"
#include "concurrent_job.h"

namespace Testing
{

  struct CounterJob : public Concurrent::Job
  {
    CounterJob();
    virtual void JobDefinition() override;
    
    static Mutex s_mutex;
    static size_t s_counter;
  };

  struct TestJob : public Concurrent::Job 
  {
    TestJob();
    virtual void JobDefinition() override;
  };

} //namespace Testing

#endif // testing_concurrency_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


