cmake_minimum_required(VERSION 3.10)
project(Homework9)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Word Ladder executable
add_executable(ladder
    ladder_main.cpp
    ladder.cpp
)

# Dijkstra's algorithm executable
add_executable(dijkstras
    dijkstras_main.cpp
    dijkstras.cpp
)

# Copy resource files to build directory
configure_file(words.txt words.txt COPYONLY)
configure_file(small.txt small.txt COPYONLY)
configure_file(medium.txt medium.txt COPYONLY)
configure_file(large.txt large.txt COPYONLY)
configure_file(largest.txt largest.txt COPYONLY)

# Add GTest support if available
find_package(GTest)
if(GTEST_FOUND)
    enable_testing()
    
    # Create test executable for ladder
    add_executable(ladder_test
        ladder_test.cpp
        ladder.cpp
    )
    target_link_libraries(ladder_test PRIVATE GTest::GTest GTest::Main)
    add_test(NAME LadderTests COMMAND ladder_test)
    
    # Create test executable for dijkstras
    add_executable(dijkstras_test
        dijkstras_test.cpp
        dijkstras.cpp
    )
    target_link_libraries(dijkstras_test PRIVATE GTest::GTest GTest::Main)
    add_test(NAME DijkstrasTests COMMAND dijkstras_test)
endif()