#include "detectdifference.h"

class DetectDifference DetectDifference;

//Comparision function between two images represented as matrices, this function checks if the two images are identical or different
double DetectDifference::DetectError(const Mat Reference, const Mat Input)
{
    if(Reference.empty() || Input.empty()){
        printf("matrix is empty\n\r");
    }

    //Output sizes of each image
    cout<<Reference.size()<<endl;
    cout<<Input.size()<<endl;
    //Work out the error between the reference and the input and output the difference as result
    absdiff(Reference, Input, result);

    /*
     *
     *  Colour thresholding
     *
     */



    //If unable to open input or reference output an error
    if(Input.empty()){
        cout << "Input image not available\n\r";
    }
    else if(Reference.empty()){
        cout << "Reference image not availble\n\r";
    }
    else {
        //If images exist then run colour filter to set the range of brightness acceptable for the PCB
        inRange(Input, Scalar(4, 36, 2), Scalar(146, 255, 140), colInput);
        //show the filtered input
        imshow("Colour filter input", colInput);
        //
        inRange(Reference, Scalar(4, 36, 2), Scalar(146, 255, 140), colReference);
        imshow("Colour filter reference", colReference);
        absdiff(colReference, colInput, colDiff);
        imshow("Color filter difference", colDiff);
    }

    /*
     *  Noise reduction mask
     *
     */

    //Set the dilation brush size
    int dilation_size=2;
    //Define the brush type for dilation and erosion
    Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*dilation_size + 1, 2*dilation_size+1 ), Point( dilation_size, dilation_size ) );
    //Convert color space to gray to remove all colour
    cvtColor(result,result,CV_BGR2GRAY);
    //Define the range of colour values to modify
    //inRange(result, 25, 255, Mask);
    inRange(colDiff, 25, 255, Mask);

    //Erode then dilate to remove noise
    erode(Mask, Mask, element);
    dilate(Mask, Mask, element);
    erode(Mask, Mask, element);
    dilate(Mask, Mask, element);
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

