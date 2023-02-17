#ifndef INCLUDE_MAYBE_HH_
#define INCLUDE_MAYBE_HH_

#include "panic.hh"
#include "utils.hh"

namespace mf {

template<typename T>
struct Maybe {
	T data;
	bool is_ok;

	// Check if data is safe to get value (not nil)
	bool ok() const { return is_ok; }

	// Causes data to be coerced to be non-ok
	void make_nil() { is_ok = false; }

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

	// Copy constructor
	Maybe(const Maybe& opt) : is_ok(opt.ok()){
		if(is_ok){ data = opt.data; }
	}
	Maybe(const T& val) : data(val) {
		is_ok = true;
	}

	// Copy assignment
	void operator=(const Maybe& opt){
		is_ok = opt.ok();
		if(is_ok){
			data = opt.data;
		}
	}
	void operator=(const T& val){
		data  = val;
		is_ok = true;
	}

	// Move constructor
	Maybe(Maybe&& opt) : is_ok(opt.ok()){
		if(is_ok){
			data = as_rval(opt.data);
			opt.is_ok = false;
		}
	}
	Maybe(T&& val) : data(as_rval(val)) {
		is_ok = true;
	}

	// Move assignment
	void operator=(Maybe&& opt){
		is_ok = opt.ok();
		if(is_ok){
			data = as_rval(opt.data);
		}
		opt.is_ok = false;
	}
	void operator=(T&& val){
		data  = as_rval(val);
		is_ok = true;
	}
};

}

#endif /* include guard */
