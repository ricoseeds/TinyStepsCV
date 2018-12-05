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

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Mat test = imread("/Users/arghachakraborty/Desktop/cats.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
//    imshow("DOF", test);
//    imwrite("/Users/arghachakraborty/Desktop/dof_g.png", test);
    namedWindow("DOF", CV_WINDOW_FREERATIO);
    imshow("DOF", test);
//    moveWindow("DOF", 0, 100);
    waitKey();
    return 0;
}
