#ifndef math_matrix_2_h__
#define math_matrix_2_h__

#include <math/mat.h>
#include <math/vec2.h>

namespace sandcastle::math
{

	struct mat2 : public matrix<2, 2, float>
	{

		using matrix<2, 2, float>::matrix;

		mat2(const vec2& e1, const vec2& e2);

	};

}

#endif