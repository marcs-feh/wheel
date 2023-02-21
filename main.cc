#define PANIC_INTERCEPT 1
#include "maybe.hh"

// Test files
#include "print.cc"
#include "tests/dyn_array.cc"
#include "tests/array.cc"
#include "tests/defer.cc"
#include "tests/either.cc"
#include "tests/maybe.cc"
#include "tests/dummy.hh"

using namespace wheel;

// TODO: reinforce tests with move ctor and assignment
// TODO: raii bs for dyn_array
// TODO: finish Etiher

int main(){
	test_defer();
	test_maybe();
	test_either();
	test_array();
	test_dyn_array();
	return 0;
}

