#include "selectcomponents.h"

class SelectComponents SelectComponents;
Mat Components[255];
string ComponentNames[255];
string componentID;
string XML_Path;
int componentNumber = 0;

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
    //cout << "right button " << endl;
    return;
  }
//Mouse Left button down to set origin coordinates
  if (event == EVENT_LBUTTONDOWN) {
    SelectedRoi.initX = x;
    SelectedRoi.initY = y;
    SelectedRoi.init = 1;
    //cout << "left button DOWN" << endl;
    return;
  }
//Mouse Left button up to set final coordinates
  if (event == EVENT_LBUTTONUP) {
    SelectedRoi.actualX = x;
    SelectedRoi.actualX = y;
    //When left mouse released set to the state to name a component
    SelectedRoi.init = 2;
    //cout << "left button UP" << endl;
    return;
  }
//Mouse move coordinates update
  if (event == EVENT_MOUSEMOVE) {

     //cout << "event mouse move"<< endl;
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


    Mat DrawReference = imread("C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/Reference.jpg");
    namedWindow("ImageDrawing");
    // mouse call back function, where CallBackF is function
    // with parameters event type, x y coorfinates
    setMouseCallback("ImageDrawing", CallBackF, 0);

    //
    while(1){
    //Copy the array to display the rectangles
    Mat DrawReference2;
    DrawReference.copyTo(DrawReference2);

    //init 0 haven't started, init 1 drawing, init 2 label, init 3 write to file

    /*
     *
     *  Draw rectangle when left mouse click
     *
     */

    if (SelectedRoi.init == 1) {
        // draw the rectangle updated by mouse move
        rectangle(DrawReference2, Rect(SelectedRoi.initX, SelectedRoi.initY, SelectedRoi.actualX- SelectedRoi.initX, SelectedRoi.actualY- SelectedRoi.initY), Scalar(255, 255, 255), 1, 8, 0);
        //Store rectangle in an array
        Components[componentNumber] = Mat(DrawReference2 ,Rect(SelectedRoi.initX, SelectedRoi.initY, SelectedRoi.actualX- SelectedRoi.initX, SelectedRoi.actualY- SelectedRoi.initY));
    }

    /*
     *
     *  Label component selected
     *
     */

    if(SelectedRoi.init == 2){
        //Ask user for component name
        cout << "Enter component name:\n\r";
        //Input component name
        cin >> componentID;
        //Store component ID (name) with relation to the number of the component
        ComponentNames[componentNumber] = componentID;
        //Clear ID after storage to prevent data corruption
        componentID.clear();
        //Incriment the component number
        componentNumber++;
        SelectedRoi.init = 0;
    }

    /*
     *
     *  Write to file
     *
     */
    if(SelectedRoi.init == 3){
        //Set pFile as a file type
        FILE * pFile;
        //Attempt to open pFile as a read to detect if there is any issue in opening
        pFile = fopen(XML_Path.c_str(), "r");
        //If not able to open the file give error
        if(!pFile){
            perror("File opening failed, creating new file");
            //If file does not exist then make file
            pFile = fopen(XML_Path.c_str(), "w");
        }
        //If the file is openable then open it as a write
        pFile = fopen(XML_Path.c_str(), "w");
        //Store each component name and coordinate in the xml file
        for(int i = 0; i >= 255; i++){
        fprintf(pFile, ComponentNames[i].c_str());

        }
    }

      imshow("ImageDrawing", DrawReference2);
      int key2 = waitKey(27);

      //Grab rectangle store into an array COMPLETED

      //Change draw function to draw all stored rectangles
      //Once selected region prompt user to type into control pannel, use name for rectangle is a string COMPLETED
      //Save into xml, look up how to save variable types to xml files in opencv, save as rect, save under string name

      //Call each rectangle something generic, rectangle 0 rect, and rectangle name, could save structure region of interest including a rectangle and a string

      //QT widgets,



    }
      return 0;
}

int Image_number = 6;
double SelectComponents::DrawComponent(int Image_number){
string File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
    //Switch the file path to the correct image
    switch(Image_number){
        case 1:
            //Select image file 1
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/01/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\01\\Coordinate locations\\ComponentCoordinates.xml";
        break;
        case 2:
            //Select image file 2
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/02/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\02\\Coordinate locations\\ComponentCoordinates.xml";
        break;
        case 3:
            //Select image file 3
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/03/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\03\\Coordinate locations\\ComponentCoordinates.xml";
        break;
        case 4:
            //Select image file 4
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/04/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\04\\Coordinate locations\\ComponentCoordinates.xml";
        break;
        case 5:
            //Select image file 5
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/05/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\05\\Coordinate locations\\ComponentCoordinates.xml";
        break;
        case 6:
            //Select image file 6
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\06\\Coordinate locations\\ComponentCoordinates.xml";
        break;
        default:
            //Select image file 6
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\06\\Coordinate locations\\ComponentCoordinates.xml";
        break;
    }
    int pathlength = XML_Path.length();
    char PathArray[pathlength + 1];
    strcpy(PathArray, XML_Path.c_str());
    //Run the draw components function
    DrawBoxes(File_Path);
    //Store the component coordinates into a notepad with a label

    //Return 0
    return 0;
}
