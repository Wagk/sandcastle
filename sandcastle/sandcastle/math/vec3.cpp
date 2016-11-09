#include "vec3.h"

namespace sandcastle::math
{

	vec3::vec3(const vec2& rhs, float z)
		: vec3(rhs[0], rhs[1], z)
	{

	}

	vec3::vec3(float x, float y, float z)
		: vector({x, y, z})
	{

	}

}
