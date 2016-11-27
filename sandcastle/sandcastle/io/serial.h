#ifndef io_serial_h__
#define io_serial_h__

#include "value.h"
#include <json\json.h>

#include <string>

namespace sandcastle::io::serial
{

	using namespace Json;
	using json_data = Json::Value;

    template<typename T>
	class json
	{
	public:

        virtual json_data& operator<<(json_data&) = 0;
        virtual json_data& operator>>(json_data&) = 0;

	};

	class serializable
	{
	public:



	private:
	};




	
    /*
     *  A a;
     *  a >> value >> json;
     *  a >> value >> son;
     *
     *  class A : serializable<A>
     *  {
     *
     *  };
     *
     * */
}

#endif
