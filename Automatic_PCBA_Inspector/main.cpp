
/*
Phil Culverhouse Oct 2016 (c) Plymouth University
James Rogers Jan 2020     (c) Plymouth University

This demo code will move eye and neck servos with kepresses.
When 'c' is pressed, one eye will track the target currently within the target window.

Use this code as a base for your assignment.

*/


/*
This is a proof of concept software to demonstrate the use of machine vision for automated circuit inspection

*/
#include "shared_include.h"
#include "check_equal.h"
#include "realign.h"
#include "detectdifference.h"
using namespace std;
using namespace cv;
//Global definitions for image paths
static string referenceimg(test_img_path + "Reference01.jpg");
static string productimg(test_img_path + "Different01.jpg");
static string fixedimg(output_img_path + "aligned_image.jpg");

int main()
{
    cv::setBreakOnError(true);

    //Read the images stored in the directory and define them as img0 and img1
    Mat Reference = imread(referenceimg);
    Mat Input = imread(productimg);
    //Create two windows for reference image and for the product image
    namedWindow("Reference", WINDOW_NORMAL);
    namedWindow("Product", WINDOW_NORMAL);

    //Rescale the windows
    resizeWindow("Reference", 600, 800);				//Size set to be 3/4 ratio window size may need adjustment
    resizeWindow("Input", 600, 800);

    //Display the images for product and reference
    imshow("Reference", Reference);
    imshow("Product", Input);
    //Failure condition test mode to check if no image is available
    if (Reference.empty())
    {
        //Print reference image is missing
        printf("Error: reference image is missing");
        //Wait for any key press to exit
        cin.get();
        return -1;
    }
    else if (Input.empty())
    {
        //Print input image is missing
        printf("Error: product image is missing");
        //Wait for any key press to exit
        cin.get();
        return -1;
    }
    //If both images are available then run comparision algorithms
    else
    {
        Realign.image_realignment(Reference, Input);
        Mat Aligned = imread(fixedimg);
        DetectDifference.DetectError(Reference, Aligned);
    }
    //Wait until 0 is pressed to exit
    waitKey(0);
    return 0;
}
