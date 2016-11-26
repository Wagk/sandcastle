/*!************************************************************
Created:	2016/04/20
Intent:

**************************************************************/
#ifndef reflection_statedata_h__
#define reflection_statedata_h__

#include "reflection_propertydata.h"

namespace sandcastle::io::serial
{

  class statedata
  {
  public:

    statedata(DataLayoutType layout = LEAF);
    statedata(size_t array_count);

    //nested accessors
    statedata& operator[](const std::string& name);
    const statedata& operator[](const std::string& name) const;

    //array accessors
    statedata& operator[](size_t index);
    const statedata& operator[](size_t index) const;
    void Pushback(const statedata& data);
    void Popback();

    size_t Size() const;
    DataLayoutType LayoutType() const;

    //"getters"
    template<typename T>
    void operator<<(const MirroredType<T>& value); //for types we can grab Propertydata from
    template<typename T>
    void operator<<(const NonMirroredType<T>& value); //for types we need to call extraction operators on

  private:

    DataLayoutType m_layout; //if true, we use `m_arrayfields`, false we use `m_subfields`

    std::string m_leaf_field;; //used only for leaf nodes to hold std::string data
    std::vector<statedata> m_array_field;
    Map<std::string, statedata> m_struct_field;

  };

} //namespace sandcastle::io::serial

#include "reflection_statedata.inl"

#endif
/*!************************************************************
  Todo:

**************************************************************/

