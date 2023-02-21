#ifndef INCLUDE_TEST_HH_
#define INCLUDE_TEST_HH_

#include "utils.hh"
#include "types.hh"
#include "panic.hh"
#include <iostream>

struct Test {
	u32 error_count;
	u32 test_count;
	const char* test_name;

	template<typename A, typename B>
	bool eq(const A& expect, const B& expr, const char* msg = nullptr){
		bool ok = expect == expr;
		test_count += 1;
		if(!ok){
			error_count += 1;
			if(msg){
				std::cout << msg << '\n';
			} else {
				std::cout << "\tFAIL: " << expect << " <-> " << expr << '\n';
			}
		}
		return ok;
	}

	void display_start(){
		std::cout << "----" << test_name << "----\n";
	}

	void display_end(){
		if(error_count == 0){
			std::cout << "PASSED: ";
		} else {
			std::cout << "FAILED: ";
		}
		std::cout << "ok in " << test_count - error_count << " out of " << test_count << " tests.\n";
	}

	Test(const char* name){
		test_name   = name;
		error_count = 0;
		test_count  = 0;
		display_start();
	}
	~Test(){
		display_end();
		#ifdef PANIC_INTERCEPT
		wheel::panic_intercepts = 0;
		#endif
	}
};

#define EQ(expr1, expr2) T.eq((expr1), (expr2), #expr1 " <-> " #expr2)

#endif /* include guard */
