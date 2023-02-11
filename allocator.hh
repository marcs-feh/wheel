#ifndef INCLUDE_ALLOCATOR_HH_
#define INCLUDE_ALLOCATOR_HH_

#include "types.hh"

// Allocator interface.
struct Allocator {
	virtual void* alloc(usize) = 0;
	virtual void  free(void*) = 0;
};

#endif /* include guard */
