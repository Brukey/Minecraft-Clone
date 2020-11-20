#pragma once

#ifdef DEBUG
	#include <stdio.h>
	#define LOG(...) printf(__VA_ARGS__)
	#define ASSERT(condition)if(!(condition)) {printf("assert (%s) failed in %s:%d", #condition, __FILE__, __LINE__); __debugbreak();}
#else
	#define LOG(...)
	#define ASSERT(condition)
#endif