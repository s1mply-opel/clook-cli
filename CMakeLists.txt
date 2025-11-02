cmake_minimum_required(VERSION 3.15)
project(clook-cli LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include headers
include_directories(include)

# --- Library ---
file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
)

add_library(clook_lib ${SRC_FILES})
target_include_directories(clook_lib PUBLIC include)

# --- Main Executable ---
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE clook_lib)

# --- Tests ---
file(GLOB TEST_FILES
    "tests/*.cpp"
)

if(TEST_FILES)
    add_executable(${PROJECT_NAME}_tests ${TEST_FILES})
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE clook_lib)
    target_include_directories(${PROJECT_NAME}_tests PRIVATE include)
endif()

# --- Output directory ---
set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_tests clook_lib
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
