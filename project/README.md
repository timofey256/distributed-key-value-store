# Distributed key-value store

## How to use?
### 0. Libraries
You will need `boost`, `cmake` and `g++`. You can either install using the below instructions, or use our tooling in `tools/dependencies/`.

#### For Windows:
_Option 1:_
- Go to `https://cmake.org/download/` and install the latest distrubution.
- Install `boost` with `tools/dependencies/install_windows.bat`. Run this program as administrator. 
-  

_Option 2:_
- Go to `https://cmake.org/download/` and install the latest distrubution.
- Install `boost` yourself from `https://www.boost.org/doc/libs/1_82_0/more/getting_started/windows.html`.

#### For Linux/Mac:
- Use `tools/dependencies/install_*.sh`.

### 1. Build the project itself
Then, use `tools/build.sh` for Linux/Mac or `tools/build.bat` for Windows.

### 2. Run the program
Go to `src/build` and run the program.
