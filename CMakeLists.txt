cmake_minimum_required (VERSION 2.6)
project (Dodger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src)
aux_source_directory(src SRC)

add_executable(test_point tests/test_point.cpp ${SRC})
add_executable(test_st_point tests/test_st_point.cpp ${SRC})
add_executable(test_grid tests/test_grid.cpp ${SRC})
add_executable(test_roadmap tests/test_roadmap.cpp ${SRC})
