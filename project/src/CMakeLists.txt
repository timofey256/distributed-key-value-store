cmake_minimum_required(VERSION 3.10)
project(distributed-kv-store)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BOOST_MIN_VERSION "1.74.0")
set(BOOST_REQUIRED_COMPONENTS
    system
    thread
)

message(STATUS "Looking for Boost ${BOOST_MIN_VERSION}...")
find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS ${BOOST_REQUIRED_COMPONENTS})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost ${BOOST_MIN_VERSION} not found. You need Boost and CMake to run this program:\n"
        "You can use scripts in tools/dependencies.\n"
        "We provided scripts for Debian, Fedora, Mac and Windows.\n"
        "\nAlternative installation:"
        "On Debian/Ubuntu:\n"
        "    sudo apt-get install libboost-all-dev\n"
        "On Fedora:\n"
        "    sudo dnf install boost boost-devel cmake\n"
        "On macOS:\n"
        "    brew install boost cmake\n"
        "On Windows with vcpkg:\n"
        "    vcpkg install boost:x64-windows\n"
        "Manual installation instructions: https://www.boost.org/doc/libs/1_74_0/more/getting_started/\n"
    )
endif()

message(STATUS "Found Boost version: ${Boost_VERSION}")
message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")

add_executable(kvstore 
    main.cpp
    network/http_server.cpp
    network/node_client.cpp
)

target_include_directories(kvstore
    PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(kvstore
    PRIVATE
        Boost::system
        Boost::thread
)

if(UNIX)
    target_link_libraries(kvstore PRIVATE pthread)
endif()