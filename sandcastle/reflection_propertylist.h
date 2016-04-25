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

      Propertylist a_props;

      a_props["m_int"] = Propertylist(INT); //or something
      a_props["m_float"] = Propertylist(FLOAT);

      struct B
      {
        A m_a;
        bool m_bool[6];
      };

      Propertylist b_props;

      b_props["m_bool"] = Propertylist(BOOL, 6);
      b_props["m_a"] = a_props; //get it from A's virtual function, if it's reflectable
      //alternatively
      b_props["m_a"] = b.m_a.Properties();

    ```
  Note	:

**************************************************************/
#ifndef reflection_propertylist_h__
#define reflection_propertylist_h__

#include "include_std.h"
#include "reflection_propertydata.h"
#include <type_traits>

namespace Reflection
{

  enum PODType //we can't serialize/meaningfully modify pointers/references via strings so we ignore them
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
  class Propertylist
  {
  public:

    template<typename T>
    using TrivialType = typename std::enable_if < 
      std::is_fundamental<T>::value == true &&
      std::is_void<T>::value == false &&
      std::is_null_pointer<T>::value == false, T > ::type;
    template<typename T>
    using NonTrivialType = typename std::enable_if <
      std::is_fundamental<T>::value == false ||
      std::is_void<T>::value == true ||
      std::is_null_pointer<T>::value == true, T > ::type;

    Propertylist();
    //template<typename T>
    //Propertylist(PODType type, unsigned count = 1, const TrivialType<T>& defaultval = T());
    template<typename T>
    Propertylist(const String& type_string, unsigned count = 1, const NonTrivialType<T>& defaultval = T());

    Propertylist& operator=(const Propertylist& rhs);
    Propertylist& operator[](const String& name);

    void Swap(Propertylist& rhs);
    /*!************************************************************
      FullName :	Reflection::Propertylist::Validate
      Returns  :	bool, true if the Propertylist and all its sublists are valid
                        false otherwise
      Brief    :

      Usage    :
      ```

      ```
    **************************************************************/
    bool Validate() const; //checks for empty strings or illegal values

  private:

    String PODStringify(PODType type);

    DataLayoutType m_type;

    String m_typename;
    unsigned m_arraycount; //is it an array?
    String m_defaultvalue;

    Map<String, Propertylist> m_memberlists;

  };

} //namespace Reflection

#include "reflection_propertylist.inl"

#endif // reflection_propertylist_h__
/*!************************************************************
  Todo:

  References:

**************************************************************/


