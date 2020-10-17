#ifndef Lector_H
#define Lector_H

#define cimg_use_jpeg 1
#include "CImg.h"

namespace fs = std::__fs::filesystem;

struct Lector {
    Lector();

    vector<vector<float>>  Vectorizar(CImg<float>& img) {
        std::string path("faces94");
        std::string ext(".jpg");
        for (auto &p : fs::recursive_directory_iterator(path)) {
            if (p.path().extension() == ext)
                std::cout << p.path().stem().string() << '\n';
        }
        // vector<float> R;
        // cimg_forXY(img,x,y) 
        // { 
        //     R.push_back( (img(x,y,0) + img(x,y,1) +  img(x,y,2))/3);
        // }
        // return R;
    }

};

#endif