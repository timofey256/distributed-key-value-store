cmake_minimum_required(VERSION 3.10)
project(distributed-kv-store)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.74 REQUIRED COMPONENTS 
    system 
    thread
)

add_executable(kvstore 
    main.cpp
    network/http_server.cpp
    network/node_client.cpp
)

target_include_directories(kvstore PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(kvstore PRIVATE
    Boost::system
    Boost::thread
    pthread
)