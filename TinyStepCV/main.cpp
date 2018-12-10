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
void invertDFT(Mat &source, Mat &destination);
void createGaussian(int row, int col, Mat &output, int ux, int uy, float sigmaX, float sigmaY, float amp);

int main(int argc, const char * argv[]) {
    Mat original = imread("/Users/arghachakraborty/Desktop/cats.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat output;
    createGaussian(256, 256, output, 128, 128, 10.0f, 10.0f, 1.0f);
    imshow("Gaussian", output);
    waitKey();
//    Mat originalFloat;
//    original.convertTo(originalFloat, CV_32FC1, 1.0 / 255.0 );
//    Mat dftOriginal;
//    takeDFT(originalFloat, dftOriginal);
//    showDFT(dftOriginal);
//    Mat invertedDFT;
//    invertDFT(dftOriginal, invertedDFT);
//    imshow("InvertDFTResult", invertedDFT);
//    waitKey();
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

void invertDFT(Mat &source, Mat &destination){
    dft(source, destination, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
}
void createGaussian(int row, int col, Mat &output, int ux, int uy, float sigmaX, float sigmaY, float amp){
    Mat temp = Mat(row, col, CV_32F);
    for (int r = 0; r < row; r++) {
        for (int c = 0; c< col; c++) {
            float x = ((c - ux) * ((float)c - ux)) / (2.0f * sigmaX * sigmaX);
            float y = ((r - uy) * ((float)r - uy)) / (2.0f * sigmaY * sigmaY);
            float val = amp * exp(-(x + y));
            temp.at<float>(r, c) = val;
        }
    }
    normalize(temp, temp, 0.0f, 1.0f, NORM_MINMAX);
    output = temp;
}
