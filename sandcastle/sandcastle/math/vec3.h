#ifndef math_vec_3_h__
#define math_vec_3_h__

#include <math/vec.h>
#include <math/vec2.h>

namespace sandcastle::math
{

	struct vec3 : public vector<3, float>
	{

		using vector<3, float>::vector;

		vec3(const vec2& rhs, float z);
		vec3(float x, float y, float z);

		float x() const { return m[0]; };
		float y() const { return m[1]; };
		float z() const { return m[2]; };

		void x(float in) { m[0] = in; };
		void y(float in) { m[1] = in; };
		void z(float in) { m[2] = in; };

	};

}

#endif
