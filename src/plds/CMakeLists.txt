add_subdirectory(base)
add_subdirectory(client)
add_subdirectory(server)
file(GLOB_RECURSE c_files_1 "base/*.c")
file(GLOB_RECURSE cpp_files_1 "base/*.cpp")
file(GLOB_RECURSE c_files_2 "client/*.c")
file(GLOB_RECURSE cpp_files_2 "client/*.cpp")
file(GLOB_RECURSE c_files_3 "server/*.c")
file(GLOB_RECURSE cpp_files_3 "server/*.cpp")
addlib(plds ${c_files_1} ${cpp_files_1} ${c_files_2} ${cpp_files_2} ${c_files_3} ${cpp_files_3})