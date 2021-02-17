cd build
rmdir /S /Q Debug
cmake --build .
cd debug
print_ip.exe

:: return back
cd ../../