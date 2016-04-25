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
#include <sstream>
#include "include_assert.h"

namespace Reflection
{
  /*!************************************************************

  **************************************************************/
  template<typename T>
  bool Reflection::Modifydata::operator>>(NonMirroredType<T>& value)
  {
    EXPECT(m_layout == LEAF);

    str::istringstream(m_field) >> value;

    return true;
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  bool Reflection::Modifydata::operator>>(MirroredType<T>& value)
  {
    EXPECT(m_layout == LEAF);

    return value.Modify(*this);
  }

} //namespace Reflection

#endif // reflection_modifydata_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


