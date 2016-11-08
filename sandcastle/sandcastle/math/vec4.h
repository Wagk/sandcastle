#ifndef math_vec_4_h__
#define math_vec_4_h__

#include <math/vec.h>
#include <math/vec2.h>
#include <math/vec3.h>

namespace sandcastle::math
{

	struct vec4 : public vector<4, float>
	{

		using vector<4, float>::vector;

		vec4(float x, float y, float z, float w);
		vec4(const vec3& rhs, float w);
		vec4(const vec2& rhs, float z, float w);

		//swizzling functions
		float x() const { return m[0]; };
		float y() const { return m[1]; };
		float z() const { return m[2]; };
		float w() const { return m[3]; };

		void x(float in) { m[0] = in; };
		void y(float in) { m[1] = in; };
		void z(float in) { m[2] = in; };
		void w(float in) { m[3] = in; };

	};

}

#endif