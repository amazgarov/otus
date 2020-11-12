call clean.cmd

cd build

set TRAVIS_BUILD_NUMBER=1.1
cmake ..
cmake --build .

:: test
:: cmake --build . --target run_tests

:: run
::cd debug
::ip_filter.tsv > ip_filter.exe

:: run GTest tests
:: make check

:: return back
cd ../