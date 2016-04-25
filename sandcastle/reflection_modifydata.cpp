/*!************************************************************
	Created	:	2016/04/22
	Note	:
		
**************************************************************/
#include "reflection_modifydata.h"

#include "include_assert.h"

namespace Reflection
{

  /*!************************************************************

  **************************************************************/
  Modifydata& Modifydata::operator[](const String& name)
  {
    EXPECT(m_layout == STRUCT);

    return m_subfields[name].second;
  }

  /*!************************************************************

  **************************************************************/
  const Modifydata& Modifydata::operator[](const String& name) const
  {
    EXPECT(m_layout == STRUCT);

    return m_subfields.at(name).second;
  }

  /*!************************************************************

  **************************************************************/
  Modifydata& Modifydata::operator[](size_t index)
  {
    EXPECT(m_layout == STRUCT && index < m_arrayfields.size());

    return m_arrayfields[index].second;
  }

  /*!************************************************************

  **************************************************************/
  const Modifydata& Modifydata::operator[](size_t index) const
  {
    EXPECT(m_layout == STRUCT && index < m_arrayfields.size());

    return m_arrayfields[index].second;
  }

  /*!************************************************************

  **************************************************************/
  bool Modifydata::ToModify(const String& name) const
  {
    return m_modify;
  }

} //namespace Reflection


/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/
