/*!************************************************************
  Created	:	2016/04/22
  Note	:

**************************************************************/
#include "reflection_statedata.h"

#include "include_assert.h"
#include "reflection_reflectable.h"

namespace sandcastle::io::serial
{


  /*!************************************************************

  **************************************************************/
  statedata::statedata(DataLayoutType layout /*= LEAF*/)
    : m_layout(layout)
    , m_leaf_field()
    , m_array_field()
    , m_struct_field()
  {

  }

  /*!************************************************************

  **************************************************************/
  statedata::statedata(size_t array_count)
    : m_layout(ARRAY)
    , m_leaf_field()
    , m_array_field(array_count)
    , m_struct_field()
  {

  }

  /*!************************************************************

  **************************************************************/
  statedata& statedata::operator[](const std::string& name)
  {
    assert(m_layout == STRUCT);

    return m_struct_field[name];
  }

  /*!************************************************************

  **************************************************************/
  const statedata& statedata::operator[](const std::string& name) const
  {
    assert(m_layout == STRUCT);

    return m_struct_field.at(name);
  }

  /*!************************************************************

  **************************************************************/
  statedata& statedata::operator[](size_t index)
  {
    assert(m_layout == ARRAY);

    return m_array_field[index];
  }

  /*!************************************************************

  **************************************************************/
  const statedata& statedata::operator[](size_t index) const
  {
    assert(m_layout == ARRAY);

    return m_array_field[index];
  }

  /*!************************************************************

  **************************************************************/
  void statedata::Pushback(const statedata& data)
  {
    assert(m_layout == ARRAY);

    m_array_field.push_back(data);
  }

  /*!************************************************************

  **************************************************************/
  void statedata::Popback()
  {
    assert(m_layout == ARRAY);

    m_array_field.pop_back();
  }

  /*!************************************************************

  **************************************************************/
  size_t statedata::Size() const
  {
    assert(m_layout == ARRAY);

    return m_array_field.size();
  }

  /*!************************************************************

  **************************************************************/
  DataLayoutType statedata::LayoutType() const
  {
    return m_layout;
  }

} //namespace sandcastle::io::serial


/*!************************************************************
  Todo:

  References:

**************************************************************/
