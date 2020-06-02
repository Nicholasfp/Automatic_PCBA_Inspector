#include "selectcomponents.h"

class SelectComponents SelectComponents;
int InitialX[255];
int InitialY[255];
int FinalX[255];
int FinalY[255];
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
string DrawBoxes(string File_Path)
{
    //Set a matrix for the reference
    Mat DrawReference = imread(File_Path + "Reference.jpg");
    namedWindow("ImageDrawing");
    //Set up mouse callback function
    setMouseCallback("ImageDrawing", CallBackF, 0);


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
        //Store coordinates in arrays
        InitialX[componentNumber] = SelectedRoi.initX;
        InitialY[componentNumber] = SelectedRoi.initY;
        FinalX[componentNumber] = SelectedRoi.actualX;
        FinalY[componentNumber] = SelectedRoi.actualY;
    }

    /*
     *
     *  Label component selected
     *
     */

    if(SelectedRoi.init == 2){
        //Ask user for component name
        cout << "Enter component name: " << endl;
        //Input component name
        cin.get();
        getline(cin, componentID);
        cout << endl;
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
     *  Write to file and stop drawing
     *
     */
    if(SelectedRoi.init == 3){
        cout << "Please enter the file name\n\r";
        string UserInputName;
        getline(cin, UserInputName);
        string FileName = XML_Path + UserInputName + ".xml";
        //Set pFile as a file type
        FILE * pFile;
        //Attempt to open pFile as a read to detect if there is any issue in opening
        pFile = fopen(FileName.c_str(), "r");
        //If not able to open the file give error
        if(!pFile){
            perror("File opening failed, creating new file");
        }
        fclose(pFile);
        //If the file is openable then open it as a write
        pFile = fopen(FileName.c_str(), "w");
        //Store each component name and coordinate in the xml file
        for(int i = 0; i < componentNumber; i++){
        fprintf(pFile, ComponentNames[i].c_str());
        fprintf(pFile, ", %d", InitialX[i]);
        fprintf(pFile, ", %d", InitialY[i]);
        fprintf(pFile, ", %d", FinalX[i]);
        fprintf(pFile, ", %d", FinalY[i]);
        fprintf(pFile, "\n");
        }
        fclose(pFile);
        cout << "File saved\n\r";
        cvDestroyWindow("ImageDrawing");
        return FileName;
        break;
      }

      imshow("ImageDrawing", DrawReference2);
      //Display all previous rectangles
      for(int j = 0; j < componentNumber; j++){
          rectangle(DrawReference2, Point(InitialX[j], InitialY[j]), Point(FinalX[j], FinalY[j]), Scalar(0, 0, 255), 2);
      }
      imshow("ImageDrawing", DrawReference2);
      int key2 = waitKey(10);
      if (key2 == 27){
            SelectedRoi.init = 3;
      }
    }

}
string SelectComponents::DrawComponent(int Image_number){
string File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
    //Switch the file path to the correct image
    switch(Image_number){
        case 1:
            //Select image file 1
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/01/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\01\\Coordinate locations\\";
        break;
        case 2:
            //Select image file 2
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/02/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\02\\Coordinate locations\\";
        break;
        case 3:
            //Select image file 3
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/03/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\03\\Coordinate locations\\";
        break;
        case 4:
            //Select image file 4
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/04/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\04\\Coordinate locations\\";
        break;
        case 5:
            //Select image file 5
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/05/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\05\\Coordinate locations\\";
        break;
        case 6:
            //Select image file 6
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\06\\Coordinate locations\\";
        break;
        default:
            //Select image file 6
            File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
            XML_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\06\\Coordinate locations\\";
        break;
    }

    //Run the draw components function
    string OutputFile = DrawBoxes(File_Path);
    return OutputFile;
}
