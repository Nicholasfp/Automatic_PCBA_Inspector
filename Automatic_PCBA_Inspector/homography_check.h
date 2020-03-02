#ifndef HOMOGRAPHY_CHECK_H_
#define HOMOGRAPHY_CHECK_H_
#include "shared_include.h"
#pragma once
using namespace std;
using namespace cv;

//Global constant for the maximum number of features to search for
const int max_features2 = 500;
//Global constant for the percentage match requirement
const float good_match_percent2 = 0.15f;

//A function that uses ORB to detect key features and align images with homography
void image_alignment(Mat B, Mat A, Mat imReg, Mat h)

{
    //Create two empty matrices for use as grayscale images
    Mat AGray, BGray;
    // Convert A and B matrix to grayscale matrix, AGray and BGray
    cvtColor(A, AGray, COLOR_BGR2GRAY);
    cvtColor(B, BGray, COLOR_BGR2GRAY);

    //Create two vector variables to store keypoints
    vector<KeyPoint> keypointsA, keypointsB;
    //Create two matrices to describe the keypoints for ORB feature detection
    Mat descriptorsA, descriptorsB;

    // Detect ORB features and compute descriptors
    Ptr<Feature2D> orb = ORB::create(max_features2);
    orb->detectAndCompute(AGray, Mat(), keypointsA, descriptorsA);
    orb->detectAndCompute(BGray, Mat(), keypointsB, descriptorsB);

    //Create a vector variable to store matches
    vector<DMatch> matches;
    //Use Description matcher to match the descriptors from A and B
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match(descriptorsA, descriptorsB, matches, Mat());

    // Sort matches by score
    sort(matches.begin(), matches.end());

    // Remove matches under the good match percentage
    const int numGoodMatches = matches.size() * good_match_percent2;
    matches.erase(matches.begin() + numGoodMatches, matches.end());


    //Create a matrix for drawing matches on
    Mat imMatches;
    // Draw the best matches on the images
    drawMatches(A, keypointsA, B, keypointsB, matches, imMatches);
    //Save drawn image as matches.jpg
    imwrite(calculation_img_path + "matches.jpg", imMatches);

    // Extract location of good matches
    vector<Point2f> pointsA, pointsB;

    //Run a for loop to loop location finding of good matches
    for (size_t i = 0; i < matches.size(); i++)
    {
        pointsA.push_back(keypointsA[matches[i].queryIdx].pt);
        pointsB.push_back(keypointsB[matches[i].trainIdx].pt);
    }

    //Calculate homography
    h = findHomography(pointsA, pointsB, RANSAC);

    //Use homography to warp image for use in alignment
    warpPerspective(A, imReg, h, B.size());

    //Save the output file
    imwrite(output_img_path + "aligned_image.jpg", imReg);

    //Print estimated homography
    cout << "Estimated homography" << endl << h << endl;
}



double homography_check(Mat A, Mat B)
{
    //Create matrices to store the registered image and to store the homography matrix
    Mat h;
    Mat imReg;

    //Align images and calculate homography
    image_alignment(A, B, imReg, h);


    //Display matches
    namedWindow("Matches", WINDOW_NORMAL);
    Mat match_draw = imread(calculation_img_path + "matches.jpg");
    imshow("Matches", match_draw);
    //Display output
    namedWindow("Output", WINDOW_NORMAL);
    Mat Aligned = imread(output_img_path + "aligned_image.jpg");
    imshow("Output", Aligned);




    return 0;
}




#endif

