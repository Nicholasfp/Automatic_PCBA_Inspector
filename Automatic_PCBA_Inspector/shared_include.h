#pragma once
#ifndef SHARED_INCLUDE_H_
#define SHARED_INCLUDE_H_


#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>		//Search for and include openCV header
#include <opencv2/features2d.hpp>	//Search for and include openCV features header
//#include <opencv2/tracking.hpp>		//include tracking library for use in selecting ROI
//#include <opencv2/xfeatures2d.hpp> //isolated as not found
using namespace std;
using namespace cv;
#include <string>					//Search for and include the input output header
#include <iostream>					//Search for and include iostream
//Global constant for test and reference images file path
const string test_img_path = "C:/Samples/";
//Global constant for calculation images file path
const string calculation_img_path = "C:/Samples/Calculation images/";
//Global constant for output images file path
const string output_img_path = "C:/Samples/Output images/";
//Global constant for the maximum number of features to search for
const int max_features = 500;
//Global constant for the percentage match requirement
const float good_match_percent = 0.15f;

#endif
