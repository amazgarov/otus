call clean.cmd
cd build
cmake ..
cmake --build .

cd debug
allocator.exe

:: return back
cd ../../

:: return back
::cd ../