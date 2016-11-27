/*!************************************************************
  Created	:	2016/04/19
  Intent	:

  Usage	:
    ```

      struct A : serializable
      {
        int m_int;
        float m_float;
      };

      struct B : serializable
      {
        A m_a; // we need to throw a propertydata inside
        bool m_bool[3];
        std::vector m_vec; //not reflectable, so we use std::string operator
      };

      Propertydata data; //lets say it's already loaded with the std::string goods

      //**within the virtual function**, you would do something like this:

      data["m_bool"][0] >> m_bool[0];
      data["m_bool"][1] >> m_bool[1];
      data["m_bool"][2] >> m_bool[2];
      data["m_vec"] >> m_vec; //need someway to distinguish between the two
      data["m_a"] >> m_a; //this tosses a sub-propertydata for A to manage

      //INSIDE A
      sub_data["m_int"] >> m_int;
      sub_data["m_float"] >> m_float;

    ```
    What about `m_data["m_arr"][3]["m_val"].....;`

  Note	:
    Don't forget this struct ACTUALLY CONTAINS std::string DATA
    to manipulate

    we also need to handle arrays somehow
**************************************************************/
#ifndef reflection_propertydata_h__
#define reflection_propertydata_h__

#include <type_traits>

namespace sandcastle::io::serial
{

  class serializable;

  enum data_layout_type
  {
    STRUCT,
    ARRAY,
    LEAF
  };

  //helper types
  template<typename T>
  using mirrored_type = typename std::enable_if<std::is_base_of<serializable, T>::value == true, T>::type;
  template<typename T>
  using non_mirrored_type = typename std::enable_if<std::is_base_of<serializable, T>::value == false, T>::type;


} //namespace sandcastle::io::serial

#include "propertydata.inl"

#endif // reflection_propertydata_h__
/*!************************************************************
  Todo:

  References:

**************************************************************/


