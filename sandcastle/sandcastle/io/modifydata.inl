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

#include "modifydata.h"
#include <sstream>

namespace sandcastle::io::serial
{
  /*!************************************************************

  **************************************************************/
  template<typename T>
  bool sandcastle::io::serial::modify_data::operator>>(non_mirrored_type<T>& value)
  {
    assert(m_layout == LEAF);

    str::istd::stringstream(m_field) >> value;

    return true;
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  bool sandcastle::io::serial::modify_data::operator>>(mirrored_type<T>& value)
  {
    assert(m_layout == LEAF);

    return value.Modify(*this);
  }

} //namespace sandcastle::io::serial

#endif // reflection_modifydata_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


