cmake_minimum_required(VERSION 3.10)
project(distributed-kv-store)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost packages
find_package(Boost 1.74 REQUIRED COMPONENTS 
    system 
    thread
)

add_executable(kvstore 
    src/main.cpp
    src/network/http_server.cpp
    src/network/node_client.cpp
)

# Include directories
target_include_directories(kvstore PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(kvstore PRIVATE
    Boost::system
    Boost::thread
    pthread
)