/*!************************************************************
  Created:	2016/02/24
  Intent:
      we will eventually add more serialization formats.
      in fact, this is probably where it all starts
  Note:
      The macros are necessary evils. At least this method of
      implementation would be easy to remove/adjust whenever
      the need calls for it (hopefully sometime in the future)

      I like to think this is a good example of reducing
      interdependencies, but time will tell

      **NOTE**
        filling out the template declarations will cause SFINAE
        to fail and hence require us to declare our serialization
        functions. This is a bad thing. Hence the stream operators
        must NEVER have a definition (for the templates anyway)

      **NOTE**
        don't forget the `template<>` for each individual class
        when filling them out

**************************************************************/
#ifndef util_serial_h__
#define util_serial_h__

#include "external/json/json/json.h"

namespace Utility
{
  namespace Serial
  {

    using JsonFormat = Json::Value;
    enum JsonLayout
    {
      ARRAY = Json::arrayValue,
      STRUCT = Json::objectValue
    };

    void JsonUnitTest();

  } //namespace serial
} //namespace util

/*!************************************************************
  FullName:	Serial::operator<<
  Returns:	Json::Value&
  Parameter:	Json::Value & file
  Parameter:	const T & data
  Brief:
        use case:

        obj2 << jsondat << obj;

  Assumes:
  Consider:
  Note:
**************************************************************/
template<typename T>
Utility::Serial::JsonFormat&
operator<<(Utility::Serial::JsonFormat& json, const T& value);

/*!************************************************************
  FullName:	Serial::operator>>
  Returns:	T&
  Parameter:	const Json::Value & data
  Parameter:	T & object
  Brief:

  Assumes:
  Consider:
  Note:
**************************************************************/
template<typename T>
T& operator>>(const Utility::Serial::JsonFormat& json, T& value);


#endif // serial_h__
/*!************************************************************
  Todo:

**************************************************************/


