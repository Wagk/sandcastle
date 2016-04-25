/*!************************************************************
	Created	:	2016/03/13
	Intent	:		
		
	Usage	:
		
	Note	:
		Triggers are basically atomic counters wrapped up nicely
**************************************************************/
#ifndef multicore_trigger_h__
#define multicore_trigger_h__

#include <atomic>

namespace Concurrent
{

  class Trigger
  {
  public:

    Trigger(int count = 0);
    Trigger(const Trigger& rhs);

    void operator=(int setcount);
    void operator++();
    void operator--();
    bool operator==(int cmp);
    bool operator!=(int cmp);
    Trigger& operator=(const Trigger& rhs);

    /*!************************************************************
    	FullName :	Concurrent::Trigger::Done
    	Returns  :	bool, true if counter is 0, false otherwise
    	Brief    :		
    			
    	Expect   :		
    	Ensure   :
    	Usage    :		
    **************************************************************/
    bool Done() const;

  private:

    std::atomic<int> m_counter;

  };

} //namespace Concurrent

#endif // multicore_trigger_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


