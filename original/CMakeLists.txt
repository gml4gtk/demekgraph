cmake_minimum_required(VERSION 3.5.0)

project(bakalarka)

# helper targets for different compile and link options
add_library(options INTERFACE)
target_include_directories(options INTERFACE include/)

add_library(debug_options INTERFACE)
target_compile_options(debug_options INTERFACE -g -std=c++17 -fsanitize=address -fsanitize=undefined)
target_link_libraries(debug_options INTERFACE options -fsanitize=address -fsanitize=undefined)

add_library(fast_options INTERFACE)
target_compile_options(fast_options INTERFACE -O2 -std=c++17)
target_link_libraries(fast_options INTERFACE options)


# actual targets
add_executable(draw example/draw/draw.cpp)
target_link_libraries(draw PRIVATE fast_options)

add_executable(cycl stats/cyclify.cpp)
target_link_libraries(cycl PRIVATE fast_options)
target_include_directories(cycl PRIVATE example/draw/)

add_executable(stats stats/stats.cpp)
target_link_libraries(stats PRIVATE fast_options)
target_include_directories(stats PRIVATE example/draw/)

add_executable(simple example/simple/simple.cpp)
target_link_libraries(simple PRIVATE fast_options)
target_include_directories(simple PRIVATE example/draw/)
