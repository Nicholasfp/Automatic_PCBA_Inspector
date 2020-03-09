#include "detectdifference.h"

class DetectDifference DetectDifference;

//Comparision function between two images represented as matrices, this function checks if the two images are identical or different
double DetectDifference::DetectError(const Mat Reference, const Mat Input)
{
    printf("Enter function\n\r");
    //An empty matrix for later calculations
    Mat result;
    Mat Mask;
    if(Reference.empty() || Input.empty()){
        printf("matrix is empty\n\r");
    }


    //Work out the error between the reference and the input and output the difference as result
    cout<<"test"<<endl;
    cout<<Reference.size()<<endl;
    cout<<Input.size()<<endl;
    absdiff(Reference, Input, result);
    printf("Calculate absolute difference\n\r");

    /*
     *  Noise reduction mask
     *
     */

    //Set the dilation brush size
    int dilation_size=1;
    //Define the brush type for dilation and erosion
    Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*dilation_size + 1, 2*dilation_size+1 ), Point( dilation_size, dilation_size ) );
    //Convert color space to gray to remove all colour
    cvtColor(result,result,CV_BGR2GRAY);
    //Define the range of colour values to modify
    inRange(result, 35, 255, Mask);
    //Erode then dilate to remove noise
    erode(Mask, Mask, element);
    dilate(Mask, Mask, element);

    //Overlay the mask with a red mask to identify the error between the two images
    Mat Diff(Mask.size(),CV_8UC3,Scalar(0,0,0));
    Diff.setTo(Scalar(0, 0, 255), Mask);
    imwrite(calculation_img_path + "Error.jpg", Diff);
    imshow("result", Diff);

    /*
     *  End mask
     *
     */


    return 0;
}

