/*!************************************************************
	Created	:	2016/04/22
	Note	:
		
**************************************************************/
#include "modifydata.h"

#include <cassert>
#include <string>

namespace sandcastle::io::serial
{

  /*!************************************************************

  **************************************************************/
  modify_data& modify_data::operator[](const std::string& name)
  {
    assert(m_layout == STRUCT);

    return m_subfields[name].second;
  }

  /*!************************************************************

  **************************************************************/
  const modify_data& modify_data::operator[](const std::string& name) const
  {
    assert(m_layout == STRUCT);

    return m_subfields.at(name).second;
  }

  /*!************************************************************

  **************************************************************/
  modify_data& modify_data::operator[](size_t index)
  {
    assert(m_layout == STRUCT && index < m_arrayfields.size());

    return m_arrayfields[index].second;
  }

  /*!************************************************************

  **************************************************************/
  const modify_data& modify_data::operator[](size_t index) const
  {
    assert(m_layout == STRUCT && index < m_arrayfields.size());

    return m_arrayfields[index].second;
  }

  /*!************************************************************

  **************************************************************/
  bool modify_data::to_modify(const std::string& name) const
  {
    return m_modify;
  }

} //namespace sandcastle::io::serial


/*!************************************************************
	Todo:
			
	References:
		
**************************************************************/
