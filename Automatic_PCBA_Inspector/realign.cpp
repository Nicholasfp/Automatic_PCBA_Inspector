#include "realign.h"

class Realign Realign;

double Realign::image_realignment(Mat input, Mat reference)
{
    {
        //Create two empty matrices for use as grayscale images
        Mat AGray, BGray;
        // Convert A and B matrix to grayscale matrix, AGray and BGray
        cvtColor(reference, AGray, COLOR_BGR2GRAY);
        cvtColor(input, BGray, COLOR_BGR2GRAY);

        //Create two vector variables to store keypoints
        vector<KeyPoint> keypointsReference, keypointsInput;
        //Create two matrices to describe the keypoints for ORB feature detection
        Mat descriptorsReference, descriptorsInput;

        // Detect ORB features and compute descriptors
        Ptr<Feature2D> orb = ORB::create(max_features);
        orb->detectAndCompute(AGray, Mat(), keypointsReference, descriptorsReference);
        orb->detectAndCompute(BGray, Mat(), keypointsInput, descriptorsInput);

        //Create a vector variable to store matches
        vector<DMatch> matches;
        //Use Description matcher to match the descriptors from the reference and the input
        Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
        matcher->match(descriptorsReference, descriptorsInput, matches, Mat());

        // Sort matches by score
        sort(matches.begin(), matches.end());

        // Remove matches under the good match percentage
        const int numGoodMatches = matches.size() * good_match_percent;
        matches.erase(matches.begin() + numGoodMatches, matches.end());


        //Create a matrix for drawing matches on
        Mat imMatches;
        // Draw the best matches on the images
        drawMatches(reference, keypointsReference, input, keypointsInput, matches, imMatches);
        //Save drawn image as matches.jpg
        imwrite(calculation_img_path + "matches.jpg", imMatches);

        // Extract location of good matches
        vector<Point2f> pointsReference, pointsInput;

        //Run a for loop to loop location finding of good matches
        for (size_t i = 0; i < matches.size(); i++)
        {
            pointsReference.push_back(keypointsReference[matches[i].queryIdx].pt);
            pointsInput.push_back(keypointsInput[matches[i].trainIdx].pt);
        }

        //Calculate homography
        homography_matrix = findHomography(pointsReference, pointsInput, RANSAC);

        //Use homography to warp image for use in alignment
        warpPerspective(reference, output, homography_matrix, input.size());
        //Save the output file
        imwrite(output_img_path + "aligned_image.jpg", output);

        //Print estimated homography
        cout << "Estimated homography" << endl << homography_matrix << endl;
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
}
