#include "identifyfaults.h"

class IdentifyFaultyComponents FindFaults;

//Structure for converting file component to local variables
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

//Structure for storing coordinates read from the error image
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

    /*
     *
     * Iterate through each rectangle and check if error lays within the rectangle
     *
     */
    cout << "Looking for errors" << endl;
    //Copy error to display rectangles over
    Mat ErrorCopy;
    Errors.copyTo(ErrorCopy);
    //Boolean for outputting if no error detected
    bool NoError = true;
    for(int i = 0; i < SelectionList.size(); i++){
        Mat SelectionImg;
        Rect ComponentRect(Point(SelectionList[i].initX, SelectionList[i].initY), Point(SelectionList[i].FinalX, SelectionList[i].FinalY));
        //Access specific region
        Errors(ComponentRect).copyTo(SelectionImg);
        //Loop through all coordinates in the image
        for(int y = 0; y < SelectionImg.size().height; y++){
            for(int x = 0; x < SelectionImg.size().width; x++){
                //Check that points are not black
                if (SelectionImg.at<Vec3b>(y,x) != Vec3b(0, 0, 0)){
                    rectangle(ErrorCopy, ComponentRect, Scalar(0, 255, 0), 2);
                    NoError = false;
                    //If error detected break loop for this component and output component name as error
                    goto endloop;
                }
            }
        }
        continue;
        endloop: cout << "Fault detected with component: " << SelectionList[i].Name << endl;

    }
    imshow("Overlay rectangles",ErrorCopy);
    //If no errors detected then say no errors detected
    if(NoError == true){
        cout << "No errors detected" << endl;
    }

    return 0;
}
