#include "counter.h"

namespace sandcastle
{
	namespace concurrency
	{
		counter::counter(int i)
			: _ctr(i)
		{

		}

		counter::counter(const counter & rhs)
			: _ctr(rhs._ctr.load())
		{
			
		}

		counter & counter::operator=(int i)
		{
			_ctr.store(i);

			return *this;
		}

		counter & counter::operator++()
		{
			++_ctr;

			return *this;
		}

		counter & counter::operator--()
		{
			--_ctr;
			
			return *this;
		}

		counter::operator int() const
		{
			return _ctr.load();
		}

		counter::operator bool() const
		{
			return _ctr.load() != 0;
		}

		bool counter::operator==(const counter & rhs) const
		{
			return rhs._ctr.load() == _ctr.load();
		}

		bool counter::operator!=(const counter & rhs) const
		{
			return rhs._ctr.load() != _ctr.load();
		}
	}
}