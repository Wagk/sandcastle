#include "interface_singleton.inl"
/*!************************************************************
	Created	:	2016/03/16
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef interface_singleton_h__
#define interface_singleton_h__

namespace Interface
{

  class Singleton
  {
  public:

    template<typename T>
    static T& Get();

  private:


  };

} //namespace Interface

#include "interface_singleton.inl"

#endif // interface_singleton_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


