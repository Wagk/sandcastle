#ifndef io_serial_h__
#define io_serial_h__

#include "value.h"

namespace sandcastle::io::serial
{

    template<typename T>
	class serializable
	{
	public:

        virtual void operator<<(serial::value);
        virtual void operator>>(serial::value);

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
