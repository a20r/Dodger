cmake_minimum_required (VERSION 2.6)
project (Dodger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src)
aux_source_directory(src SRC)

add_library(libdodger STATIC ${SRC})

add_executable(test_point tests/test_point.cpp)
add_executable(test_st_point tests/test_st_point.cpp)
add_executable(test_grid tests/test_grid.cpp)
add_executable(test_roadmap tests/test_roadmap.cpp)
add_executable(test_search tests/test_search.cpp)

target_link_libraries(test_point libdodger)
target_link_libraries(test_st_point libdodger)
target_link_libraries(test_grid libdodger)
target_link_libraries(test_roadmap libdodger)
target_link_libraries(test_search libdodger)
