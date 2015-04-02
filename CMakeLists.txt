cmake_minimum_required (VERSION 2.6)
project (Dodger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Ofast -march=native -flto -fwhole-program -g")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src)
aux_source_directory(src SRC)

# static library
add_library(dodger STATIC ${SRC})

# tests
add_executable(test_point tests/test_point.cpp)
add_executable(test_st_point tests/test_st_point.cpp)
add_executable(test_grid tests/test_grid.cpp)
add_executable(test_roadmap tests/test_roadmap.cpp)
add_executable(test_search tests/test_search.cpp)

# examples
add_executable(frogger examples/frogger.cpp)
add_executable(pendulum examples/pendulum.cpp)
add_executable(stochastic examples/stochastic.cpp)
add_executable(replanner examples/replanner.cpp)
add_executable(potential examples/potential.cpp)

# experiments
add_executable(exp_planner_speed_noise_0 experiments/planner_speed_noise_0.cpp)
add_executable(exp_pf_speed_noise_0 experiments/pf_speed_noise_0.cpp)
add_executable(exp_planner_wait_0 experiments/planner_wait_0.cpp)


# linking libdodger
target_link_libraries(test_point dodger)
target_link_libraries(test_st_point dodger)
target_link_libraries(test_grid dodger)
target_link_libraries(test_roadmap dodger)
target_link_libraries(test_search dodger)
target_link_libraries(frogger dodger)
target_link_libraries(pendulum dodger)
target_link_libraries(stochastic dodger)
target_link_libraries(replanner dodger)
target_link_libraries(potential dodger)
target_link_libraries(exp_planner_speed_noise_0 dodger)
target_link_libraries(exp_pf_speed_noise_0 dodger)
target_link_libraries(exp_planner_wait_0 dodger)
