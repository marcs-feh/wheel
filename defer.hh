// Defers a lambda call to the end of a scope.

#ifndef INCLUDE_DEFER_HH_
#define INCLUDE_DEFER_HH_

#include "utils.hh"

namespace mf {

template<typename F>
struct Deferred_Call {
	F f;
	Deferred_Call(F&& f) : f(as_rval(f)) {}
	~Deferred_Call(){ f(); }
};

#define DEFER_HH_CONCAT_1(x, y) x##y
#define DEFER_HH_CONCAT_2(x, y) DEFER_HH_CONCAT_1(x, y)
#define DEFER_HH_CONCAT_COUNTER(x) DEFER_HH_CONCAT_2(x, __COUNTER__)
#define defer ::mf::Deferred_Call DEFER_HH_CONCAT_COUNTER(_tmp_defer_func_) = [&]()

}
#endif /* include guard */
