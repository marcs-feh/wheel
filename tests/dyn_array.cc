#ifndef INCLUDE_DYN_ARR_CC_
#define INCLUDE_DYN_ARR_CC_

#include "../test.hh"
#include "../dyn_array.hh"
using namespace mf;

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

	arr.add(7, 1);
	arr.add(7, 0);
	arr.add(7, arr.len());
	EQ(true, (arr[2] == 7) && (arr[0] == 7) && (arr[arr.len()-1] - 1));

	arr.del(0);
	EQ(0, arr[0]);
	arr.del(1);
	EQ(2, arr[1]);
	arr.del(arr.len() - 1);
	EQ(6, arr[arr.len() - 1]);
	EQ(false, arr.contains(-4));
	EQ(true, arr.contains(0));

	Dyn_Array<i32> x, y;
	x.add(6);
	x.add(9);
	y.add(4);
	y.add(2);
	y.add(0);
	y = x;
	EQ(true, y == x);
	y[0] = 7;
	EQ(7, y[0]);
	EQ(6, x[0]);
}


#endif /* include guard */
