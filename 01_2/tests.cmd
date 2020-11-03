cd build/debug

:: by using tests executable
tests

:: standard CMake way for Windows
::cmake --build . --target RUN_TESTS

:: by using custom target
::cmake --build . --target check

cd ../../