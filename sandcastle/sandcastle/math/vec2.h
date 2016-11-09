#ifndef math_vec_2_h__
#define math_vec_2_h__

#include <math/vec.h>

namespace sandcastle::math
{

	struct vec2 : public vector<2, float>
	{

		using vector<2, float>::vector;

		vec2(float x, float y);

		float x() const { return m[0]; };
		float y() const { return m[1]; };

		vec2 xx() const { return vec2(m[0], m[0]); }
		vec2 yy() const { return vec2(m[1], m[1]); }
		vec2 xy() const { return vec2(m[0], m[1]); }
		vec2 yx() const { return vec2(m[1], m[0]); }

		void x(float in) { m[0] = in; };
		void y(float in) { m[1] = in; };

	};

}

#endif
