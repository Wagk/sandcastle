/*!************************************************************
	Created	:	2016/03/25
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef concurrent_light_job_h__
#define concurrent_light_job_h__

#include "concurrent_job.h"
#include "include_std.h"

#include "export_macros.h"

namespace Concurrent
{

  class LightJob : public Job
  {
  public:

    using FuncType = void(void);

    SANDCASTLE_API LightJob(const Function<FuncType>& function,
      JobAffinity affinity = AFFINITY_WORKER);

  private:

    virtual void JobDefinition() override;

    Function<FuncType> m_functor;

  };

} //namespace Concurrency


#endif // concurrent_light_job_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


