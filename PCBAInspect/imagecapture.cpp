#include "imagecapture.h"

class imagecapture imagecapture;

double imagecapture::captureimg()
{
    //Setup cap as a video capture
    VideoCapture cap;
    //If capture not opened output that camera is not connected
    if(!cap.open(0)){
        printf("Error no camera connected\n\r");
    }

    //Create a matrix for storing the capture
    Mat capture;
    //Store capture
    cap.read(capture);
    //Save capture into
    imwrite(capture_img_path + "capture.jpg", capture);
    return 0;
}
