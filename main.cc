#include "types.hh"
#include <iostream>

#define print(x) std::cout << x << '\n'

#define PANIC_INTERCEPT 1
#include "defer.hh"
#include "test.hh"
#include "panic.hh"
#include "maybe.hh"
#include "array.hh"

using namespace mf;

void test_maybe(){
	Test T("Maybe");
	Maybe<i32> a, b;
	EQ(false, b.ok());
	EQ(false, a.ok());
	a = 69;
	EQ(true, a.ok());
	EQ(69, a.get());
	b.get();
	EQ(1U, G::panic_intercepts);
	b = a;
	EQ(69, b.get());
	EQ(a.get(), b.get());
	EQ(1U, G::panic_intercepts);
}

void test_array(){
	Test T("Array");
	Array<f32, 8> a;
	a[0] = 4;
	a[1] = 2;
	EQ(4, a[0]);
	EQ(2, a[1]);
	a[34] = 3;
	EQ(1u, G::panic_intercepts);
	Array<i32, 2> x, y;
	x[0] = 6;
	x[1] = 9;
	y = x;
	EQ(true, x == y);
}

int main(){
	test_maybe();
	test_array();
	return 0;
}

