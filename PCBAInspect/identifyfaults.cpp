#include "identifyfaults.h"

class IdentifyFaultyComponents FindFaults;

// global structure to remember some states changed
// by mouse action and move
struct Selection {

  //Initial coordinates
  int initX;
  int initY;

  //Final coordinates
  int FinalX;
  int FinalY;

  //Component name
  string Name;
}
Component;

struct ErrorPoints {

    //Coordinates to save x and y from errors
    int Errorx;
    int Errory;

};


//Create a boolean to detect if point is within a rect
bool FindPoint(int x1, int y1, int x2, int y2, int x, int y) {
    if (x > x1 and x < x2 and y > y1 and y < y2){
        return true;
    }
    else {
        return false;
    }
}

int IdentifyFaultyComponents::SearchError(string CoordinatesFile){
    //Use fscanf and set a structure, string, int, int, int, int
    //mask error with areas of interest
    //If part of mask and error, draw an error
    //copy to and draw a mask


    ifstream file(CoordinatesFile);
    string str;

    //Vector for holding component id and
    vector <Selection> SelectionList;

    //Create a new
    Selection NewSelection;

   /*
    *
    *  Store coordinate files locally in a vector
    *
    */
    while (getline(file, str, ',')) {
      NewSelection.Name = str;
      getline(file, str, ',');
      NewSelection.initX = stoi(str);
      getline(file, str, ',');
      NewSelection.initY = stoi(str);
      getline(file, str, ',');
      NewSelection.FinalX = stoi(str);
      getline(file, str, '\n');
      NewSelection.FinalY = stoi(str);
      SelectionList.push_back(NewSelection);
    }

    //Load error from calculation path
    Errors = imread(calculation_img_path + "Error.jpg");

    //Create vector to store error coordinates
    vector <ErrorPoints> ErrorList;
    //Loop through all pixels in the image
//    for(int x = 0; x < Errors.rows; x++){
//        for(int y = 0; y < Errors.cols; y++){
//            //Read pixel values
//            Vec3b colourVals = Errors.at<Vec3b>(y,x);
//            //Check red value
//            uchar red = colourVals.val[2];
//            //if red value is equal to or greater than 10 store coordinates
//            if (red >= 10){
//                //Store coordinates
//                ErrorList[RedPixNum].Errorx = x;
//                ErrorList[RedPixNum].Errory = y;
//                //Incriment error number
//                RedPixNum++;
//            }
//        }
//    }

    //Make subimage that makes a selection, loop through all items in the selection list


    /*
     *
     * Iterate through each rectangle and check if error lays within the rectangle
     *
     */
    cout << "Looking for errors" << endl;
    Mat ErrorCopy;
    Errors.copyTo(ErrorCopy);
    cout << SelectionList.size() << endl;
    for(int i = 0; i < SelectionList.size(); i++){

        Mat SelectionImg;
        Rect ComponentRect(Point(SelectionList[i].initX, SelectionList[i].initY), Point(SelectionList[i].FinalX, SelectionList[i].FinalY));
        rectangle(ErrorCopy, ComponentRect, Scalar(255, 0, 0), 2);
        //Access specific region
        Errors(ComponentRect).copyTo(SelectionImg);
        cout << SelectionImg.size() << endl;
        for(int y = 0; y < SelectionImg.size().height; y++){
            for(int x = 0; x < SelectionImg.size().width; x++){
                if (SelectionImg.at<Vec3b>(y,x) != Vec3b(0, 0, 0)){
                    goto endloop;
                }
            }
        }
        continue;
        endloop: cout << SelectionList[i].Name << endl;
//      for(int j = 0; j < RedPixNum; j++){
//        //Check if point lays within rectangle
//        if (FindPoint(SelectionList[i].initX, SelectionList[i].initY, SelectionList[i].FinalX, SelectionList[i].FinalY, ErrorList[j].Errorx, ErrorList[j].Errory)){
//            //If point lays within component then output error and component name
//            cout << "Fault detected with component: " << SelectionList[i].Name << endl;
//        }

      //}
    }
    imshow("Show me rectangles",ErrorCopy);
    //Mat1(Rect).copyto(Mat2)
    //Grab results image (ROI) copy to its own image if any red in this image then component has an error
    //Have a loop which goes through every roi in list and makes a small image which represents error for each component
    //Make a rect based on 4 numbers and make a subimage of result
    //check pixel by pixel for red
    return 0;
}
