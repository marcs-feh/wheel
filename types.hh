// Useful type aliases.

#ifndef INCLUDE_MF_TYPES_HH_
#define INCLUDE_MF_TYPES_HH_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdalign.h>

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

using usize   = size_t;
using uintptr = uintptr_t;
using uint    = unsigned int;
using byte    = unsigned char;
using uint    = unsigned int;

#ifndef NO_SIGNED_SIZE
static_assert(sizeof(ptrdiff_t) == sizeof(size_t),
              "ptrdiff_t and size_t are different, cannot create `ssize` type "
              "alias, you can remove it by defining NO_SIGNED_SIZE");
using ssize = ptrdiff_t;
#endif

#endif /* header guard */
