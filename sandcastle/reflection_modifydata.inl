/*!************************************************************
	Created	:	2016/04/22
	Intent	:		
		
	Usage	:
		```
			
		```
	Note	:
		
**************************************************************/
#ifndef reflection_modifydata_inl__
#define reflection_modifydata_inl__

#include "reflection_modifydata.h"

namespace Reflection
{
  /*!************************************************************

  **************************************************************/
  template<typename T>
  bool Reflection::Modifydata::operator>>(NonMirroredType<T>& value)
  {
    return false;
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  bool Reflection::Modifydata::operator>>(MirroredType<T>& value)
  {
    return false;
  }

} //namespace Reflection

#endif // reflection_modifydata_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


