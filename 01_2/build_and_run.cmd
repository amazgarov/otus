cd build
set TRAVIS_BUILD_NUMBER=1.1
cmake --build .
cd debug
ip_filter.exe < "ip_filter.tsv" > output.txt
certutil -hashfile output.txt md5

:: return back
cd ../../