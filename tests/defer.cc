#ifndef INCLUDE_DEFER_CC_
#define INCLUDE_DEFER_CC_

#include "../test.hh"
#include "../defer.hh"
using namespace mf;

void test_defer(){
	Test T("Defer");
	i32 n = 69;
	{
		defer { n = 420; };
		EQ(69, n);
	}
	EQ(420, n);
}


#endif /* include guard */
