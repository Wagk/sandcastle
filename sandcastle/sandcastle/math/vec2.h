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

		void x(float in) { m[0] = in; };
		void y(float in) { m[1] = in; };

	};

}

#endif
