/*!************************************************************
  Created	:	2016/04/19
  Intent	:

  Usage	:
    ```

      struct A
      {
        int m_int;
        float m_float;
      };

      propertylist a_props;

      a_props["m_int"] = propertylist(INT); //or something
      a_props["m_float"] = propertylist(FLOAT);

      struct B
      {
        A m_a;
        bool m_bool[6];
      };

      propertylist b_props;

      b_props["m_bool"] = propertylist(BOOL, 6);
      b_props["m_a"] = a_props; //get it from A's virtual function, if it's reflectable
      //alternatively
      b_props["m_a"] = b.m_a.Properties();

    ```
  Note	:

**************************************************************/
#ifndef reflection_propertylist_h__
#define reflection_propertylist_h__

#include "propertydata.h"
#include <type_traits>

#include <map>

namespace sandcastle::io::serial
{

  enum PODType //we can't serialize/meaningfully modify pointers/references via std::strings so we ignore them
  {
    BOOL,
    CHAR,
    CHAR_16,
    CHAR_32,
    WCHAR,
    SHORT,
    INT,
    LONG,
    LONG_LONG,
    UNSIGNED_CHAR,
    UNSIGNED_SHORT,
    UNSIGNED_INT,
    UNSIGNED_LONG,
    UNSIGNED_LONG_LONG,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE
  };

  //property list
  class property_list
  {
  public:

    template<typename T>
    using trivial_type = typename std::enable_if < 
      std::is_fundamental<T>::value == true &&
      std::is_void<T>::value == false &&
      std::is_null_pointer<T>::value == false, T > ::type;
    template<typename T>
    using non_trivial_type = typename std::enable_if <
      std::is_fundamental<T>::value == false ||
      std::is_void<T>::value == true ||
      std::is_null_pointer<T>::value == true, T > ::type;

    property_list();
    //template<typename T>
    //propertylist(PODType type, unsigned count = 1, const TrivialType<T>& defaultval = T());
    template<typename T>
    property_list(const std::string& typestring, unsigned count = 1, const non_trivial_type<T>& defaultval = T());

    property_list& operator=(const property_list& rhs);
    property_list& operator[](const std::string& name);

    void Swap(property_list& rhs);
    /*!************************************************************
      FullName :	sandcastle::io::serial::propertylist::Validate
      Returns  :	bool, true if the propertylist and all its sublists are valid
                        false otherwise
      Brief    :

      Usage    :
      ```

      ```
    **************************************************************/
    bool Validate() const; //checks for empty std::strings or illegal values

  private:

    std::string PODStringify(PODType type);

    data_layout_type m_type;

    std::string m_typename;
    unsigned m_arraycount; //is it an array?
    std::string m_defaultvalue;

    std::map<std::string, property_list> m_memberlists;

  };

} //namespace sandcastle::io::serial

#include "propertylist.inl"

#endif // reflection_propertylist_h__
/*!************************************************************
  Todo:

  References:

**************************************************************/


