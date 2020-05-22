#include "shared_include.h"
#include "realign.h"
#include "detectdifference.h"
#include "imagecapture.h"
#include "selectcomponents.h"
#include "identifyfaults.h"
using namespace std;
using namespace cv;
//Global definitions for image paths
static string fixedimg(output_img_path + "aligned_image.jpg");

//Used for selecting image to use
int Image_number = 6;
//Change this to use the camera
int UseCam = 0;
//Used for image setup
Mat Input;
Mat Reference;
Mat Aligned;
//Used for path names
string File_Path;
string Coord_Path;
string DefaultCoordName = "Test.xml";


int main()
{
    cv::setBreakOnError(true);

       /*
        *
        *  User interface
        *
        */

        //Option selection
        string Option;
        string ProductNum;
        string CoordinatesFile;
        int User_Selection;

        //Project title
        cout << "Student 10554824 PROJ324 final year project: Automatic Printed Circuit Board (PCB) Inspector" << endl;

        //Mode selector
        cout << "Please select one of the following options" << endl;

        //Option 1 setup a new product
        cout << "1) Setup a new coordinates file" << endl;

        //Option 2 select a product
        cout << "2) Select an existing program to run" << endl;

        //Option 3 continue with current project;
        cout << "3) Run with default program" << endl;

        getline(cin, Option);

        if(Option != "1" && Option != "2" && Option != "3"){
            cout << "Please enter a valid option" << endl;
        }

        else if(Option == "1"){
            User_Selection = 1;
        }
        else if(Option == "2"){
            User_Selection = 2;

            switch(Image_number){
                case 1:
                    //Select image file 1
                    File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/01/";
                break;
                case 2:
                    //Select image file 2
                    File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/02/";
                break;
                case 3:
                    //Select image file 3
                    File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/03/";
                break;
                case 4:
                    //Select image file 4
                    File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/04/";
                break;
                case 5:
                    //Select image file 5
                    File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/05/";
                break;
                case 6:
                    //Select image file 6
                    File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
                break;
                default:
                    //Select image file 6
                    File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
                break;
            }
            //Write the coordinates file as the file listed in the directory
            CoordinatesFile = File_Path + DefaultCoordName;

        }
        else if(Option == "3"){
            //Set product number to the current product
            cout << "Running product " << ProductNum << endl;
            User_Selection = 3;

        }

        switch(User_Selection){

       /*
        *
        *   Case 1: Setup new coordinates file
        *
        */
        case 1:
            cout << "Please ensure that the file path with reference images are set up in the references folder and the program has been set up for your new file, if an incorrect file is selected the default program will be modified" << endl;
            cout << "Please enter the program number for the file you wish to modify" << endl;
            //User variable for selection
            int NewCoordnum;
            cin >>NewCoordnum;
            while(!cin){
                cout << "Please enter a valid value" << endl;
            }
            CoordinatesFile = SelectComponents.DrawComponent(NewCoordnum);
        break;

       /*
        *
        *   Case 2: Select a existing program to run
        *
        */
        case 2:
            cout << "Please enter the program number that you wish to run" << endl;
            int UserProgramnum;
            cin >> UserProgramnum;
            while(!cin){
                cout << "Please enter a valid value" << endl;
            }

           /*
            *
            *  Set path based on user input
            *
            */

            switch(UserProgramnum){
            case 1:
                //Select image file 1
                File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/01/";
                Coord_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\01\\Coordinate locations\\";
                break;
            case 2:
                //Select image file 2
                File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/02/";
                Coord_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\02\\Coordinate locations\\";
                break;
            case 3:
                //Select image file 3
                File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/03/";
                Coord_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\03\\Coordinate locations\\";
                break;
            case 4:
                //Select image file 4
                File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/04/";
                Coord_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\04\\Coordinate locations\\";
                break;
            case 5:
                //Select image file 5
                File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/05/";
                Coord_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\05\\Coordinate locations\\";
                break;
            case 6:
                //Select image file 6
                File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
                Coord_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\06\\Coordinate locations\\";
                break;
            default:
                //Select image file 6
                File_Path = "C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/";
                Coord_Path = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\06\\Coordinate locations\\";
                break;
            }


            //Set up file name for coordinates        SET UP TO USE A DEFAULT NAME FOR COORDINATE FILES
            CoordinatesFile = Coord_Path + DefaultCoordName;

            //Read the images stored in the directory and define them as Reference and Input
            Reference = imread(File_Path + "Reference.jpg");

           /*
            *
            *   Camera selection
            *
            */

            if(UseCam == 1){
                //Take a capture on a camera, this is for proof of concept and can be implemented when boards are aquired
                imagecapture.captureimg();
                Input = imread(capture_img_path + "capture.jpg");
            }
            else{
                Input = imread(File_Path + "Different01.jpg");
            }

           /*
            *
            *  Check if images exist
            *
            */

            //Failure condition test mode to check if no image is available
            if (Reference.empty())
            {
                //Print reference image is missing
                printf("Error: reference image is missing\n");
                //Wait for any key press to exit
                cin.get();
                return -1;
            }
            else if (Input.empty())
            {
                //Print input image is missing
                printf("Error: product image is missing\n");
                //Wait for any key press to exit
                cin.get();
                return -1;
            }

           /*
            *
            *   Run software to realign, detect difference and identify faulty components
            *
            */

            //Compute image realignment to remove rotations or scaling issues between reference and input
            Realign.image_realignment(Reference, Input);
            //Load the aligned image
            Aligned = imread(fixedimg);
            //Detect the differences between the reference and the realigned image
            DetectDifference.DetectError(Reference, Aligned);
            //Show the faults detected
            FindFaults.SearchError(CoordinatesFile);

        break;

       /*
        *
        *   Case 3: Run default program
        *
        */
        case 3:
            //Set up file name for coordinates        SET UP TO USE A DEFAULT NAME FOR COORDINATE FILES
            CoordinatesFile = "C:\\Users\\User\\Documents\\QTProjects\\PCBAI\\Samples\\Reference images\\06\\Coordinate locations\\Test.xml";

            //Read the images stored in the directory and define them as Reference and Input
            Reference = imread("C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/Reference.jpg");

           /*
            *
            *   Camera selection
            *
            */

            if(UseCam == 1){
                //Take a capture on a camera, this is for proof of concept and can be implemented when boards are aquired
                imagecapture.captureimg();
                Input = imread(capture_img_path + "capture.jpg");
            }
            else{
                Input = imread("C:/Users/User/Documents/QTProjects/PCBAI/Samples/Reference images/06/Different01.jpg");
            }

           /*
            *
            *  Check if images exist
            *
            */

            //Failure condition test mode to check if no image is available
            if (Reference.empty())
            {
                //Print reference image is missing
                cout << "Error: reference image is missing" << endl;
                //Wait for any key press to exit
                cin.get();
                return -1;
            }
            else if (Input.empty())
            {
                //Print input image is missing
                cout << "Error: Input image is missing" << endl;
                //Wait for any key press to exit
                cin.get();
                return -1;
            }

           /*
            *
            *   Run software to realign, detect difference and identify faulty components
            *
            */

            //Compute image realignment to remove rotations or scaling issues between reference and input
            Realign.image_realignment(Reference, Input);
            //Load the aligned image
            Aligned = imread(fixedimg);
            //Detect the differences between the reference and the realigned image
            DetectDifference.DetectError(Reference, Aligned);
            //Show the faults detected
            FindFaults.SearchError(CoordinatesFile);
        break;
        }

    //Wait until 0 is pressed to exit
    waitKey(0);
    return 0;

}
