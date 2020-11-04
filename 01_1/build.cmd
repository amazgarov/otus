rmdir /S /Q build
mkdir build
cd build
set TRAVIS_BUILD_NUMBER=1.1
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\Projects\vcpkg-master\scripts\buildsystems\vcpkg.cmake

:: build
cmake --build .

:: test
cmake --build . --target run_tests

:: run
cd debug
helloworld_cli.exe

:: return back
cd ../../