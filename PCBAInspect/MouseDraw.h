#ifndef MOUSEDRAW_H
#define MOUSEDRAW_H

#include "shared_include.h"

using namespace cv;
using namespace std;

// global structure to remember some states changed
// by mouse action and move
struct initRoi {
  // on off
  int init = 0;

  //initial coordination origin based on EVENT_LBUTTONDOWN
  int initX;
  int initY;

  // actual coordination based on current mouse position
  int actualX;
  int actualY;

  //Selected Rect
  Rect roiRectangle;

  //Selected Mat roi
  Mat takenRoi;
}
SelectedRoi;


//event int is compared to determine action of the mouse EVENT_RBUTTONDOWN
// EVENT_LBUTTONDOWN, EVENT_LBUTTONUP, EVENT_MOUSEMOVE.
// If the event is evauated as happened the global structure SelectedRoi
// is updated.
static void CallBackF(int event, int x, int y, int flags, void* img) {
//Mouse Right button down
  if (event == EVENT_RBUTTONDOWN) {
    cout << "right button " << endl;
    return;
  }
//Mouse Left button down to set origin coordinates
  if (event == EVENT_LBUTTONDOWN) {
    SelectedRoi.initX = x;
    SelectedRoi.initY = y;
    SelectedRoi.init = 1;
    cout << "left button DOWN" << endl;
    return;
  }
//Mouse Left button up to set final coordinates
  if (event == EVENT_LBUTTONUP) {
    SelectedRoi.actualX = x;
    SelectedRoi.actualX = y;
    SelectedRoi.init = 0;
    cout << "left button UP" << endl;
    return;
  }
//Mouse move coordinates update
  if (event == EVENT_MOUSEMOVE) {

     cout << "event mouse move"<< endl;
      SelectedRoi.actualX = x;
      SelectedRoi.actualY = y;
      SelectedRoi.roiRectangle = Rect(SelectedRoi.initX, SelectedRoi.initY,
      SelectedRoi.actualX,  SelectedRoi.actualY);
    return;
  }
}

//Function for drawing on top of an image, input image or open
int DrawBoxes(string File_Path)
{
    // Set initial state for the SelectedRoi structure
    //- The init is set = 1 by left button down action
    //- This start to display image if (SelectedRoi.init != 0) in main for loop


    Mat DrawReference = imread(File_Path + "Reference.jpg");

    //Show image
    imshow("ImageDrawing",DrawReference);
    // mouse call back function, where CallBackF is function
    // with parameters event type, x y coorfinates
    setMouseCallback("Video", CallBackF, 0);
    //Draw rectangle if selection made (Left mouse click)
    if (SelectedRoi.init != 0) {
        // draw the rectangle updated by mouse move
        rectangle(DrawReference, Rect(SelectedRoi.initX, SelectedRoi.initY, SelectedRoi.actualX- SelectedRoi.initX, SelectedRoi.actualY- SelectedRoi.initY), Scalar(255, 255, 255), 1, 8, 0);
      }
    //Calculate all coordinates between init y and y
//    for(int i = SelectedRoi.initY; i >= SelectedRoi.actualY; i++){

//    }
    //Calculate all coordinates between init x and x
      //Display image
      string Teststring = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/Reference.jpg";
      imshow("DrawReference", DrawReference);
      int key2 = waitKey(20);
      return 0;

}

#endif // MOUSEDRAW_H
