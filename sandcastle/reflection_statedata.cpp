/*!************************************************************
  Created	:	2016/04/22
  Note	:

**************************************************************/
#include "reflection_statedata.h"

#include "include_assert.h"
#include "reflection_reflectable.h"

namespace Reflection
{


  /*!************************************************************

  **************************************************************/
  Statedata::Statedata(DataLayoutType layout /*= LEAF*/)
    : m_layout(layout)
    , m_leaf_field()
    , m_array_field()
    , m_struct_field()
  {

  }

  /*!************************************************************

  **************************************************************/
  Statedata::Statedata(size_t array_count)
    : m_layout(ARRAY)
    , m_leaf_field()
    , m_array_field(array_count)
    , m_struct_field()
  {

  }

  /*!************************************************************

  **************************************************************/
  Statedata& Statedata::operator[](const String& name)
  {
    EXPECT(m_layout == STRUCT);

    return m_struct_field[name];
  }

  /*!************************************************************

  **************************************************************/
  const Statedata& Statedata::operator[](const String& name) const
  {
    EXPECT(m_layout == STRUCT);

    return m_struct_field.at(name);
  }

  /*!************************************************************

  **************************************************************/
  Statedata& Statedata::operator[](size_t index)
  {
    EXPECT(m_layout == ARRAY);

    return m_array_field[index];
  }

  /*!************************************************************

  **************************************************************/
  const Statedata& Statedata::operator[](size_t index) const
  {
    EXPECT(m_layout == ARRAY);

    return m_array_field[index];
  }

  /*!************************************************************

  **************************************************************/
  void Statedata::Pushback(const Statedata& data)
  {
    EXPECT(m_layout == ARRAY);

    m_array_field.push_back(data);
  }

  /*!************************************************************

  **************************************************************/
  void Statedata::Popback()
  {
    EXPECT(m_layout == ARRAY);

    m_array_field.pop_back();
  }

  /*!************************************************************

  **************************************************************/
  size_t Statedata::Size() const
  {
    EXPECT(m_layout == ARRAY);

    return m_array_field.size();
  }

  /*!************************************************************

  **************************************************************/
  DataLayoutType Statedata::LayoutType() const
  {
    return m_layout;
  }

} //namespace Reflection


/*!************************************************************
  Todo:

  References:

**************************************************************/
