/*!************************************************************
	Created	:	2016/04/22
	Note	:
		
**************************************************************/
#include "reflection_modifydata.h"

#include <cassert>
#include <std::string>

namespace sandcastle::io::serial
{

  /*!************************************************************

  **************************************************************/
  Modifydata& Modifydata::operator[](const std::std::string& name)
  {
    assert(m_layout == STRUCT);

    return m_subfields[name].second;
  }

  /*!************************************************************

  **************************************************************/
  const Modifydata& Modifydata::operator[](const std::std::string& name) const
  {
    assert(m_layout == STRUCT);

    return m_subfields.at(name).second;
  }

  /*!************************************************************

  **************************************************************/
  Modifydata& Modifydata::operator[](size_t index)
  {
    assert(m_layout == STRUCT && index < m_arrayfields.size());

    return m_arrayfields[index].second;
  }

  /*!************************************************************

  **************************************************************/
  const Modifydata& Modifydata::operator[](size_t index) const
  {
    assert(m_layout == STRUCT && index < m_arrayfields.size());

    return m_arrayfields[index].second;
  }

  /*!************************************************************

  **************************************************************/
  bool Modifydata::ToModify(const std::std::string& name) const
  {
    return m_modify;
  }

} //namespace sandcastle::io::serial


/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/
