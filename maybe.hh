#ifndef INCLUDE_MAYBE_HH_
#define INCLUDE_MAYBE_HH_

#include "panic.hh"
#include "utils.hh"

namespace mf {

template<typename T>
struct Maybe {
	T data;
	bool is_ok;

	// Check if data is safe to get()
	bool ok() const { return is_ok; }

	// Causes data to be coerced to be non-ok
	void make_nil() { is_ok = false; }

	T& get() & {
		panic_assert(is_ok, "Cannot get() from nil");
		return data;
	}

	const T& get() const& {
		panic_assert(is_ok, "Cannot get() from nil");
		return data;
	}

	T&& get() && {
		panic_assert(is_ok, "Cannot get() from nil");
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
	void operator=(const Maybe<T>& opt){
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
	Maybe(T&& val) : data(as_rval(val)) {
		is_ok = true;
	}
	Maybe(Maybe&& opt) : is_ok(opt.ok()){
		if(is_ok){
			data = as_rval(opt.data);
			opt.is_ok = false;
		}
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
