cmake_minimum_required(VERSION 3.10)
project(kozlowski_stealer)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(kozlowski_stealer main.cpp)

# Link Winsock library
target_link_libraries(kozlowski_stealer ws2_32)
