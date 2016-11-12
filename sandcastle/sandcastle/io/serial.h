#ifndef io_serial_h__
#define io_serial_h__

namespace sandcastle::io::serial
{

	class value;

	class interface
	{
	public:

		virtual value values() = 0;
		virtual void values(const value&) = 0;

	};
	
	class value
	{
	public:

	private:
	};

}

#endif