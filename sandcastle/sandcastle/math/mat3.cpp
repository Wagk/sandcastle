#include "mat3.h"

namespace sandcastle::math
{

	sandcastle::math::mat3::mat3(const vec3 & e1, const vec3 & e2, const vec3 & e3)
		: matrix({ 
			{e1[0], e1[1], e1[2]},
			{e2[0], e2[1], e2[2]},
			{e3[0], e3[1], e3[2]},
		})
	{}

}
