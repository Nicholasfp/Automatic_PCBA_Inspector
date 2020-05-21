#ifndef INDENTIFYFAULTS_H
#define INDENTIFYFAULTS_H
#include "shared_include.h"
#pragma once

using namespace std;
using namespace cv;

class IdentifyFaultyComponents
{
    public:
        int SearchError(string CoordinatesFile);

    private:
        string ReadName;
        int ReadInitX;
        int ReadInitY;
        int ReadFinalX;
        int ReadFinalY;
        Mat Errors;
        int ErrorThreshold;
};

extern IdentifyFaultyComponents FindFaults;

#endif // INDENTIFYFAULTS_H
