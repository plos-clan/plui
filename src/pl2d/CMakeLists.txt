file(GLOB_RECURSE c_files "*.c")
file(GLOB_RECURSE cpp_files "*.cpp")
addlib(pl2d ${c_files} ${cpp_files})
mkheader_hpp(fb)