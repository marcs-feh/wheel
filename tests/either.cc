#ifndef INCLUDE_EITHER_CC_
#define INCLUDE_EITHER_CC_

#define PANIC_INTERCEPT 1

#include "../test.hh"
#include "../either.hh"

using namespace wheel;

void test_either(){
	Test T("Either");
	Either<char, u32> e;
	EQ(true, e.side() == Either_Side::Left);
	Either<char, u32> a('L');
	EQ(true, a.side() == Either_Side::Left);
	Either<char, u32> b(34u);
	EQ(true, b.side() == Either_Side::Right);
	a.r_get();
	b.l_get();
	EQ(2u, wheel::panic_intercepts);
	EQ('L', a.l_get());
	EQ(34u, b.r_get());
	a = 69u;
	b = 'e';
	EQ(69u, a.r_get());
	EQ('e', b.l_get());
	a.l_get();
	b.r_get();
	EQ(4u, wheel::panic_intercepts);
	Either<char, u32> m(as_rval(a));
	EQ(69u, m.r_get());
}


#endif /* include guard */
