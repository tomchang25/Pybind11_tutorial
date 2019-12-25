CC:=g++

Ipybind:=`python3 -m pybind11 --includes`

project:=SimpleNumpy

src:=main.cpp
build:=Build.cpp

exe:=$(project).exe
so:=$(project)`python3-config --extension-suffix`

python:
	$(CC) $(build) -o $(so) -O3 -w -shared -std=c++17 -fPIC -D USE_PYTHON $(Ipybind)
cpp:
	$(CC) $(src) -o $(exe) -O3 -w -std=c++17 $(Ipybind)

.PHONY:clean
clean: 
	rm -rf $(exe) $(so)
