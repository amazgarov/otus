cd build
set TRAVIS_BUILD_NUMBER=1.1

:: build
cmake --build .

:: return back
cd ../