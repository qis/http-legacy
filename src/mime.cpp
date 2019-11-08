#include <http/mime.hpp>
#include <map>

namespace http {
namespace {

std::map<std::string, std::string> mime_map() {
  std::map<std::string, std::string> map;

  // Web
  map["htm"] = "text/html; charset=utf-8";
  map["html"] = "text/html; charset=utf-8";
  map["css"] = "text/css; charset=utf-8";
  map["js"] = "application/javascript; charset=utf-8";
  map["txt"] = "text/plain; charset=utf-8";
  map["text"] = "text/plain; charset=utf-8";

  // Data
  map["json"] = "application/json";
  map["pdf"] = "application/pdf";
  map["xml"] = "application/xml";

  // Archives
  map["zip"] = "application/zip";

  // Images
  map["jpg"] = "image/jpeg";
  map["jpeg"] = "image/jpeg";
  map["png"] = "image/png";
  map["gif"] = "image/gif";
  map["ico"] = "image/x-icon";

  // Vector
  map["svg"] = "image/svg+xml";

  // Fonts
  map["ttf"] = "application/font-ttf";
  map["eot"] = "application/vnd.ms-fontobject";
  map["otf"] = "application/font-otf";
  map["woff"] = "application/font-woff";

  // Multimedia
  map["avi"] = "video/avi";
  map["mp3"] = "audio/mpeg";
  map["mp4"] = "video/mp4";
  map["m4v"] = "video/mp4";
  map["m4a"] = "audio/mp4";
  map["ogg"] = "audio/ogg";
  map["oga"] = "audio/ogg";
  map["ogv"] = "video/ogg";
  map["webm"] = "video/webm";

  // Certificates
  map["key"] = "application/x-pem-file";
  map["cer"] = "application/x-pem-file";
  map["crl"] = "application/x-pem-file";
  map["pem"] = "application/x-pem-file";
  map["pfx"] = "application/x-pkcs12";

  // Sources
  map["asm"] = "text/plain; charset=utf-8";
  map["c"] = "text/plain; charset=utf-8";
  map["cc"] = "text/plain; charset=utf-8";
  map["c++"] = "text/plain; charset=utf-8";
  map["cpp"] = "text/plain; charset=utf-8";
  map["cxx"] = "text/plain; charset=utf-8";
  map["h"] = "text/plain; charset=utf-8";
  map["h++"] = "text/plain; charset=utf-8";
  map["hpp"] = "text/plain; charset=utf-8";
  map["hxx"] = "text/plain; charset=utf-8";
  map["ipp"] = "text/plain; charset=utf-8";

  return map;
}

}  // namespace

std::string mime(const std::filesystem::path& filename) {
  static auto map = mime_map();
  auto str = filename.string();
  auto pos = str.find_last_of('.');
  if (pos != std::string::npos) {
    str.erase(0, pos + 1);
  } else {
    return "text/html";
  }
  auto it = map.find(str);
  if (it != map.end()) {
    return it->second;
  }
  return "application/octet-stream";
}

}  // namespace http
