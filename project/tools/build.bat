@echo off

where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo cmake not found. Please install cmake from https://cmake.org/download/
    exit /b 1
)

where cl >nul 2>&1
if %errorlevel% neq 0 (
    echo Microsoft Visual C++ not found. Please install Visual Studio with C++ workload
    exit /b 1
)

cd ../src/
mkdir build
cd build
cmake ..
cmake --build .