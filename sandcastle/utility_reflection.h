/*!************************************************************
  Created:	2016/02/24
  Intent:
      REFLECTION

      To establish a way to generate some form of endJinn Intermediate Data Format (JIDF)
  Note:
      
      What I really want is some way to define a class such that I can use
      it to generate IDF data from objects on the stack and vice versa

**************************************************************/
#ifndef util_mirror_h__
#define util_mirror_h__

#include <map>
#include <vector>
#include <string>

#include <cstddef>

namespace Reflection
{

  /*
    We steal shamelessly from how JSON organizes its data, for our intermediate
    format
  */
  class DataFormatSpecifier
  {
  public:

    using StringType = std::string;
    using StructType = std::map<StringType, DataFormatSpecifier>;
    using ArrayType = std::vector<DataFormatSpecifier>;
    using BoolType = bool;
    using IntType = std::ptrdiff_t;
    using UintType = std::size_t;
    using RealType = double;

    template<typename T>
    void Specify(const T& type = T());

    DataFormatSpecifier& operator[](const std::string& key);  //for heterogeneous blocks
    DataFormatSpecifier& operator[](size_t index);            //if this is a homogeneous block

  private:

    enum LayoutType
    {
      BOOL_TYPE,
      INT_TYPE,
      UINT_TYPE,
      REAL_TYPE,
      STRING_TYPE,
      STRUCT_TYPE,
      ARRAY_TYPE
    };

    union Value
    {
      BoolType valbool;
      RealType valreal;
      IntType valint;
      UintType valuint;
      StringType valstring;
      ArrayType valarray;
      StructType valstruct;
    };

    LayoutType m_layout;
    Value m_value;

  };

  

} //namespace Reflection

#endif // mirror_h__
/*!************************************************************
  Todo:

  use case:

  template<>
  DataFormatSpecifier& operator<<(DataFormatSpecifier& dfs, )
  {
    DataFormatSpecifier dataformat;

    dataformat["m_int_1"].Specify<int>();
    dataformat["m_int_2"].Specify<int>(5.f);
    dataformat["m_a"].Specify<Vector<A>>();

    return dataformat;
  }

  Then somewhere else we get:

  IMPORT_FORMAT(Type)
  {
    Type object;


  }

  probably need function pointers or some other stuff if we
  want to modify just a single variable at runtime

  ------

  With Metadata, I think the holy grail would be:
  ```
    A obj;
    Metadata<A> meta;
    DataFormatSpecifier data(meta, obj);

    //or even better:

    DataFormatSpecifier data_a(obj); // and let the templated constructor figure out the metadata
  ```

**************************************************************/


