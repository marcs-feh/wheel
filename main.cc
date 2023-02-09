#include <iostream>
#define print(x) std::cout << x << '\n'

#include "defer.hh"

int main(){
	int n = 69;
	defer {
		n = 420;
		if(n % 2 == 0){ print(n); }
	};
	print(n);
	return 0;
}

