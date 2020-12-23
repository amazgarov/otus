cd build
rmdir /S /Q Debug
cmake --build .
cd debug
allocator.exe

:: return back
cd ../../