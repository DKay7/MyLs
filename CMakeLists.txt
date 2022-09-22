cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(my_ls VERSION 2.0)

add_subdirectory(err_lib)
add_subdirectory(arg_parse_lib)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D _DEBUG  -g -ggdb3 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wno-narrowing -Wno-old-style-cast -fcheck-new -fstack-protector -fsanitize=address -fsanitize=alignment -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vptr -Og")

add_executable(${PROJECT_NAME} main.cpp ls_core.cpp)
target_link_libraries(${PROJECT_NAME} arg_parser)
target_link_libraries(${PROJECT_NAME} err_lib)
