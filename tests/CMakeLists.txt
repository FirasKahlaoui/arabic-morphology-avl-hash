cmake_minimum_required(VERSION 3.10)
project(ArabicMorphologyTests)

set(CMAKE_CXX_STANDARD 17)

# Locate GTest or use a simple main for now if GTest isn't available
# For phase 1, we will just create a placeholder CMakeLists for tests

add_executable(run_tests test_main.cpp)

# Link against project sources if needed, or link a library
# target_link_libraries(run_tests ...)
