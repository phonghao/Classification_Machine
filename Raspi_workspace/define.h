#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

#define WHITE(X)            (countNonZero(X))
#define BLACK(X)            ((X.rows * X.cols) - countNonZero(X))

#define WIDTH(X)            X.cols
#define HEIGHT(X)           X.rows

#define MID_WIDTH(X)        (WIDTH(X)/2)
#define MID_HEIGHT(X)       (HEIGHT(X)/2)

#define POINT(X)            (*(&X))

String PATH= "G:/Classification_Machine/Picture";
Mat origin_img, gray_img, blur_img, resize_img, bin_img, skel_img;
Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));

int ptBot = 0;
int ptTop = 0;
int ptLeft = 0;
int ptRight = 0;

int bottom(Mat src, Mat binary);
int top(Mat src, Mat binary);
int left(Mat src, Mat binary);
int right(Mat src, Mat binary);

#endif