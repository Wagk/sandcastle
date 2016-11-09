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
		vec3(float x = 0.f, float y = 0.f, float z = 0.f);

		float x() const { return m[0]; };
		float y() const { return m[1]; };
		float z() const { return m[2]; };

		vec2 xx() const { return vec2(m[0], m[0]); };
		vec2 xy() const { return vec2(m[0], m[1]); };
		vec2 xz() const { return vec2(m[0], m[2]); };

		vec2 yx() const { return vec2(m[1], m[0]); };
		vec2 yy() const { return vec2(m[1], m[1]); };
		vec2 yz() const { return vec2(m[1], m[2]); };

		vec2 zx() const { return vec2(m[2], m[0]); };
		vec2 zy() const { return vec2(m[2], m[1]); };
		vec2 zz() const { return vec2(m[2], m[2]); };

		vec3 xxx() const { return vec3(m[0], m[0], m[0]); };
		vec3 xxy() const { return vec3(m[0], m[0], m[1]); };
		vec3 xxz() const { return vec3(m[0], m[0], m[2]); };
		vec3 xyx() const { return vec3(m[0], m[1], m[0]); };
		vec3 xyy() const { return vec3(m[0], m[1], m[1]); };
		vec3 xyz() const { return vec3(m[0], m[1], m[2]); };
		vec3 xzx() const { return vec3(m[0], m[2], m[0]); };
		vec3 xzy() const { return vec3(m[0], m[2], m[1]); };
		vec3 xzz() const { return vec3(m[0], m[2], m[2]); };

		vec3 yxx() const { return vec3(m[1], m[0], m[0]); };
		vec3 yxy() const { return vec3(m[1], m[0], m[1]); };
		vec3 yxz() const { return vec3(m[1], m[0], m[2]); };
		vec3 yyx() const { return vec3(m[1], m[1], m[0]); };
		vec3 yyy() const { return vec3(m[1], m[1], m[1]); };
		vec3 yyz() const { return vec3(m[1], m[1], m[2]); };
		vec3 yzx() const { return vec3(m[1], m[2], m[0]); };
		vec3 yzy() const { return vec3(m[1], m[2], m[1]); };
		vec3 yzz() const { return vec3(m[1], m[2], m[2]); };

		vec3 zxx() const { return vec3(m[2], m[0], m[0]); };
		vec3 zxy() const { return vec3(m[2], m[0], m[1]); };
		vec3 zxz() const { return vec3(m[2], m[0], m[2]); };
		vec3 zyx() const { return vec3(m[2], m[1], m[0]); };
		vec3 zyy() const { return vec3(m[2], m[1], m[1]); };
		vec3 zyz() const { return vec3(m[2], m[1], m[2]); };
		vec3 zzx() const { return vec3(m[2], m[2], m[0]); };
		vec3 zzy() const { return vec3(m[2], m[2], m[1]); };
		vec3 zzz() const { return vec3(m[2], m[2], m[2]); };

		void x(float in) { m[0] = in; };
		void y(float in) { m[1] = in; };
		void z(float in) { m[2] = in; };

	};

}

#endif
