cd build
cmake --build .
cd debug
ip_filter.exe < "ip_filter.tsv" > output.txt

:: return back
cd ../../