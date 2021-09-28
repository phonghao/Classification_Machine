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

#define POS_SHOW_X          30
#define POS_SHOW_Y          20

String PATH= "G:/Classification_Machine/Picture";
String Color_windowName = "Result";
String Gray_windowName = "Gray Image";
String Binary_windowName = "Binary Image";
Mat origin_img;
Mat gray_img;
Mat blur_img;
Mat resize_img;
Mat bin_img;
Mat crop_img;
Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));

int mergeHeight = 0;
int mergeWidth = 0;

int ptBottom = 0;
int ptTop = 0;
int ptLeft = 0;
int ptRight = 0;

int Bottom(Mat src, Mat binary);
int Top(Mat src, Mat binary);
int Left(Mat src, Mat binary);
int Right(Mat src, Mat binary);
float Percentage(Mat crop);
String percent;

#endif