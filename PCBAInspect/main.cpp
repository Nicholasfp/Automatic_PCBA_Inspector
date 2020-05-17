
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
#include "realign.h"
#include "detectdifference.h"
#include "imagecapture.h"
#include "selectcomponents.h"
using namespace std;
using namespace cv;
//Global definitions for image paths
static string referenceimg(test_img_path + "Reference.jpg");
static string productimg(test_img_path + "Different02.jpg");
static string fixedimg(output_img_path + "aligned_image.jpg");


int main()
{
    cv::setBreakOnError(true);
    imread("C:/Users/User/Documents/QTProjects/PCBAI/Samples/Test_image_02.jpg");

    printf("Test\r\n");

    //Read the images stored in the directory and define them as img0 and img1
    Mat Reference = imread(referenceimg);
    Mat Input = imread(productimg);

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

        //Compute image realignment to remove rotations or scaling issues between reference and input
        Realign.image_realignment(Reference, Input);
        //Load the aligned image
        Mat Aligned = imread(fixedimg);
        //Detect the differences between the reference and the realigned image
        DetectDifference.DetectError(Reference, Aligned);
        //Take a capture on a camera, this is for proof of concept and can be implemented when boards are aquired
        imagecapture.captureimg();
        //Test draw function
        SelectComponents.DrawComponent(6);
    }
    //Wait until 0 is pressed to exit
    waitKey(0);
    return 0;

}
