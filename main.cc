#include <iostream>
#define print(x) std::cout << x << '\n'

#include "defer.hh"
#include "test.hh"

void test_thing(){
	Test t("Some thing.");
	i32 n = 43;
	t.eq(42, n);
	t.eq(43, n);
}

int main(){
	test_thing();
	int n = 69;
	defer {
		n = 420;
		if(n % 2 == 0){ print(n); }
	};
	print(n);
	return 0;
}

