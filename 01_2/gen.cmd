call clean.cmd
cd build
set TRAVIS_BUILD_NUMBER=1.1
cmake ..
cmake --build .

:: return back
cd ../