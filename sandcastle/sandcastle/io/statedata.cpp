/*!************************************************************
  Created	:	2016/04/22
  Note	:

**************************************************************/
#include "statedata.h"

#include <cassert>
#include "reflectable.h"

namespace sandcastle::io::serial
{

  /*!************************************************************

  **************************************************************/
  state_data::state_data(data_layout_type layout /*= LEAF*/)
    : m_layout(layout)
    , m_leaf_field()
    , m_array_field()
    , m_struct_field()
  {

  }

  /*!************************************************************

  **************************************************************/
  state_data::state_data(size_t array_count)
    : m_layout(ARRAY)
    , m_leaf_field()
    , m_array_field(array_count)
    , m_struct_field()
  {

  }

  /*!************************************************************

  **************************************************************/
  state_data& state_data::operator[](const std::string& name)
  {
    assert(m_layout == STRUCT);

    return m_struct_field[name];
  }

  /*!************************************************************

  **************************************************************/
  const state_data& state_data::operator[](const std::string& name) const
  {
    assert(m_layout == STRUCT);

    return m_struct_field.at(name);
  }

  /*!************************************************************

  **************************************************************/
  state_data& state_data::operator[](size_t index)
  {
    assert(m_layout == ARRAY);

    return m_array_field[index];
  }

  /*!************************************************************

  **************************************************************/
  const state_data& state_data::operator[](size_t index) const
  {
    assert(m_layout == ARRAY);

    return m_array_field[index];
  }

  /*!************************************************************

  **************************************************************/
  void state_data::push_back(const state_data& data)
  {
    assert(m_layout == ARRAY);

    m_array_field.push_back(data);
  }

  /*!************************************************************

  **************************************************************/
  void state_data::pop_back()
  {
    assert(m_layout == ARRAY);

    m_array_field.pop_back();
  }

  /*!************************************************************

  **************************************************************/
  size_t state_data::size() const
  {
    assert(m_layout == ARRAY);

    return m_array_field.size();
  }

  /*!************************************************************

  **************************************************************/
  data_layout_type state_data::layout_type() const
  {
    return m_layout;
  }

} //namespace sandcastle::io::serial


/*!************************************************************
  Todo:

  References:

**************************************************************/
