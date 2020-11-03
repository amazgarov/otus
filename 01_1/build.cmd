rmdir /S /Q build
mkdir build
cd build
set TRAVIS_BUILD_NUMBER=1.1
::set BOOST_ROOT=C:\Projects\vcpkg-master\installed\x64-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\Projects\vcpkg-master\scripts\buildsystems\vcpkg.cmake

:: build
cmake --build .

:: run
cd debug
helloworld_cli.exe

:: return back
cd ../../