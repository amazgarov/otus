cd build
cmake --build .
cd debug
ip_filter.exe < "ip_filter.tsv" > output.txt
certutil -hashfile output.txt md5

:: return back
cd ../../