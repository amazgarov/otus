cd build/debug

:: by using tests executable
tests

:: starndard way
::cmake --build . --target RUN_TESTS

:: by using custom target
::cmake --build . --target check

cd ../../