set(CMAKE_C_FLAGS "-nostdlib")
set(CMAKE_CXX_FLAGS "-nostdlib -nostdlib++")

add_subdirectory(both)
add_subdirectory(c)
add_subdirectory(cpp)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(plac)