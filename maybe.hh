#ifndef INCLUDE_MAYBE_HH_
#define INCLUDE_MAYBE_HH_

#include "panic.hh"
#include "utils.hh"

namespace wheel {

template<typename T>
struct Maybe {
	union {
		T data;
	};
	bool is_ok;

	// Check if data is safe to get value (not nil)
	bool ok() const { return is_ok; }

	// Destroys contained data, returing back to nil
	void destroy() {
		if(is_ok){
			data.~T();
			is_ok = false;
		}
	}

	// Get contained value, panic otherwhise
	T& val() & {
		panic_assert(is_ok, "Cannot get value from nil");
		return data;
	}

	// Get contained value, panic otherwhise
	const T& val() const& {
		panic_assert(is_ok, "Cannot get value from nil");
		return data;
	}

	// Get contained value, panic otherwhise
	T&& val() && {
		panic_assert(is_ok, "Cannot get valuefrom nil");
		return as_rval(data);
	}

	// Default constructor
	Maybe() { is_ok = false; }

	// Value constructor (copy)
	Maybe(const T& val) : data(val) {
		is_ok = true;
	}

	// Value constructor (move)
	Maybe(T&& val) : data(as_rval(val)) {
		is_ok = true;
	}

	// Copy constructor
	Maybe(const Maybe& opt) : is_ok(opt.is_ok){
		if(is_ok){
			new (&data) T(opt.data);
		}
	}

	// Move constructor
	Maybe(Maybe&& opt) : is_ok(opt.is_ok){
		if(is_ok){
			new (&data) T(as_rval(opt.data));
			opt.is_ok = false;
		}
	}

	// Copy assignment
	void operator=(const Maybe& opt){
		if(opt.is_ok){
			if(is_ok){
				data = opt.data;
			} else {
				new (&data) T(opt.data);
			}
			is_ok = true;
		} else {
			if(is_ok){
				data.~T();
			}
			is_ok = false;
		}
	}

	// Copy assignment value
	void operator=(const T& val){
		if(is_ok){
			data  = val;
		} else {
			new (&data) T(val);
		}
		is_ok = true;
	}

	// Move assignment
	void operator=(Maybe&& opt){
		if(opt.is_ok){
			if(is_ok){
				data = as_rval(opt.data);
			} else {
				new (&data) T(as_rval(opt.data));
			}
			is_ok = true;
		} else {
			if(is_ok){
				data.~T();
			}
			is_ok = false;
		}
	}

	// Move assignment value
	void operator=(T&& val){
		if(is_ok){
			data  = as_rval(val);
		} else {
			new (&data) T(as_rval(val));
		}
		is_ok = true;
	}

	// Destructor
	~Maybe(){
		if(is_ok){
			data.~T();
		}
	}
};

}

#endif /* include guard */
