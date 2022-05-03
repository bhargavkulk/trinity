#ifndef CRASH_HH
#define CRASH_HH

#include <cstdlib>
#include <cstdio>

inline void CRASH_IF_TRUE(bool cond, const char *msg)
{
    if(cond)
    {
        fprintf(stderr, "FATAL ERROR: %s\n", msg);
		exit(1);
    }
}

#define CRASH_IF_NIL(ptr) CRASH_IF_TRUE(!ptr, "NIL Reference")

#endif /* CRASH_HH */