/*
This function checks that two image matrices have the same size and number of channels and then checks if they are identical
*/
//Define header name and include and use relevant libraries
#ifndef CHECK_EQUAL_H_
#define CHECK_EQUAL_H_
#include "shared_include.h"
#pragma once
using namespace std;
using namespace cv;

//Comparision function between two images represented as matrices, this function checks if the two images are identical or different
double check_equal(const Mat A, const Mat B)
{
    //An empty matrix for later calculations
    Mat result;
    Mat Mask;
    printf("Entered check equal\r\n");
    //Used for checking that images are roughly the same

    //Create comparing integers for channels, collumns and rows. Which represent the number of colour channels of each image and the size in collumns and rows of each image
    //int A_chan = A.channels();
    //int B_chan = A.channels();
    //int A_cols = A.cols;
    //int B_cols = A.cols;
    //int A_rows = A.rows;
    //int B_rows = B.rows;
    //printf("The number of channels in the reference image is %i and the number of channels in the product image is %i\n", A_chan, B_chan);
    //printf("The number of columns in the reference image is %i and the number of columns in the product image is %i\n", A_cols, B_cols);
    //printf("The number of rows in the reference image is %i and the number of columns in the product image is %i\n", A_rows, B_rows);

    //Work out the difference between A and B and output the difference as result
    absdiff(A, B, result);

    /*
     *  Noise reduction mask
     *
     */

    printf("Entered mask");
    //Set the dilation brush size
    int dilation_size=1;
    //Define the brush type for dilation and erosion
    Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*dilation_size + 1, 2*dilation_size+1 ), Point( dilation_size, dilation_size ) );
    //Convert color space to gray to remove all colour
    cvtColor(result,result,CV_BGR2GRAY);
    printf("Convert to color\r\n");
    //Define the range of colour values to modify
    inRange(result, 35, 255, Mask);
    //Erode then dilate to remove noise
    erode(Mask, Mask, element);
    dilate(Mask, Mask, element);

    printf("Eroded and dilated\r\n");

    //Overlay the mask with a red mask to identify the error between the two images
    Mat Diff(Mask.size(),CV_8UC3,Scalar(0,0,0));
    Diff.setTo(Scalar(255, 255, 0), Mask);
    imshow("result", Diff);

    /*
     *  End mask
     *
     */

    printf("Exited mask\n\r");
    return 0;
}

#endif
