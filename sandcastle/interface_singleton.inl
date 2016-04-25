/*!************************************************************
	Created	:	2016/03/16
	Intent	:		
		
	Usage	:
		
	Note	:
		
**************************************************************/
#ifndef interface_singleton_inl__
#define interface_singleton_inl__

#include "interface_singleton.h"

namespace Interface
{
  template<typename T>
  T& Singleton::Get()
  {
    static T singleton;
    return singleton;
  }
}

#endif // interface_singleton_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


