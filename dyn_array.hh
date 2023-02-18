#ifndef INCLUDE_DYN_ARRAY_HH_
#define INCLUDE_DYN_ARRAY_HH_

#include "panic.hh"
#include "types.hh"
#include "utils.hh"

namespace mf {

constexpr usize dyn_array_default_size = 16;
constexpr usize dyn_array_min_size     = 4;
constexpr float dyn_array_growth_fact  = 1.75;

template<typename T>
struct Dyn_Array {
	T* data;
	usize lenght;
	usize capacity;

	// Get array lenght
	usize len() const { return lenght; }

	// Get underlying buffer capacity
	usize cap() const { return capacity; }

	// Resize underlying buffer
	void resize(usize size){
		usize new_cap = max(size, dyn_array_min_size);
		usize new_len = min(size, lenght);
		T* new_data   = static_cast<T*>(::operator new(new_cap * sizeof(T)));
		for(usize i = 0; i < new_len; i += 1){
			new (&(new_data[i])) T(as_rval(data[i]));
		}
		::operator delete(data);
		data     = new_data;
		lenght   = new_len;
		capacity = new_cap;
	}

	// Add element to end of array
	void add(const T& e){
		if((lenght + 1) >= capacity){
			resize(static_cast<usize>((capacity + 1) * dyn_array_growth_fact));
		}
		new (&(data[lenght])) T(e);
		lenght += 1;
	}

	// Remove element from end of array
	void del(){
		if(lenght == 0){ return; }
		lenght -= 1;
	}

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

static_assert(mf::dyn_array_default_size >= mf::dyn_array_min_size, "Default size must be bigger than min size");
static_assert(mf::dyn_array_min_size > 3, "Min size must be larger than 3");
static_assert(mf::dyn_array_growth_fact > 1.0, "Growth factor must be greater than 1.0");

#endif /* include guard */
