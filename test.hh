#ifndef INCLUDE_TEST_HH_
#define INCLUDE_TEST_HH_

#include "types.hh"
#include <iostream>

struct Test {
	u32 error_count;
	u32 test_count;
	const char* test_name;

	template<typename A, typename B>
	bool eq(const A& expect, const B& expr){
		bool ok = expect == expr;
		test_count += 1;
		if(!ok){
			error_count += 1;
			std::cerr << "\tFAIL: " << expect << " <-> " << expr << "\n";
		}
		return ok;
	}

	void display_start(){
		std::cerr << "----" << test_name << "----\n";
	}

	void display_end(){
		if(error_count == 0){
			std::cerr << "PASSED: ";
		} else {
			std::cerr << "FAILED: ";
		}
		std::cerr << "ok in " << test_count - error_count << " out of " << test_count << " tests.\n";
	}

	Test(const char* name){
		test_name   = name;
		error_count = 0;
		test_count  = 0;
		display_start();
	}
	~Test(){
		display_end();
	}
};

#endif /* include guard */
