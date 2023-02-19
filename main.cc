#include <cstdio>
#include <iostream>
#include "print.cc"
#define PANIC_INTERCEPT 1

#include "utils.hh"
#include "types.hh"
#include "defer.hh"
#include "panic.hh"
#include "maybe.hh"
#include "array.hh"
#include "dyn_array.hh"
#include "test.hh"

using namespace mf;
// Tests
void test_defer(); void test_maybe(); void test_array(); void test_dyn_array();

template<typename T>
void print(const Dyn_Array<T>& arr){
	std::cout << "(len:" << arr.len() << ",cap:" << arr.cap() << ")[ ";
	for(usize i = 0; i < arr.len(); i += 1){
		std::cout << arr[i] << ' ';
	}
	std::cout << "]\n";
}

void test_dyn_array(){
	Test T("Dynamic Array");
	Dyn_Array<i32> arr;
	EQ(dyn_array_default_size, arr.cap());
	EQ(0u, arr.len());
	EQ(true, arr.data != nullptr);
	arr.resize(8);
	EQ(8u, arr.cap());
	arr.add(6);
	arr.add(9);
	EQ(2u, arr.len());
	EQ(6, arr[0]);
	EQ(9, arr[1]);
	arr.resize(1);
	EQ(dyn_array_min_size, arr.cap());
	EQ(1u, arr.len());
	EQ(6, arr[0]);

	arr.del();
	EQ(0u, arr.len());

	usize n = arr.cap();
	for(usize i = 0; i < n; i += 1){
		arr.add(i*2);
	}
	EQ(static_cast<usize>((n + 1) * dyn_array_growth_fact), arr.cap());

	print(arr);
	arr.add(7, 1);
	arr.add(7, 0);
	arr.add(7, arr.len());
	EQ(true, (arr[2] == 7) && (arr[0] == 7) && (arr[arr.len()-1] - 1));
	print(arr);

	print(arr);
	arr.del(0);
	EQ(0, arr[0]);
	arr.del(1);
	EQ(2, arr[1]);
	arr.del(arr.len() - 1);
	EQ(6, arr[arr.len() - 1]);
	print(arr);
	EQ(false, arr.contains(-4));
	EQ(true, arr.contains(0));
}

int main(){
	test_defer();
	test_maybe();
	test_array();
	test_dyn_array();

	return 0;
}

void test_defer(){
	Test T("Defer");
	i32 n = 69;
	{
		defer { n = 420; };
		EQ(69, n);
	}
	EQ(420, n);
}

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

void test_array(){
	Test T("Array");
	Array<f32, 8> a;
	a[0] = 4;
	a[1] = 2;
	EQ(4, a[0]);
	EQ(2, a[1]);
	a[34] = 3;
	EQ(1u, panic_intercepts);
	Array<i32, 2> x, y;
	x[0] = 6;
	x[1] = 9;
	y = x;
	EQ(true, x == y);
}

