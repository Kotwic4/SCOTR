#include <assert.h>

/*
 * debugAssert is a function, which is active only if there is define DEBUG.
 * If DEBUG is not defined, then debugAssert do nothing.
 */

#ifdef DEBUG

#define debugAssert(x) assert(x)

#else

#define debugAssert(ignore) ((void)0)

#endif
