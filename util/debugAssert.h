#include <assert.h>

#define DEBUG

#ifdef DEBUG

#define debugAssert(x) assert(x)

#else

#define debugAssert(x) ((void)0)

#endif
