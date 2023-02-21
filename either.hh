#ifndef INCLUDE_EITHER_HH_
#define INCLUDE_EITHER_HH_

#include "panic.hh"
#include "types.hh"
#include "utils.hh"

namespace wheel {
namespace w = wheel;

template<typename TL, typename TR>
struct Either {
	enum struct Side : u8 { Left, Right };
	union {
		TL left_data;
		TR right_data;
	};
	Side side_tag;

	constexpr
	Side side() const { return side_tag; };

	TR& r_get() & {
		if(side_tag != Side::Right){
			panic("Cannot access right_data when it is tagged as Left");
		}
		return right_data;
	}

	const TR& r_get() const& {
		if(side_tag != Side::Right){
			panic("Cannot access right_data when it is tagged as Left");
		}
		return right_data;
	}

	TL& l_get() & {
		if(side_tag != Side::Left){
			panic("Cannot access left_data when it is tagged as Right");
		}
		return left_data;
	}

	const TL& l_get() const& {
		if(side_tag != Side::Left){
			panic("Cannot access left_data when it is tagged as Right");
		}
		return left_data;
	}

	// Default constructor
	Either() : left_data() {
		side_tag = Side::Left;
	}

	// Left constructor
	Either(const TL& val) : left_data(val) {
		side_tag = Side::Left;
	}

	// Right constructor
	Either(const TR& val) : right_data(val) {
		side_tag = Side::Right;
	}

	// Copy constructor
	Either(const Either& e) : side_tag(e.side_tag){
		if(side_tag == Side::Left){
			new (&left_data) TL(e.left_data);
		} else {
			new (&right_data) TR(e.right_data);
		}
	}

	// Copy assignment
	void operator=(const Either& e){
		if(e.side_tag == side_tag){
			// Same tag, just copy
			if(side_tag == Side::Left){
				left_data = e.left_data;
			} else {
				right_data = e.right_data;
			}
		} else {
			// Diff tag, call destructor then copy
			if(side_tag == Side::Left){
				left_data.~TL();
				right_data = new(&right_data) TR(e.right_data);
			} else {
				right_data.~TR();
				left_data = new(&left_data) TL(e.left_data);
			}
			side_tag = e.side_tag;
		}
	}

	// Left copy assign
	void operator=(const TL& l){
		if(side_tag == Side::Right){
			right_data.~TR();
			new (&left_data) TL(l);
		} else {
			left_data = l;
		}
		side_tag = Side::Left;
	}

	// Right copy assign
	void operator=(const TR& r){
		if(side_tag == Side::Left){
			left_data.~TL();
			new (&right_data) TR(r);
		} else {
			right_data = r;
		}
		side_tag = Side::Right;
	}

	// Move constructor
	Either(Either&& e) : side_tag(e.side_tag) {
		if(side_tag == Side::Left){
			new (&left_data) TL(w::as_rval(e.left_data));
		} else {
			new (&right_data) TR(w::as_rval(e.right_data));
		}
	}

	// Move assignment
	void operator=(Either&& e){
		if(e.side_tag == Side::Left){
			right_data.~TR();
			new (&left_data) TL(e.left_data);
		} else {
			left_data.~LR();
			new (&right_data) TR(e.right_data);
		}
		side_tag = e.side_tag;
	}

	// Left move assign

	// Right move assign

	// Destructor
	~Either(){
		if(side_tag == Side::Left){
			left_data.~TL();
		} else {
			right_data.~TR();
		}
	}
};

}

#endif /* include guard */
