#ifndef H_SRT_VECTOR
#define H_SRT_VECTOR

#include "srtReal.h"
#include "srtMath.h"
#include "stdio.h"

typedef struct {
	float x, y, z;
} srtVector3;

const srtVector3 SRT_VECTOR3_ZERO =   {0.0f, 0.0f, 0.0f};
const srtVector3 SRT_VECTOR3_UNIT_X = {1.0f, 0.0f, 0.0f};
const srtVector3 SRT_VECTOR3_UNIT_Y = {0.0f, 1.0f, 0.0f};
const srtVector3 SRT_VECTOR3_UNIT_Z = {0.0f, 0.0f, 1.0f};

srtVector3 srtVec3_Add(const srtVector3 const *a, const srtVector3 const *b) {
	srtVector3 result = {a->x + b->x, a->y + b->y, a->z + b->z};
	return result;
}

srtVector3 srtVec3_Sub(const srtVector3 const *a, const srtVector3 const *b) {
	srtVector3 result = {a->x - b->x, a->y - b->y, a->z - b->z};
	return result;
}

srtVector3 srtVec3_Mult(const srtVector3 const *v, float s) {
	srtVector3 result = {v->x * s, v->y * s, v->z * s};
	return result;
}

float srtVec3_Dot(const srtVector3 const *u, const srtVector3 const *v) {
	return v->x * u->x + v->y * u->y + v->z * u->z;
}

int srtVec3_Equals(const srtVector3 const *u, const srtVector3 const *v) {
	return v->x == u->x && v->y == u->y && v->z == u->z;
}

void srtVec3_Normalize(srtVector3 *v) {
	srtReal lengthSq = v->x * v->x + v->y * v->y + v->z * v->z;
	if (lengthSq > SRT_REAL_EPSILON) {
		srtReal oneOverLength = 1.0 / srtSqrt(lengthSq);
		v->x *= oneOverLength;
		v->y *= oneOverLength;
		v->z *= oneOverLength;
	}
}

srtVector3 srtVec3_Reflect(const srtVector3 const *v, const srtVector3 const *n) {
	srtVector3 product = srtVec3_Mult(n, srtVec3_Dot(v, n));
	product = srtVec3_Mult(&product, 2.0f);
	return srtVec3_Sub(v, &product);
}

srtVector3 srtVec3_Cross(const srtVector3 const *u, const srtVector3 const *v) {
	srtVector3 result;
	result.x = u->y*v->z - u->z*v->y;
	result.y = u->z*v->x - u->x*v->z;
	result.z = u->x*v->y - u->y*v->x;
	return result;
}

void srtVec3_Print(const srtVector3 const *v) {
	printf("{ %f, %f, %f }", v->x, v->y, v->z);
}
/*
inline float srtVec3_Length_Squared(const srtVector3 const *v) {
	return v->x * v->x + v->y * v->y + v->z * v->z;
}

inline float srtVec3_Length(const srtVector3 const *v) {
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

inline float srtVec3_Distance_Squared(const srtVector3 const *u, const srtVector3 const *v) {
	float subx = v->x - u->x;
	float suby = v->y - u->y;
	float subz = v->z - u->z;
	return subx * subx + suby * suby + subz * subz;
}

inline float srtVec3_Distance(const srtVector3 const *v, const srtVector3 const *u) {
	return sqrt(srtVec3_Distance_Squared(v, u));
}
*/
#endif