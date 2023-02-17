#ifndef INCLUDE_DYN_ARRAY_HH_
#define INCLUDE_DYN_ARRAY_HH_

#include "panic.hh"
#include "types.hh"
#include "utils.hh"

namespace mf {

constexpr usize dyn_array_default_size = 16;
constexpr usize dyn_array_min_size = 4; // WARN: Changing this to be less than 3 can cause terrible things.

template<typename T>
struct Dyn_Array {
	T* data;
	usize lenght;
	usize capacity;

	// Get array lenght
	usize len() const { return lenght; }

	// Get underlying buffer capacity
	usize cap() const { return capacity; }

	// Bounds-checked access
	T& at(usize idx) & {
		if(idx >= lenght){
			panic("Out of bounds access");
			return data[0];
		}
		return data[idx];
	}
	// Syntax sugar for at()
	T& operator[](usize idx) & { return at(idx); }

	// Bounds-checked access
	const T& at(usize idx) const& {
		if(idx >= lenght){
			panic("Out of bounds access");
			return data[0];
		}
		return data[idx];
	}
	// Syntax sugar for at()
	const T& operator[](usize idx) const& { return at(idx); }

	// Bounds-checked access
	T&& at(usize idx) && {
		if(idx >= lenght){
			panic("Out of bounds access");
			return data[0];
		}
		return data[idx];
	}
	// Syntax sugar for at()
	T&& operator[](usize idx) && { return at(idx); }

	// Default constructor
	Dyn_Array(){
		lenght   = 0;
		capacity = dyn_array_default_size;
		data     = static_cast<T*>(::operator new(capacity * sizeof(T)));
	}

	// Construct with size hint
	Dyn_Array(usize hint){
		lenght   = 0;
		capacity = max(hint, dyn_array_min_size);
		data     = static_cast<T*>(::operator new(capacity * sizeof(T)));
	}

	// Destructor
	~Dyn_Array(){
		for(usize i = 0; i < lenght; i += 1){
			data[i].~T();
		}
		::operator delete(data);
	}

};

}

#endif /* include guard */
