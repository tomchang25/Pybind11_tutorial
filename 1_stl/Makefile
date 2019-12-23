CC:=g++

Ipybind:=`python3 -m pybind11 --includes`

src:=STL.cpp
build:=Build.cpp

exe:=STL.exe
so:=STL`python3-config --extension-suffix`

python:
	$(CC) $(build) $(src) -o $(so) -O3 -Wall -shared -std=c++17 -fPIC -D USE_PYTHON $(Ipybind)
cpp:
	$(CC) $(src) -o $(exe) -O3 -std=c++17 $(Ipybind)

.PHONY:clean
clean: 
	rm -rf $(exe) $(so)
