#include "detectdifference.h"

class DetectDifference DetectDifference;

//Comparision function between two images represented as matrices, this function checks if the two images are identical or different
double DetectDifference::DetectError(const Mat Reference, const Mat Input)
{
    /*
     *
     *  Colour thresholding
     *
     */
    //If unable to open input or reference output an error
    if(Input.empty()){
        cout << "Input image not available" << endl;
    }
    else if(Reference.empty()){
        cout << "Reference image not availble" << endl;
    }
    else {
        //If images exist then run colour filter to set the range of brightness acceptable for the PCB, set these to the range of colours used by the PCB board
        inRange(Input, Scalar(4, 36, 2), Scalar(146, 255, 140), colInput);
        //show the filtered input
        imshow("Colour filter input", colInput);
        //If images exist then run colour filter to set the range of brightness acceptable for the PCB, set these to the range of colours used by the PCB board
        inRange(Reference, Scalar(4, 36, 2), Scalar(146, 255, 140), colReference);
        //show the filtered reference
        imshow("Colour filter reference", colReference);
        absdiff(colReference, colInput, colDiff);
        //show the difference
        imshow("Color filter difference", colDiff);
    }
    /*
     *
     *  Noise reduction mask
     *
     */
    //Set the dilation brush size
    int dilation_size=2;
    //Define the brush type for dilation and erosion
    Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*dilation_size + 1, 2*dilation_size+1 ), Point( dilation_size, dilation_size ) );
    //Define the range of colour values to modify
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
    //colour the errors red
    Diff.setTo(Scalar(0, 0, 255), Mask);
    //Save the image
    imwrite(calculation_img_path + "Error.png", Diff);
    //Show the result
    imshow("result", Diff);
    /*
     *  End mask
     *
     */
    return 0;
}

