#ifndef INCLUDE_ARRAY_CC_
#define INCLUDE_ARRAY_CC_

#define PANIC_INTERCEPT 1

#include "../test.hh"
#include "../array.hh"
#include "../panic.hh"

using namespace wheel;

void test_array(){
	Test T("Array");
	Array<f32, 8> a;
	a[0] = 4;
	a[1] = 2;
	EQ(4, a[0]);
	EQ(2, a[1]);
	a[34] = 3;
	EQ(1u, wheel::panic_intercepts);
	Array<i32, 2> x, y;
	x[0] = 6;
	x[1] = 9;
	y = x;
	EQ(true, x == y);
}

#endif /* include guard */
