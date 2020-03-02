#ifndef REALIGN_H
#define REALIGN_H
#include "shared_include.h"
#pragma once

using namespace std;
using namespace cv;

//Global constant for the maximum number of features to search for
const int max_features = 500;
//Global constant for the percentage match requirement for each feature
const float good_match_percent = 0.15f;

class Realign
{
    //Define the public variables and functions
    public:
        double image_realignment(Mat reference, Mat input);   //A function that uses ORB feature detection to realign images using homography
    //Define private variables and functions
    private:
        Mat homography_matrix;
        Mat output;
        Mat reference_gray;
        Mat input_grey;
};

extern Realign Realign;
#endif // REALIGN_H
