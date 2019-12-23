// pybind11_exp.cpp
#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#include "xtensor/xarray.hpp"
#include "xtensor/xview.hpp"
#include "xtensor/xcsv.hpp"
#include "xtensor/xadapt.hpp"

// bind numpy to xtensor
#define FORCE_IMPORT_ARRAY                // numpy C api loading
#include "xtensor-python/pyarray.hpp"     // Numpy bindings

#include "mat_warper.h"

namespace py = pybind11;

using namespace std;

void hello_world(){
    py::print("Hello world! ");
}

string say_hello(string name){
    return "太陽公公出來了, " + name + "說你好.";
}




class Rescale {
public:
    int output_size;
    Rescale(int output_size) : output_size(output_size) { } 
    
    tuple<py::array_t<unsigned char>,xt::pyarray<double>> operator()(py::array_t<unsigned char>& image, xt::pyarray<double>& landmark){
        cv::Mat srcMat = numpy_uint8_3c_to_cv_mat(image);

        double h = srcMat.cols;
        double w = srcMat.rows;
        double new_h, new_w;

        if (h > w){
            new_h = this->output_size * h / w;
            new_w = this->output_size;
        }
        else{
            new_h = this->output_size;
            new_w = this->output_size * w / h;
        }
        
        cv::Mat dstMat;
        cv::resize( srcMat, dstMat, cv::Size(new_h, new_w) );
        auto new_image =  cv_mat_uint8_3c_to_numpy(dstMat);

        xt::xarray<double> offset = {new_w / w, new_h / h};
        auto new_landmark = landmark * offset;
        
        return tuple<py::array_t<unsigned char>,xt::pyarray<double>>(new_image,new_landmark);

    }
    
    tuple<cv::Mat,xt::xarray<double>> call(cv::Mat srcMat, xt::xarray<double> landmark){
        double h = srcMat.cols;
        double w = srcMat.rows;
        double new_h, new_w;
        
        
        if (h > w){
            new_h = this->output_size * h / w;
            new_w = this->output_size;
        }
        else{
            new_h = this->output_size;
            new_w = this->output_size * w / h;
        }
        

        cv::Mat dstMat;
        cv::resize( srcMat, dstMat, cv::Size(new_h, new_w) );
        xt::xarray<double> offset = {new_w / w, new_h / h};

        auto new_landmark = landmark * offset;

        return tuple<cv::Mat,xt::pyarray<double>>(dstMat,new_landmark);

    }
};

class RandomCrop {
public:
    int output_size;
    RandomCrop(int output_size) : output_size(output_size) { }
    
    tuple<xt::pyarray<unsigned>,xt::pyarray<double>>  operator()(xt::pyarray<unsigned>& image, xt::pyarray<double>& landmark){
        
        int h = image.shape(0);
        int w = image.shape(1);
        int new_h = this->output_size;
        int new_w = this->output_size;

        int top = rand()%(h - new_h);
        int left = rand()%(w - new_w);
        
        auto new_image = xt::view(image, xt::range(top,top + new_h), xt::range(left,left + new_w));
        xt::xarray<int> offset = {left, top};
        xt::xarray<double> new_landmark = landmark - offset;
        
        return {new_image , new_landmark}; 
    }
    
    tuple<cv::Mat,xt::xarray<double>> call(cv::Mat srcMat, xt::xtensor<double, 2> landmark){
        int h = srcMat.cols;
        int w = srcMat.rows;
        int new_h = this->output_size;
        int new_w = this->output_size;

        int top = rand()%(h - new_h);
        int left = rand()%(w - new_w);
        
        auto newMat = srcMat(cv::Rect(0,0,new_w,new_h));
        //auto new_image = xt::view(image, xt::range(top,top + new_h), xt::range(left,left + new_w));

        xt::xarray<int> offset = {left, top};
        xt::pyarray<double> new_landmark = landmark - offset;
        return {newMat , new_landmark}; 


    }
};

class Myclass {
public:
    // parameter
    int output_size;
    // init
    Myclass(int output_size) : output_size(output_size) { } 
    
    vector<int> get(){        
        return vector<int>(this->output_size);
    }
    
    xt::pyarray<double> sub(xt::pyarray<double> arr,int num){
        return arr - num;
    }
};


tuple<xt::pyarray<double>,xt::pyarray<double>>createFaceLandmarksArray(string csv_file,string root_dir)
{
    auto rescale = Rescale(256);
    //auto rescale = Rescale(224);
    auto crop = RandomCrop(224);
    
    xt::xtensor<double, 3>::shape_type landmarks_shape = {0,68,2};
    xt::xtensor<double, 3> landmarks(landmarks_shape);
    
    xt::xtensor<double, 4>::shape_type images_shape = {0,224,224,3};
    xt::xtensor<double, 4> images(images_shape);

    ifstream data(csv_file);
    string line;
    
    // ignore first line
    getline(data,line);

    while(getline(data,line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        
        unsigned index = 0;
        cv::Mat image;

        xt::xtensor<double, 2>::shape_type landmark_shape = {68,2};
        xt::xtensor<double, 2> landmark(landmark_shape);
        
        while(getline(lineStream,cell,','))
        {
            if (index == 0){
                image = cv::imread(root_dir + cell, CV_LOAD_IMAGE_COLOR);
            }
            else{
                landmark((index-1)/2,(index-1)%2) = stod(cell);
            }
            
            index += 1;
        }

        
        tie(image, landmark) = rescale.call(image,landmark);
        tie(image, landmark) = crop.call(image,landmark);
        
        size_t size = image.total();
        size_t channels = image.channels();
        std::vector<int> shape = {image.cols, image.rows, image.channels()};
                
        xt::xarray<double> xarr_image = xt::adapt((float*)image.data, size * channels, xt::no_ownership(), shape);

        auto new_image = xt::view(xarr_image, xt::newaxis(), xt::all(), xt::all(), xt::all());
        auto new_landmark = xt::view(landmark, xt::newaxis(), xt::all(), xt::all());
        images = xt::concatenate(xtuple(images, new_image),0);
        landmarks = xt::concatenate(xtuple(landmarks, new_landmark),0);

    }


    
    return {images,landmarks};
    /*
    landmarks_frame = pd.read_csv(csv_file)

    for idx in range(landmarks_frame.shape[0]):

image, landmark = rescale(image, landmark)
        image, landmark = crop(image, landmark)
        image = image[np.newaxis,:]
        landmark = landmark[np.newaxis,:]

        images = np.append(images,image, axis=0)
        landmarks = np.append(landmarks,landmark, axis=0)
        #show_landmarks(image[0], landmark[0])
    */
}
PYBIND11_MODULE(test, m) {
  xt::import_numpy();

  m.doc() = "pybind11 example plugin";      // module doc string
  m.def("hello_world",&hello_world);
  m.def("say_hello",&say_hello);
  m.def("createFaceLandmarksArray",&createFaceLandmarksArray);
    
  py::class_<Rescale>(m, "Rescale")
    .def(py::init<int>())
    .def("__call__",&Rescale::operator());

  py::class_<RandomCrop>(m, "RandomCrop")
    .def(py::init<int>())
    .def("__call__",&RandomCrop::operator());

  py::class_<Myclass>(m, "Myclass")
    .def(py::init<int>())
    .def("get",&Myclass::get)
    .def("sub",&Myclass::sub);

}
