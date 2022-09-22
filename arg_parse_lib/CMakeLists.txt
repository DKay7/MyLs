add_library(arg_parser STATIC arg_parser.cpp)

target_include_directories(
  arg_parser PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(arg_parser err_lib)