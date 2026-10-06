# CGCLab

Software Rasterization Project for Visual Computing and Computer Science Bachelor students at Coburg University.

## Create Individual Assignments

1. Create PDF Assignment descriptions
    1. Go to root folder of cgclab
    2. Run `make -f labtools/Makefile`
2. Create Stubs
    1. Go to lab folder
    2. Run `cgclab/labtools/CreateAssignmentStubs.sh`

## macOS + CLion setup

The macOS pre-installed clang is not compiled with OpenMP, but the one from Homebrew is. Run `brew install llvm`, then
create a new toolchain in CLion with the C and C++ compiler paths set to `/opt/homebrew/opt/llvm/bin/clang` and
`.../clang++`, and select it in the CMake profile.

Only the top-level `CMakeLists.txt` needs to be loaded, CLion will detect the executables of all subfolders
automatically.

To use `clang-format`, select it as the formatting engine in the C/C++ code style settings and set
`/opt/homebrew/opt/llvm/bin/clang-format` as the external path. Also enable _Reformat code_ under _Actions on Save_.
