set(CMAKE_C_FLAGS "-nostdlib ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "-nostdlib -nostdlib++ ${CMAKE_CXX_FLAGS}")

add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(pl2d)
add_subdirectory(plds)
add_subdirectory(plac)