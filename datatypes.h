#pragma once

#include <cstdint>

namespace alex {

using size   = std::size_t;
using byte   = std::uint8_t;
using rune   = std::int32_t;
using int8   = std::int8_t;
using int32  = std::int32_t;
using int64  = std::int64_t;
using uint8  = std::uint8_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using float32 = float;
using float64 = double;

using error   = const char *;

const error OK = nullptr;

// struct error {
//     const char *text;
//     
//     constexpr
//     error()
//         : text(nullptr)
//     {
//         
//     }
//     
//     constexpr
//     error(const char *text) 
//         : text(text)
//     {
//         
//     }
// };
}