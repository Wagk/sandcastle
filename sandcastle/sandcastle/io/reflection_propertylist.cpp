/*!************************************************************
  Created	:	2016/04/19
  Note	:

**************************************************************/
#include "reflection_propertylist.h"

#include "include_assert.h"

namespace sandcastle::io::serial
{


  /*!************************************************************

  **************************************************************/
  propertylist::propertylist()
    : m_typename("")
    , m_arraycount(0)
    , m_defaultvalue("")
    , m_memberlists()
  {

  }

  /*!************************************************************

  **************************************************************/
  propertylist& propertylist::operator[](const std::string& name)
  {
    return m_memberlists[name];
  }

  /*!************************************************************

  **************************************************************/
  void propertylist::Swap(propertylist& rhs)
  {
    std::swap(m_typename, rhs.m_typename);
    std::swap(m_arraycount, rhs.m_arraycount);
    std::swap(m_memberlists, rhs.m_memberlists);
  }

  /*!************************************************************

  **************************************************************/
  bool propertylist::Validate() const
  {
    if (m_typename == "" || m_arraycount == 0)
      return false;

    for (const auto& elem : m_memberlists)
    {
      if (elem.first == "" || elem.second.Validate() == false)
        return false;
    }

    return true;
  }

  /*!************************************************************

  **************************************************************/
  std::string propertylist::PODstd::stringify(PODType type)
  {
    switch (type)
    {
    case BOOL:
      return "bool";
    case CHAR:
      return "char";
    case CHAR_16:
      return "char16";
    case CHAR_32:
      return "char32";
    case WCHAR:
      return "wchar";
    case SHORT:
      return "short";
    case INT:
      return "int";
    case LONG:
      return "long";
    case LONG_LONG:
      return "long long";
    case UNSIGNED_CHAR: 
      return "unsigned char";
    case UNSIGNED_SHORT:
      return "unsigned short";
    case UNSIGNED_INT:
      return "unsigned int";
    case UNSIGNED_LONG:
      return "unsigned long";
    case UNSIGNED_LONG_LONG:
      return "unsigned long long";
    case FLOAT:
      return "float";
    case DOUBLE:
      return "double";
    case LONG_DOUBLE:
      return "long double";
    }
    return "";
  }

  /*!************************************************************

  **************************************************************/
  propertylist& propertylist::operator=(const propertylist& rhs)
  {
    propertylist temp(rhs);
    temp.Swap(*this);

    return *this;
  }

} //namespace sandcastle::io::serial


/*!************************************************************
  Todo:

  References:

**************************************************************/
