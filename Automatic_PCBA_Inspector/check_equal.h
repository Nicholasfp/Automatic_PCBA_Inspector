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
        absdiff(A, B, result);
        //Split result matrix into blue green and red values
        split(result, bgr);
        /*
         *  Colouring mask
         *
         */
        //Mat Temp;
        //Convert from grey to BGR and save in Mask
        cvtColor(bgr[1], Mask, COLOR_GRAY2BGR);
        //cvtColor(bgr[1], Mask, COLOR_BGR2HSV_FULL);
        //Search for non black values (difference) between the threshold and save difference in Mask
        inRange(bgr[1], Scalar(265, 0, 100), Scalar(265, 5, 63), Mask);
        //Convert threshold values to green and save as mask
        Mask.setTo(Scalar(82, 87, 100), bgr[1]);
        imwrite(calculation_img_path + "Mask.png", Mask);
        namedWindow("Mask", WINDOW_NORMAL);
        imshow("Mask", Mask);
        namedWindow("Green", WINDOW_NORMAL);
        imshow("Green", bgr[1]);


        int dilation_size=1;
        Mat element = getStructuringElement( MORPH_ELLIPSE,
                                             Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                             Point( dilation_size, dilation_size ) );



        cvtColor(result,result,CV_BGR2GRAY);

        inRange(result, 30, 255, Mask);
        erode(Mask, Mask, element);
        dilate(Mask, Mask, element);







        Mat Diff(Mask.size(),CV_8UC3,Scalar(0,0,0));
        Diff.setTo(Scalar(0, 0, 255), Mask);
        imshow("result", Diff);



        /*
         *  End colouring
         *
         */

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
