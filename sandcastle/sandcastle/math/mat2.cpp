#include "mat2.h"

namespace sandcastle::math
{
	mat2::mat2(const vec2 & e1, const vec2 & e2)
		: matrix({
			{e1[0], e1[1]},
			{e2[0], e2[1]}
		})
	{

	}
}
