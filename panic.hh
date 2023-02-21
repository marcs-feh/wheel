#ifndef INCLUDE_PANIC_HH_
#define INCLUDE_PANIC_HH_

#include <cstdlib>
#include <cstdio>
#include "types.hh"

#ifndef PANIC_INTERCEPT
namespace mf {
static inline void panic(const char* msg = nullptr){
	std::fprintf(stderr, "[PANIC]: %s\n", msg);
	while(true){ std::exit(EXIT_FAILURE); }
}
}
#else
namespace mf {
static u32 panic_intercepts = 0;
static inline void panic(const char* msg){
	std::fprintf(stderr, "[(intercepted)PANIC]: %s\n", msg);
	panic_intercepts += 1;
}
}
#endif

namespace mf{
static inline void panic_assert(bool predicate, const char* msg = "Failed assert"){
	if(!predicate){ panic(msg); }
}
}

#endif /* include guard */
