#ifndef INCLUDE_UTILS_HH_
#define INCLUDE_UTILS_HH_

template <typename T>
struct Strip_Ref { typedef T Type; };

template <typename T>
struct Strip_Ref<T&> { typedef T Type; };

template <typename T>
struct Strip_Ref<T&&> { typedef T Type; };

template<typename T>
typename Strip_Ref<T>::Type&&
as_rval(T&& a) noexcept {
	typedef typename Strip_Ref<T>::Type&& Rvalue_Ref;
	return static_cast<Rvalue_Ref>(a);
}

template<typename T>
const T& min(const T& a, const T& b){
	return (a < b) ? a : b;
}

template<typename T>
const T& max(const T& a, const T& b){
	return (a > b) ? a : b;
}

template<typename T>
void swap(T& a, T& b){
	T t = as_rval(a);
	a   = as_rval(b);
	b   = as_rval(t);
}

#endif /* include guard */
