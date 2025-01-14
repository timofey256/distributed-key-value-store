# Distributed key-value store

## How to use?
### 0. Libraries
You will need `boost`, `cmake` and `g++`. You can either install using the below instructions, or use our tooling in `tools/dependencies/`.

#### For Windows:
- You need `g++`. Install Visual Studio if you don't have it.
- You need CMake. Go to `https://cmake.org/download/` and install the latest distrubution.
- You need `boost`. Try to install it with `tools/dependencies/install_boost.bat`. Run this script as administrator. 

Fallback: if any of these steps fail, google "how to install X on Windows" and proceed. Or just use Linux. :)

#### For Linux/Mac:
Use `tools/dependencies/install_*.sh`. We support Debian/Ubuntu, Fedora and Mac now. 

Scripts are trivial, so if your distribution is not covered by the above, just use commands counterparts on your system.

### 1. Build the project itself
Then, use `tools/build.sh` for Linux/Mac or `tools/build.bat` for Windows.

### 2. Run the program
Go to `src/build` and run the program.
