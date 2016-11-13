#ifndef io_serial_h__
#define io_serial_h__

#include "value.h"

namespace sandcastle::io::serial
{

	class interface
	{
	public:

		virtual value data() const = 0;
		virtual void data(const value&) = 0;

	};
	
}

#endif