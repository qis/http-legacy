// ISC License
//
// Copyright (c) 2017 Alexej Harm
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS AL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// Usage:
//
// std::string src = "test";
//
// const auto hash = zlib::crc(src);
// assert(hash.value() == 0xD87F7E0C);
//

#pragma once
#include <zlib.h>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <cstdint>

namespace zlib {

class crc {
public:
  crc() noexcept {
    reset();
  }

  crc(std::string_view text) {
    reset();
    append(text.data(), text.size());
  }

  void append(const void* data, std::size_t size) {
    value_ = crc32_z(value_, static_cast<const unsigned char*>(data), size);
  }

  void reset() noexcept {
    value_ = crc32_z(0L, nullptr, 0);
  }

  std::uint32_t value() const {
    return value_;
  }

  std::string str(bool uppercase = false) const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::hex;
    if (uppercase) {
      oss << std::uppercase;
    }
    oss << std::setw(4) << value();
    return oss.str();
  }

private:
  std::uint32_t value_ = 0;
};

std::ostream& operator<<(std::ostream& os, const crc& hash) {
  const auto flags = os.flags();
  os << std::setfill('0') << std::hex << std::setw(4) << hash.value();
  os.flags(flags);
  return os;
}

}  // namespace zlib