cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(http VERSION 2.7.1 LANGUAGES C CXX)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS include/*.hpp include/*.h)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.hpp src/*.cpp src/*.c)

add_library(http STATIC ${headers} ${sources})
target_compile_features(http PRIVATE cxx_std_20)
target_include_directories(http PRIVATE src PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

if(WIN32)
  target_include_directories(http PRIVATE res/msvc)
  target_sources(http PRIVATE res/msvc/sys/mman.c)
  set_source_files_properties(src/http_parser.c PROPERTIES COMPILE_FLAGS /wd4244)
  target_compile_definitions(http PRIVATE _UNICODE UNICODE WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

find_package(compat CONFIG REQUIRED)
target_link_libraries(http PRIVATE compat::compat)

find_package(ice CONFIG REQUIRED)
target_link_libraries(http PRIVATE ice::ice)

find_package(sql CONFIG REQUIRED)
target_link_libraries(http PRIVATE sql::sql)

find_package(ZLIB REQUIRED)
target_link_libraries(http PUBLIC ZLIB::ZLIB)

install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
install(TARGETS http EXPORT http LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(EXPORT http FILE http-targets.cmake NAMESPACE http:: DESTINATION lib/cmake/http)

include(CMakePackageConfigHelpers)

configure_package_config_file(res/config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/http-config.cmake
  INSTALL_DESTINATION lib/cmake/http)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/http-config-version.cmake
  VERSION ${PROJECT_VERSION} COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/http-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/http-config-version.cmake
  DESTINATION lib/cmake/http)

add_library(http::http ALIAS http)
