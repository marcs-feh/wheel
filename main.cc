#include <iostream>
#define print(x) std::cout << x << '\n'

#include "defer.hh"
#include "test.hh"
#include "panic.hh"
#include "maybe.hh"

int main(){
	Maybe<i32> a = as_rval(Maybe<i32>(4)).get();
	print(a.get());
	return 0;
}

