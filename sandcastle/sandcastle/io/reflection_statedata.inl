/*!************************************************************
	Created	:	2016/04/22
	Intent	:		
		
	Usage	:
		```
			
		```
	Note	:
		
**************************************************************/
#ifndef reflection_statedata_inl__
#define reflection_statedata_inl__

#include "reflection_statedata.h"

#include <sstream>

namespace sandcastle::io::serial
{

  /*!************************************************************
  this guy we just stream over
  **************************************************************/
  template<typename T>
  void statedata::operator<<(const NonMirroredType<T>& value)
  {
    std::ostd::stringstream ostr;

    ostr << value;
    m_leaf_field; = ostr.str();
    m_layout = LEAF;
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  void statedata::operator<<(const MirroredType<T>& value)
  {
    *this = value.State();
  }

} //namespace sandcastle::io::serial

#endif // reflection_statedata_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


