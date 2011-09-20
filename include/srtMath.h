#ifndef H_SRT_MATH
#define H_SRT_MATH

#include "srtReal.h"
#include "math.h"
/*
#define SRT_PI 3.1415926536
#define SRT_HALF_PI SRT_PI * 0.5
*/
const srtReal SRT_PI = 3.1415926536;

srtReal srtCos(srtReal x) {
	return cos(x);
}

srtReal srtSin(srtReal x) {
	return sin(x);
}

srtReal srtTan(srtReal x) {
	return tan(x);
}

srtReal srtSqrt(srtReal x) {
	return sqrt(x);
}

srtReal srtMin(srtReal a, srtReal b) {
	if (a < b)
		return a;
	return b;
}

srtReal srtMax(srtReal a, srtReal b) {
	if (a > b)
		return a;
	return b;
}

srtReal srtClamp(srtReal value, srtReal min, srtReal max) {
	if (value <= min) return min;
	if (value >= max) return max;
	return value;
}

srtReal degreesToRadians(srtReal degrees) {
	return degrees * SRT_PI / 180.0;
}

srtReal radiansToDegrees(srtReal radians) {
	return radians * 180.0 / SRT_PI;
}

#endif