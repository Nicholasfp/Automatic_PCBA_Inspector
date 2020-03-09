#ifndef DETECTDIFFERENCE_H
#define DETECTDIFFERENCE_H
#include "shared_include.h"
#pragma once

using namespace std;
using namespace cv;

class DetectDifference
{
    public:
        //Define the detect error function
        double DetectError(const Mat Reference, const Mat Input);
        //Define the simple blob detection function

    private:
        //Define private variables
        Mat result;
        Mat Mask;
        Mat Brush;
};


extern DetectDifference DetectDifference;
#endif // DETECTDIFFERENCE_H
