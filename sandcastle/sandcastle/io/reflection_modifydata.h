/*!************************************************************
Created:	2016/04/20
Intent:

**************************************************************/
#ifndef reflection_updatedata_h__
#define reflection_updatedata_h__

#include "reflection_propertydata.h"

namespace sandcastle::io::serial
{

  class Modifydata
  {
  public:

    //nested accessors
    Modifydata& operator[](const std::string& name);
    const Modifydata& operator[](const std::string& name) const;
    //array accessors
    Modifydata& operator[](size_t index);
    const Modifydata& operator[](size_t index) const;

    //"setters"
    template<typename T>
    bool operator>>(MirroredType<T>& value); //for types we can pass Propertydata into
    template<typename T>
    bool operator>>(NonMirroredType<T>& value); //for types we want to call their insertion operator

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
    bool ToModify(const std::string& name) const;

  private:

    bool m_is_array; //if true, we use `m_arrayfields`, false we use `m_subfields`\

    using Modifyinfo = Pair<bool, Modifydata>;

    DataLayoutType m_layout = LEAF;

    bool m_modify;
    std::string m_field; //used only for leaf nodes to restore data
    std::vector<Modifyinfo> m_arrayfields;
    Map<std::string, Modifyinfo> m_subfields;

  };

  

} //namespace sandcastle::io::serial

#include "reflection_modifydata.inl"

#endif
/*!************************************************************
  Todo:

**************************************************************/

