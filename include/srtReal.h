#ifndef H_SRT_REAL
#define H_SRT_REAL

#include "float.h"

#define FLOAT_PRECISION 0
#define DOUBLE_PRECISION 1

#define REAL_PRECISION DOUBLE_PRECISION

#if (REAL_PRECISION == FLOAT_PRECISION)
	typedef float srtReal;
	#define SRT_REAL_MAX FLT_MAX
	#define SRT_REAL_MIN FLT_MIN
	#define SRT_REAL_EPSILON FLT_EPSILON
#elif (REAL_PRECISION == DOUBLE_PRECISION)
	typedef double srtReal;
	#define SRT_REAL_MAX DBL_MAX
	#define SRT_REAL_MIN DBL_MIN
	#define SRT_REAL_EPSILON DBL_EPSILON
#else
	#error REAL_PRECISION type is not implemented/supported
#endif

#endif