cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(plui VERSION 0.0.0)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

enable_testing()
include(GoogleTest)

include_directories(${PROJECT_SOURCE_DIR}/include)

# set(CMAKE_C_FLAGS "-std=gnu2x -flto -Ofast -march=native")
# set(CMAKE_CXX_FLAGS "-std=gnu++2b -flto -Ofast -march=native")
set(CMAKE_C_FLAGS "-std=gnu2x -flto -Og")
set(CMAKE_CXX_FLAGS "-std=gnu++2b -flto -Og")

include(cmake/gtest)
include(cmake/show-flags) 
include(cmake/mklib)
include(cmake/mkheader)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
