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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    Mat original = imread("/Users/arghachakraborty/Desktop/cats.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
//    Mat mod = imread("/Users/arghachakraborty/Desktop/cats.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat original = imread("/Users/arghachakraborty/Desktop/cats.jpeg", CV_LOAD_IMAGE_COLOR);
    Mat mod = imread("/Users/arghachakraborty/Desktop/cats.jpeg", CV_LOAD_IMAGE_COLOR);
    
    for (int r = 0; r < mod.rows; r++) {
        for (int c = 0; c < mod.cols; c++) {
//            mod.at<uint8_t>(r, c) += ((double) rand() / (RAND_MAX)) + 1;
//            mod.at<Vec3b>(r, c)[0] = rand() % 255;
//            mod.at<Vec3b>(r, c)[1] = rand() % 127;
//            mod.at<Vec3b>(r, c)[2] = rand() % 63;
        }
    }
    
    imshow("cat", original);
    imshow("modcat", mod);
    waitKey();
    
    return 0;
}
