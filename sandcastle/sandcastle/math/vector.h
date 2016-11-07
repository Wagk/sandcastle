#ifndef math_vector_h__
#define math_vector_h__

#include <array>
#include <iostream>

namespace sandcastle::math
{

	template<unsigned D, typename T = double>
	struct vector
	{
	public:

		using arraytype = std::array<T, D>;
		static const unsigned Size = D;

		vector();
		vector(const std::initializer_list<T>& list);

		T& operator[](size_t index);
		const T& operator[](size_t index) const;

		arraytype m;
	};

	using vec4 = vector<4, float>;
	using vec3 = vector<3, float>;
	using vec2 = vector<2, float>;

	template<unsigned D, typename T, typename ReturnType = T>
	ReturnType operator*(const vector<D, T>& v1, const vector<D, T>& v2);

	template<unsigned D, typename T, typename InputT>
	vector<D, T> operator*(const vector<D, T>& vec, InputT scale);

	template<unsigned D, typename T, typename InputT>
	vector<D, T> operator*(InputT scale, const vector<D, T>& vec);

	template<unsigned D, typename T, typename InputT>
	vector<D, T>& operator*=(vector<D, T>& vec, InputT scale);

	template<unsigned D, typename T>
	std::ostream& operator<<(std::ostream& os, const vector<D, T>& vec);

}

#include "vector.inl"

#endif