#pragma once
#include <filesystem>
#include <string>

namespace http {

std::string mime(const std::filesystem::path& filename);

}  // namespace http
