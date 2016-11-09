#ifndef math_matrix_inl__
#define math_matrix_inl__

#include <array>
#include <type_traits>
#include "matrix.h"

namespace sandcastle::math
{

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	matrix<R, C, T>::matrix(const std::initializer_list<std::initializer_list<T>>& list)
		: m()
	{
		size_t i = 0; size_t j = 0;
		for (const auto& sublist : list)
		{
			for (const auto& elem : sublist)
			{
				m[i][j] = elem;
				++j;
			}

			++i;
			j = 0;
		}
	}

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	const T& matrix<R, C, T>::MatrixRow::operator[](unsigned i) const
	{
		return arr[i];
	}

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	T& matrix<R, C, T>::MatrixRow::operator[](unsigned i)
	{
		return arr[i];
	}

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	matrix<R, C, T>::MatrixRow::MatrixRow(Array& mat)
		: arr(mat)
	{

	}

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	typename const matrix<R, C, T>::MatrixRow matrix<R, C, T>::operator[](unsigned i) const
	{
		return MatrixRow(const_cast<matrix<R, C, T>* const>(this)->m[i]);
	}

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	typename matrix<R, C, T>::MatrixRow matrix<R, C, T>::operator[](unsigned i)
	{
		return MatrixRow(m[i]);
	}

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	matrix<R, C, T>::matrix()
	{
		SetIdentity(*this);
	}

	template<unsigned R, unsigned C, typename T>
	void SetIdentity(matrix<R, C, T>& mat)
	{
		for (unsigned i = 0; i < C; ++i)
		{
			for (unsigned j = 0; j < R; ++j)
			{
				if (i == j)
				{
					mat.m[i][j] = static_cast<T>(1);
				}
				else
				{
					mat.m[i][j] = static_cast<T>(0);
				}
			}
		}
	}

	template<unsigned R, unsigned C, typename T>
	matrix<C, R, T> Transpose(const matrix<R, C, T>& mat)
	{
		return matrix<C, R, T> mat;
	}

	template<unsigned R, unsigned C /*= R*/, typename T /*= float*/>
	matrix<R, C, T>::matrix(const Array2D& list)
		: m(list)
	{

	}

	template<unsigned R, typename T>
	std::array<T, R> operator*(const std::array<T, R>& arr, T scalar)
	{
		static_assert(std::is_floating_point<T>::value == true, "not real value!");

		std::array<T, R> ret = arr;

		for (auto& elem : ret)
		{
			elem *= scalar;
		}

		return ret;
	}

	template<unsigned R, typename T>
	std::array<T, R> operator+(const std::array<T, R>& arr, const std::array<T, R>& addby)
	{
		std::array<T, R> ret = arr;

		for (unsigned i = 0; i < R; ++i)
		{
			ret[i] += addby[i];
		}

		return ret;
	}

	template<unsigned R, typename T>
	std::array<T, R> operator-(const std::array<T, R>& arr, const std::array<T, R>& subby)
	{
		std::array<T, R> ret = arr;

		for (unsigned i = 0; i < R; ++i)
		{
			ret[i] -= subby[i];
		}

		return ret;
	}

	template<unsigned R, typename T>
	typename vector<R, T> operator*(const matrix<R, R, T>& mat, const vector<R, T>& vec)
	{
		vector<R, T> ret;

		for (unsigned i = 0; i < R; ++i)
		{
			T value{};

			for (unsigned j = 0; j < R; ++j)
			{
				value += mat[i][j] * vec[j];
			}

			ret[i] = value;
		}

		return ret;
	}

	template<unsigned R, unsigned C, typename T>
	std::ostream& operator<<(std::ostream& os, const matrix<R, C, T>& mat)
	{
		os << "[" << std::endl;
		for (size_t i = 0; i < R; ++i)
		{
			os << "\t";
			for (size_t j = 0; j < C; ++j)
			{
				os << mat[i][j] << " ";
			}
			os << std::endl;
		}
		os << "]";

		return os;
	}

}

#endif
