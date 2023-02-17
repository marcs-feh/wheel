// THIS FILE IS *ONLY* FOR DEBUGGING PURPOSES

#ifndef INCLUDE_PRINT_CC_
#define INCLUDE_PRINT_CC_

#include <iostream>
namespace {
	template<typename T>
	void print_rec(const T& x){
		std::cout << x;
	}

	template<typename T, typename ...Args>
	void print_rec(const T& x, const Args&... args){
		print_rec(x);
		std::cout << ' ';
		print_rec(args...);
	}
}

template<typename ...Args>
void print(const Args&... args){
	print_rec(args...);
	std::cout << '\n';
}

#endif /* include guard */
