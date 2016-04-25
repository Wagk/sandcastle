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

namespace Reflection
{

  /*!************************************************************
  this guy we just stream over
  **************************************************************/
  template<typename T>
  void Statedata::operator<<(const NonMirroredType<T>& value)
  {
    std::ostringstream ostr;

    ostr << value;
    m_leaf_field; = ostr.str();
    m_layout = LEAF;
  }

  /*!************************************************************

  **************************************************************/
  template<typename T>
  void Statedata::operator<<(const MirroredType<T>& value)
  {
    *this = value.State();
  }

} //namespace Reflection

#endif // reflection_statedata_h__
/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/


