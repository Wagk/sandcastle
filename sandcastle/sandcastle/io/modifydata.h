/*!************************************************************
Created:	2016/04/20
Intent:

**************************************************************/
#ifndef reflection_updatedata_h__
#define reflection_updatedata_h__

#include <vector>
#include <map>

#include "propertydata.h"

namespace sandcastle::io::serial
{

  class modify_data
  {
  public:

    //nested accessors
    modify_data& operator[](const std::string& name);
    const modify_data& operator[](const std::string& name) const;
    //array accessors
    modify_data& operator[](size_t index);
    const modify_data& operator[](size_t index) const;

    //"setters"
    template<typename T>
    bool operator>>(mirrored_type<T>& value); //for types we can pass Propertydata into
    template<typename T>
    bool operator>>(non_mirrored_type<T>& value); //for types we want to call their insertion operator

    /*!************************************************************
    FullName	:sandcastle::io::serial::Propertydata::ToModify
    Returns		:bool, true if the member contains data to be modified
                     false otherwise
    Parameter	:const std::string & name
    Brief		:
     
    Use			:
    ```
      
    ```
    **************************************************************/
    bool to_modify(const std::string& name) const;

  private:

    bool m_is_array; //if true, we use `m_arrayfields`, false we use `m_subfields`\

    using modify_info = std::pair<bool, modify_data>;

    data_layout_type m_layout = LEAF;

    bool m_modify;
    std::string m_field; //used only for leaf nodes to restore data
    std::vector<modify_info> m_arrayfields;
    std::map<std::string, modify_info> m_subfields;

  };

  

} //namespace sandcastle::io::serial

#include "modifydata.inl"

#endif
/*!************************************************************
  Todo:

**************************************************************/

