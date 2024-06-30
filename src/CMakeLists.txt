set(CMAKE_C_FLAGS "-nostdlib")
set(CMAKE_CXX_FLAGS "-nostdlib -nostdlib++")

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(pl2d)
add_subdirectory(plds)
add_subdirectory(plac)