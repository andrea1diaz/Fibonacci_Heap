#ifndef Lector_H
#define Lector_H

#define cimg_use_jpeg 1
#include "CImg.h"
#include <iostream>
#include <utility>
#include <fstream>
#include <vector>

using namespace cimg_library;
using namespace std;

struct Lector {

    vector< pair<vector<float>, CImg<float>> > Vectorizar() {
        ifstream input ("list100.txt");
        vector< pair<vector<float>, CImg<float>> > Rs;
        string file;
        
        while(getline(input, file)) {
            CImg<float> A(file.c_str());
            A.haar(false, 1);
            A.crop(0,0,89,99);
            // CImg<float> B = A.haar(false,1);
            // CImg<float> C = B.crop(0,0,89,99);
            vector<float> R;
            cimg_forXY(A,x,y) { 
                R.push_back( (A(x,y,0) + A(x,y,1) +  A(x,y,2))/3);
            }
            Rs.push_back( {R, A} );
        }

        return Rs;
    }

} lector;

#endif
