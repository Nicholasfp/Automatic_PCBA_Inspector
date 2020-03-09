#pragma once
#ifndef SHARED_INCLUDE_H_
#define SHARED_INCLUDE_H_


#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>		//Search for and include openCV header
#include <opencv2/features2d.hpp>	//Search for and include openCV features header
//#include <opencv2/tracking.hpp>		//include tracking library for use in selecting ROI
//#include <opencv2/xfeatures2d.hpp> //isolated as not found
using namespace std;
using namespace cv;
//Global constant for test and reference images file path
const string test_img_path = "C:/Samples/Reference images/01/";
//Global constant for calculation images file path
const string calculation_img_path = "C:/Samples/Calculation images/";
//Global constant for output images file path
const string output_img_path = "C:/Samples/Output images/";
//Global constant for captured images
const string capture_img_path = "C:/Samples/capture";
#endif
