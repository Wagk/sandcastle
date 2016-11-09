#ifndef math_matrix_4_h__
#define math_matrix_4_h__

#include <math/mat.h>
#include <math/vec4.h>

namespace sandcastle::math
{

	struct mat4 : public matrix<4, 4, float>
	{

		using matrix<4, 4, float>::matrix;

		mat4(const vec4& e1, const vec4& e2, const vec4& e3, const vec4& e4 = {0, 0, 0, 1});

	};

}

#endif
