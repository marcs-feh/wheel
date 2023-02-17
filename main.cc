#include <iostream>
#include "print.cc"
#include "utils.hh"
#define PANIC_INTERCEPT 1

#include "types.hh"
#include "defer.hh"
#include "panic.hh"
#include "maybe.hh"
#include "array.hh"
#include "dyn_array.hh"
#include "test.hh"

using namespace mf;

void test_maybe(){
	Test T("Maybe");
	Maybe<i32> a, b;
	EQ(false, b.ok());
	EQ(false, a.ok());
	a = 69;
	EQ(true, a.ok());
	EQ(69, a.val());
	b.val();
	EQ(1U, G::panic_intercepts);
	b = a;
	EQ(69, b.val());
	EQ(a.val(), b.val());
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

void test_dyn_array(){
	Test T("Dynamic Array");
	Dyn_Array<i32> arr;
	EQ(dyn_array_default_size, arr.cap());
	EQ(0u, arr.len());
	EQ(true, arr.data != nullptr);
}

int main(){
	test_maybe();
	test_array();
	test_dyn_array();
	i32 x = 9, y = 6;
	print(x,y);
	mf::swap(x,y);
	print(x,y);

	return 0;
}

