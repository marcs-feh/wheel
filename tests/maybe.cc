#ifndef INCLUDE_MAYBE_CC_
#define INCLUDE_MAYBE_CC_

#define PANIC_INTERCEPT 1

#include "../test.hh"
#include "../maybe.hh"
using namespace wheel;

void test_maybe(){
	Test T("Maybe");
	Maybe<i32> a, b;
	EQ(false, b.ok());
	EQ(false, a.ok());
	a = 69;
	EQ(true, a.ok());
	EQ(69, a.val());
	b.val();
	EQ(1U, panic_intercepts);
	b = a;
	EQ(69, b.val());
	EQ(a.val(), b.val());
	EQ(1U, panic_intercepts);
}


#endif /* include guard */
