#ifndef H_SRT_ASSERT
#define H_SRT_ASSERT

#include "stdlib.h"

#define SRT_ASSERTIONS_ENABLED

/* assert handler						condition,	file,		line,	msg, 	  arg_list */
typedef void (*srtAssertionFailureFunc)(const char*, const char*, int, const char*, ...);
srtAssertionFailureFunc g_srtOnAssertFailure = NULL;

#define SRT_UNUSED(expr) do { (void)sizeof(expr); } while(0)
#ifdef SRT_ASSERTIONS_ENABLED
	#define SRT_ASSERT(expr) \
		do \
		{ \
			if (!(expr)) \
			{ \
				if (g_srtOnAssertFailure) { \
					(*g_srtOnAssertFailure)(#expr, \
											__FILE__, \
											__LINE__, \
											NULL); \
				} \
			} \
		} while (0)
	#define SRT_ASSERT_MSG(expr, msg, ...) \
		do \
		{ \
			if (!(expr)) \
			{ \
				if (g_srtOnAssertFailure) { \
					(*g_srtOnAssertFailure)(#expr, \
											__FILE__, \
											__LINE__, \
											(msg), \
											#__VA_ARGS__); \
				} \
			} \
		} while (0)	   
#else
	#define SRT_ASSERT(expr) \
		do { SRT_UNUSED(expr); } while(0)
	#define SRT_ASSERT_MSG(expr, msg, ...) \
		do { SRT_UNUSED(expr); SRT_UNUSED(msg); } while(0)
#endif

#endif