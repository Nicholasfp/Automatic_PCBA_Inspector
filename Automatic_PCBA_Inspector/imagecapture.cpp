#include "imagecapture.h"

class imagecapture imagecapture;

double imagecapture::captureimg()
{
    //Take a capture from the camera
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);

    //If the image is not captured print that the image is not captured
    if (!capture){
        printf("Image not captured\n\r");
        cin.get();
        return 0;
    }

    //Display captured image
    //cv::imwrite(capture_img_path + "Capture.jpg", capture);
    //imwrite(calculation_img_path)
    //imwrite(calculation_img_path + "Error.jpg", capture);
    imshow("result", capture);

    return 0;
}
