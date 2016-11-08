#include "vec4.h"

namespace sandcastle::math
{

	vec4::vec4(float x, float y, float z, float w)
		: vector({x, y, z, w})
	{

	}

	vec4::vec4(const vec3& rhs, float w)
		: vec4(rhs[0], rhs[1], rhs[2], w)
	{

	}

	vec4::vec4(const vec2& rhs, float z, float w)
		: vec4(rhs[0], rhs[1], z, w)
	{

	}

}