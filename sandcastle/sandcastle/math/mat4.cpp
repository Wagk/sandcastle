#include "mat4.h"

namespace sandcastle::math
{

	mat4::mat4(const vec4 & e1, const vec4 & e2, const vec4 & e3, const vec4 & e4)
		: matrix({
			{e1[0], e1[1], e1[2], e1[3]},
			{e2[0], e2[1], e2[2], e2[3]},
			{e3[0], e3[1], e3[2], e3[3]},
			{e4[0], e4[1], e4[2], e4[3]}
		})
	{

	}

}
