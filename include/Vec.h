#ifndef	__Vec_H_
#define __Vec_H_

#include <cstdio>


typedef long long vtype;


class vec3 {
public:
	vec3() { X[0] = X[1] = X[2] = 0; }
	vec3(vtype x, vtype y, vtype z) { X[0] = x; X[1] = y; X[2] = z; }

	/* 3D cross product */
	vtype dot(const vec3& v) const {
		return X[0] * v.X[0] + X[1] * v.X[1] + X[2] * v.X[2];
	}
	
	vec3 operator*(const vec3& v) const {
		return vec3(X[1] * v.X[2] - X[2] * v.X[1],
					X[2] * v.X[0] - X[0] * v.X[2],
					X[0] * v.X[1] - X[1] * v.X[0]);
	}

	vec3 operator-(const vec3& v) const {
		return vec3(X[0] - v.X[0], X[1] - v.X[1], X[2] - v.X[2]);
	}

	vec3 operator-() const {
		return vec3(-X[0], -X[1], -X[2]);
	}

public: 

	vtype X[3];
};

#endif
