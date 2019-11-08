#pragma once
#include <cstddef>

namespace http {
namespace detail {

constexpr bool string_equal(const char* a, const char* b, std::size_t size) {
  return size == 0 ? true : *a != *b ? false : string_equal(a + 1, b + 1, size - 1);
}

template <std::size_t N>
constexpr bool string_equal(const char* a, std::size_t size, const char (&b)[N]) {
  return size != N - 1 ? false : string_equal(a, b, size);
}

}  // namespace detail
}  // namespace http