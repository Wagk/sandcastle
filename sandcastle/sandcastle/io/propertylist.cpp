/*!************************************************************
  Created	:	2016/04/19
  Note	:

**************************************************************/
#include "propertylist.h"
#include <string>

namespace sandcastle::io::serial
{


  /*!************************************************************

  **************************************************************/
  property_list::property_list()
    : m_typename("")
    , m_arraycount(0)
    , m_defaultvalue("")
    , m_memberlists()
  {

  }

  /*!************************************************************

  **************************************************************/
  property_list& property_list::operator[](const std::string& name)
  {
    return m_memberlists[name];
  }

  /*!************************************************************

  **************************************************************/
  void property_list::Swap(property_list& rhs)
  {
    std::swap(m_typename, rhs.m_typename);
    std::swap(m_arraycount, rhs.m_arraycount);
    std::swap(m_memberlists, rhs.m_memberlists);
  }

  /*!************************************************************

  **************************************************************/
  bool property_list::Validate() const
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
  std::string property_list::PODStringify(PODType type)
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
  property_list& property_list::operator=(const property_list& rhs)
  {
    property_list temp(rhs);
    temp.Swap(*this);

    return *this;
  }

} //namespace sandcastle::io::serial


/*!************************************************************
  Todo:

  References:

**************************************************************/
