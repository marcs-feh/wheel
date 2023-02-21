#ifndef INCLUDE_DUMMY_HH_
#define INCLUDE_DUMMY_HH_

#include <iostream>
// Dummy structs for testing
struct A{
	A(){ std::cout << "A ctor\n"; }
	A(int){ std::cout << "A ctor\n"; }
	A(const A&){std::cout << "A copy ctor\n";}
	void operator=(const A&){std::cout << "A copy assign\n";}
	A(A&&){std::cout << "A move ctor\n";}
	void operator=(A&&){std::cout << "A move assign\n";}
	~A(){ std::cout << "A dtor\n"; }
};

struct B{
	B(){ std::cout << "B ctor\n"; }
	B(const B&){std::cout << "B copy ctor\n";}
	void operator=(const B&){std::cout << "B copy assign\n";}
	B(B&&){std::cout << "B move ctor\n";}
	void operator=(B&&){std::cout << "B move assign\n";}
	~B(){ std::cout << "B dtor\n"; }
};


#endif /* include guard */
