// Bounds checked array with proper size info

#ifndef INCLUDE_ARRAY_HH_
#define INCLUDE_ARRAY_HH_

#include "types.hh"
#include "panic.hh"
#include <sys/types.h>

namespace mf {

template<typename T, usize N>
struct Array {
	T data[N];

	constexpr
	usize len() const { return N; }
	
	// Bounds checked access
	T& at(usize idx) & {
		if(idx >= N){
			mf::panic("Index out of bounds");
			return data[0];
		}
		return data[idx];
	}
	// Syntax sugar for at()
	T& operator[](usize idx) & { return this->at(idx); }

	// Bounds checked access (const)
	const T& at(usize idx) const& {
		if(idx >= N){
			mf::panic("Index out of bounds");
			return data[0];
		}
	}
	// Syntax sugar for at()
	const T& operator[](usize idx) const& { return this->at(idx); }

	// Equality
	bool eq(const Array& arr){
		for(usize i = 0; i < N; i += 1){
			if(arr.data[i] != data[i]){ return false; }
		}
		return true;
	}
	// Syntax sugar for eq()
	bool operator==(const Array& arr){ return this->eq(arr); }

	// Default constructor
	Array() {};

	// Copy constructor
	Array(const Array& arr){
		for(usize i = 0; i < N; i += 1){
			data[i] = arr.data[i];
		}
	}
	// Copy Assignment
	void operator=(const Array& arr){
		for(usize i = 0; i < N; i += 1){
			data[i] = arr.data[i];
		}
	}
};

}

#endif /* include guard */
