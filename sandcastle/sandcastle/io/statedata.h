/*!************************************************************
Created:	2016/04/20
Intent:

**************************************************************/
#ifndef reflection_statedata_h__
#define reflection_statedata_h__

#include <string>
#include <vector>
#include <map>

#include "propertydata.h"

namespace sandcastle::io::serial
{

  class state_data
  {
  public:

    state_data(data_layout_type layout = LEAF);
    state_data(size_t array_count);

    //nested accessors
    state_data& operator[](const std::string& name);
    const state_data& operator[](const std::string& name) const;

    //array accessors
    state_data& operator[](size_t index);
    const state_data& operator[](size_t index) const;
    void Pushback(const state_data& data);
    void Popback();

    size_t Size() const;
    data_layout_type LayoutType() const;

    //"getters"
    template<typename T>
    void operator<<(const mirrored_type<T>& value); //for types we can grab Propertydata from
    template<typename T>
    void operator<<(const non_mirrored_type<T>& value); //for types we need to call extraction operators on

  private:

    data_layout_type m_layout; //if true, we use `m_arrayfields`, false we use `m_subfields`

    std::string m_leaf_field;; //used only for leaf nodes to hold std::string data
    std::vector<state_data> m_array_field; std::map<std::string, state_data> m_struct_field; 
  };

} //namespace sandcastle::io::serial

#include "statedata.inl"

#endif
/*!************************************************************
  Todo:

**************************************************************/

