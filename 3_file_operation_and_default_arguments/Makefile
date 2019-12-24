CC:=g++

Ipybind:=`python3 -m pybind11 --includes`

project:=File

src:=$(project).cpp
build:=Build.cpp

exe:=$(project).exe
so:=$(project)`python3-config --extension-suffix`

cpp:
	$(CC) $(src) main.cpp -o $(exe) -O3 -std=c++17
python:
	$(CC) $(build) $(src) -o $(so) -O3 -shared -std=c++17 -fPIC -D USE_PYTHON $(Ipybind)

.PHONY:clean
clean: 
	rm -rf $(exe) $(so)
