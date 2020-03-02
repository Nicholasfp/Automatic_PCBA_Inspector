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
    //Create a array for the result matrix to be split into blue, green and red
    Mat bgr[3];
    //Create comparing integers for channels, collumns and rows. Which represent the number of colour channels of each image and the size in collumns and rows of each image
    int A_chan = A.channels();
    int B_chan = A.channels();
    int A_cols = A.cols;
    int B_cols = A.cols;
    int A_rows = A.rows;
    int B_rows = B.rows;
    printf("The number of channels in the reference image is %i and the number of channels in the product image is %i\n", A_chan, B_chan);
    printf("The number of columns in the reference image is %i and the number of columns in the product image is %i\n", A_cols, B_cols);
    printf("The number of rows in the reference image is %i and the number of columns in the product image is %i\n", A_rows, B_rows);
    //Check that A is the same size matrice as B and has the same number of channels
    if ((A_chan > 0 && A_chan == B_chan) && (A_cols > 0 && A_cols == B_cols) && (A_rows > 0 && A_rows == B_rows))
    {
        //Display that the images have the same size and channels
        printf("The images have the same size and channels\n");
        //Work out the difference between A and B and output the difference as result
        subtract(A, B, result);
        //Split result matrix into blue green and red values
        split(result, bgr);
        //Save each colour channel as an image in calculation images
        imwrite(calculation_img_path + "blue.png", bgr[0]);
        imwrite(calculation_img_path + "green.png", bgr[1]);
        imwrite(calculation_img_path + "red.png", bgr[2]);
        //Count non black pixels in the image and set bgr compare values as new integers
        int blue_compare = countNonZero(bgr[0]);
        int green_compare = countNonZero(bgr[1]);
        int red_compare = countNonZero(bgr[2]);
        //check the difference between each channel by checking if the difference is equal to zero
        if ((0 == blue_compare) && (0 == green_compare) && (0 == red_compare))
        {
            //If there is no difference when subtracting image A and image B then print that the images are completely equal
            printf("The images are completely equal\n");
        }
        else
        {
            //If there is a difference when subtracting image A and image B then print that the images are not equal
            printf("The images are not equal\n Blue %i\n Red %i\n Green %i\n", blue_compare, red_compare, green_compare);
        }
    }
    return 0;
}

#endif
