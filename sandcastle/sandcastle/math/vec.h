#ifndef math_vec_h__
#define math_vec_h__

#include <array>
#include <iostream>
#include <type_traits>

namespace sandcastle::math
{

	template<unsigned D, typename T = double>
	struct vector
	{
	public:

		using arraytype = std::array<T, D>;

		unsigned size() const { return D; }

		vector();
		vector(const std::initializer_list<T>& list);

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		arraytype m;
	};

	template<unsigned D, typename T, typename ReturnType = T>
	ReturnType length(const vector<D, T>& vec);

	template<unsigned D, typename T, typename ReturnType = T>
	ReturnType squared_length(const vector<D, T>& vec);

	template<unsigned D, typename T, typename ReturnType = T>
	ReturnType operator*(const vector<D, T>& v1, const vector<D, T>& v2);

	template<unsigned D, typename T, typename InputT, typename std::enable_if<std::is_arithmetic<InputT>::value>::type* = nullptr>
	vector<D, T> operator*(const vector<D, T>& vec, InputT scale);

	template<unsigned D, typename T, typename InputT, typename std::enable_if<std::is_arithmetic<InputT>::value>::type* = nullptr>
	vector<D, T> operator*(InputT scale, const vector<D, T>& vec);

	template<unsigned D, typename T, typename InputT, typename std::enable_if<std::is_arithmetic<InputT>::value>::type* = nullptr>
	vector<D, T>& operator*=(vector<D, T>& vec, InputT scale);

	template<unsigned D, typename T>
	std::ostream& operator<<(std::ostream& os, const vector<D, T>& vec);

}

#include "vec.inl"

#endif