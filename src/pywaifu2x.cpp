#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <boost/python.hpp>
//#include <boost/numpy.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <Python.h> 

#if _WIN32
// image decoder and encoder with wic
#include "wic_image.h"
#else // _WIN32
// image decoder and encoder with stb
#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif // _WIN32

#include "waifu2x.h"
//*/
int Waifu2x::predict(const std::string& input, const std::string& output)
{
    unsigned char* pixeldata = 0;
    int w;
    int h;
    int c;
    pixeldata = stbi_load(input.c_str(), &w, &h, &c, 3);
    ncnn::Mat inimage = ncnn::Mat(w, h, (void*)pixeldata, (size_t)3, 3);
    ncnn::Mat outimage = ncnn::Mat(w * scale, h * scale, (size_t)3u, 3);
    
    int res = process(inimage, outimage);
    
    int success = stbi_write_png(output.c_str(), outimage.w, outimage.h, 3, outimage.data, 0);
    
    pixeldata = (unsigned char*)inimage.data;
#if _WIN32
    free(pixeldata);
#else
    stbi_image_free(pixeldata);
#endif
    if (success)
    {
#if _WIN32
        fwprintf(stderr, L"%ls -> %ls done\n", input.c_str(), output.c_str());
#else
        fprintf(stderr, "%s -> %s done\n", input.c_str(), output.c_str());
#endif
    }
    else
    {
#if _WIN32
        fwprintf(stderr, L"encode image %ls failed\n", output.c_str());
#else
        fprintf(stderr, "encode image %s failed\n", output.c_str());
#endif
    }
    return success;
}//*/

BOOST_PYTHON_MODULE(pywaifu2x)
{
    using namespace boost::python;
    //def("greet", greet);
    //def("double_string", double_string);
    //def("mywrapper", double_string);
    //boost::python::class_<Data, shared_ptr<Data>, boost::noncopyable >("Data", boost::python::no_init);
    class_<Waifu2x, boost::shared_ptr<Waifu2x> >("pywaifu2x", init<int>())
    //("Data", no_init)
    //("Data", init<>())
    //("Data", init<int,int,std::string>())
    
        .def("load", &Waifu2x::load)
        //.def("predict", &Waifu2x::predict)
        .def("predict", &Waifu2x::predict)
        
        .def("init_ncnn", &Waifu2x::init_ncnn)
        .def("destroy_ncnn", &Waifu2x::destroy_ncnn)
        
        .def("set_noise", &Waifu2x::set_noise)
        .def("get_noise", &Waifu2x::get_noise)
        
        .def("set_scale", &Waifu2x::set_scale)
        .def("get_scale", &Waifu2x::get_scale)
        
        .def("set_tilesize", &Waifu2x::set_tilesize)
        .def("get_tilesize", &Waifu2x::get_tilesize)
        
        .def("set_prepadding", &Waifu2x::set_prepadding)
        .def("get_prepadding", &Waifu2x::get_prepadding);
    //.def("SaveAll", &WrapperData::SaveAll)
    //.def("RunAll", &WrapperData::RunAll);
    //.def("__init__", make_constructor(&WrapperFuncs::initWrapper))
    //.def("Print2", &WrapperFuncs::Print );
}