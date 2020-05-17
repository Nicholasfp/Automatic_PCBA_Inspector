#ifndef IMAGECAPTURE_H
#define IMAGECAPTURE_H
#include "shared_include.h"
#pragma once

using namespace std;
using namespace cv;

class imagecapture
{
    public:
        //Define the function for capturing an image from the camera
        double captureimg ();
    private:
        //Define the local variables
        Mat capture;
};

extern imagecapture imagecapture;
#endif // IMAGECAPTURE_H
