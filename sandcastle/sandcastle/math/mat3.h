#ifndef math_matrix_3_h__
#define math_matrix_3_h__

#include <math/mat.h>
#include <math/vec3.h>

namespace sandcastle::math
{

	struct mat3 : public matrix<3, 3, float>
	{

		using matrix<3, 3, float>::matrix;

		mat3(const vec3& e1, const vec3& e2, const vec3& e3 = { 0, 0, 1 });

	};

}

#endif
