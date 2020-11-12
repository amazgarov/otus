cd build
set TRAVIS_BUILD_NUMBER=1.1

:: build
cmake --build .

:: run
cd debug
ip_filter.exe < "ip_filter.tsv" > output.txt

:: return back
cd ../../