//
//  main.cpp
//  TinyStepCV
//
//  Created by Argha Chakraborty on 05/12/18.
//  Copyright © 2018 Argha Chakraborty. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

void takeDFT(Mat &source, Mat &dest);
void showDFT(Mat &source);
void recenterDFT(Mat &source);

int main(int argc, const char * argv[]) {
    Mat original = imread("/Users/arghachakraborty/Desktop/cats.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat originalFloat;
    original.convertTo(originalFloat, CV_32FC1, 1.0 / 255.0 );
    Mat dftOriginal;
    takeDFT(originalFloat, dftOriginal);
    showDFT(dftOriginal);
    return 0;
}

void takeDFT(Mat &source, Mat &dest){
    Mat originalComplex[2] = {source, Mat::zeros(source.size(), CV_32F)};
    Mat dftReady;
    merge(originalComplex, 2, dftReady);
    Mat dftOriginal;
    dft(dftReady, dftOriginal, DFT_COMPLEX_OUTPUT);
    dest = dftOriginal;
}

void showDFT(Mat &source){
    Mat splitArray[2] = {Mat::zeros(source.size(), CV_32F)};
    split(source, splitArray);
    Mat dftMagnitude;
    magnitude(splitArray[0], splitArray[1], dftMagnitude);
    dftMagnitude += Scalar::all(1);
    log(dftMagnitude, dftMagnitude);
    normalize(dftMagnitude, dftMagnitude, 0, 1, CV_MINMAX);
    recenterDFT(dftMagnitude);
    imshow("DFT", dftMagnitude);
    waitKey();
}

void recenterDFT(Mat &source){
    int centerX = source.cols / 2;
    int centerY = source.rows / 2;
    Mat q1(source, Rect(0, 0, centerX, centerY));
    Mat q2(source, Rect(centerX, 0, centerX, centerY));
    Mat q3(source, Rect(0, centerY, centerX, centerY));
    Mat q4(source, Rect(centerX, centerY, centerX, centerY));
    Mat swapMap;
    
    q1.copyTo(swapMap);
    q4.copyTo(q1);
    swapMap.copyTo(q4);
    
    q2.copyTo(swapMap);
    q3.copyTo(q2);
    swapMap.copyTo(q3);
    
}
