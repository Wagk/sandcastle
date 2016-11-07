#ifndef math_vector_inl__
#define math_vector_inl__

#include "vec.h"

namespace sandcastle::math
{

	template<unsigned D, typename T /*= float*/>
	vector<D, T>::vector(const std::initializer_list<T>& list)
	{
		size_t i = 0;
		for (const auto& elem : list)
		{
			m[i] = elem;
			++i;
		}
	}

	template<unsigned D, typename T /*= float*/>
	const T& vector<D, T>::operator[](size_t index) const
	{
		return m[index];
	}

	template<unsigned D, typename T /*= float*/>
	T& vector<D, T>::operator[](size_t index)
	{
		return m[index];
	}

	template<unsigned D, typename T /*= float*/>
	vector<D, T>::vector()
		: m{ 0 }
	{

	}

	template<unsigned D, typename T, typename ReturnType /*= T*/>
	ReturnType operator*(const vector<D, T>& v1, const vector<D, T>& v2)
	{
		ReturnType ret{};

		for (decltype(D) i = 0; i < D; ++i)
		{
			ret += (v1[i] * v2[i]);
		}

		return ret;
	}

	template<unsigned D, typename T, typename InputT>
	vector<D, T>
		operator*(const vector<D, T>& vec, InputT scale)
	{
		vector<D, T> temp = vec;
		temp *= scale;
		return temp;
	}

	template<unsigned D, typename T, typename InputT>
	vector<D, T> operator*(InputT scale, const vector<D, T>& vec)
	{
		return vec * scale;
	}

	template<unsigned D, typename T, typename InputT>
	vector<D, T>& operator*=(vector<D, T>& vec, InputT scale)
	{
		for (size_t i = 0; i < D; ++i)
		{
			vec[i] *= scale;
		}

		return vec;
	}

	template<unsigned D, typename T>
	std::ostream& operator<<(std::ostream& os, const vector<D, T>& vec)
	{
		os << "[ ";
		for (size_t i = 0; i < D; ++i)
		{
			os << vec[i] << " ";
		}
		os << "]";

		return os;
	}

}

#endif