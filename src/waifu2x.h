// waifu2x implemented with ncnn library

#ifndef WAIFU2X_H
#define WAIFU2X_H

#include <string>

// ncnn
#include "net.h"
#include "gpu.h"

class Waifu2x
{
public:
    Waifu2x(int gpuid);
    ~Waifu2x();

#if _WIN32
    int load(const std::wstring& parampath, const std::wstring& modelpath);
#else
    int load(const std::string& parampath, const std::string& modelpath);
    int predict(const std::string& input, const std::string& ounput);
#endif

    int process(const ncnn::Mat& inimage, ncnn::Mat& outimage) const;
    
    void set_noise(int _noise) {this->noise = _noise;}
    int get_noise() {return this->noise;}
    
    void set_scale(int _scale) {this->scale = _scale;}
    int get_scale() {return this->scale;}
    
    void set_tilesize(int _tilesize) {this->tilesize = _tilesize;}
    int get_tilesize() {return this->tilesize;}
    
    void set_prepadding(int _prepadding) {this->prepadding = _prepadding;}
    int get_prepadding() {return this->prepadding;}
    
    void init_ncnn(){
        printf("init_ncnn\n");
        ncnn::create_gpu_instance();
        printf("create_gpu_instance\n");
    }
    void destroy_ncnn(){
        printf("destroy_ncnn\n");
        ncnn::destroy_gpu_instance();
        printf("destroy_gpu_instance\n");
    }
public:
    // waifu2x parameters
    int noise;
    int scale;
    int tilesize;
    int prepadding;

private:
    ncnn::Net net;
    ncnn::Pipeline* waifu2x_preproc;
    ncnn::Pipeline* waifu2x_postproc;
};

#endif // WAIFU2X_H
