#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "define.h"

int main()
{
    origin_img = imread(PATH+"/2.jpg",1);

    resize(origin_img, resize_img, Size(WIDTH(origin_img)*0.25, HEIGHT(origin_img)*0.25),0,0, INTER_LINEAR);

    cvtColor(resize_img,gray_img,COLOR_BGR2GRAY);

    GaussianBlur(gray_img, blur_img, Size(5,5),0,0);

    adaptiveThreshold(blur_img, bin_img, 225, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 9, 10);

    morphologyEx(bin_img,bin_img, MORPH_CLOSE, element);

    ptBottom = Bottom(resize_img, bin_img);
    ptTop    = Top(resize_img, bin_img);
    ptLeft   = Left(resize_img, bin_img);
    ptRight  = Right(resize_img, bin_img);

    Point TopLeft(ptLeft, ptTop);
    Point BottomRight(ptRight, ptBottom);

    bin_img(Rect(TopLeft, BottomRight)).copyTo(crop_img);
    
    rectangle(resize_img,TopLeft,BottomRight,Scalar(0,0,255),1,8);

    percent = to_string(Percentage(ptTop,ptBottom,ptLeft,ptRight,crop_img)).substr(0,5) + "%";
    putText(resize_img, percent, Point(ptRight,ptTop-5), FONT_HERSHEY_DUPLEX, 0.8 ,Scalar(0,255,255), 2);

    namedWindow(Gray_windowName);
    moveWindow(Gray_windowName,POS_SHOW_X,POS_SHOW_Y);
    namedWindow(Color_windowName);
    moveWindow(Color_windowName,POS_SHOW_X+WIDTH(resize_img),POS_SHOW_Y);
    namedWindow(Binary_windowName);
    moveWindow(Binary_windowName,POS_SHOW_X+WIDTH(resize_img)*2,POS_SHOW_Y);

    imshow(Color_windowName, resize_img);
    imshow(Gray_windowName, gray_img);
    imshow(Binary_windowName, bin_img);

    waitKey(0);

    return 0;
}

int Bottom(Mat src, Mat binary)
{
    int _position = 0;
    int _pixel;
    int _count = 0;

    for (int y = MID_HEIGHT(src); y < HEIGHT(src); y++)
    {
        for (int x = MID_WIDTH(src); x < WIDTH(src); x++)
        {
            _pixel = (int)binary.at<uchar>(y,x);
            if (_pixel != 0)
            {
                _count++;
            }
        }
        if (_count==0)
        {
            _position = y ;
            break;
        }
        _count = 0 ; 
    }
    return _position;
}

int Top(Mat src, Mat binary)
{
    int _position = 0;
    int _pixel;
    int _count = 0;

    for (int y = MID_HEIGHT(src); y > 0; y--)
    {
        for (int x = MID_WIDTH(src); x < WIDTH(src); x++)
        {
            _pixel = (int)binary.at<uchar>(y,x);
            if (_pixel != 0)
            {
                _count++;
            }
        }
        if (_count==0)
        {
            _position = y ;
            break;
        }
        _count = 0 ; 
    }
    return _position;
}

int Left(Mat src, Mat binary)
{
    int _position = 0;
    int _pixel;
    int _count = 0;

    for (int x = MID_WIDTH(src); x < WIDTH(src); x++)
    {
        for (int y = MID_HEIGHT(src); y < HEIGHT(src); y++)
        {
            _pixel = (int)binary.at<uchar>(y,x);
            if (_pixel != 0)
            {
                _count++;
            }
        }
        if (_count==0)
        {
            _position = x ;
            break;
        }
        _count = 0 ; 
    }
    return _position;
}

int Right(Mat src, Mat binary)
{
    int _position = 0;
    int _pixel;
    int _count = 0;

    for (int x = MID_WIDTH(src); x > 0; x--)
    {
        for (int y = MID_HEIGHT(src); y < HEIGHT(src); y++)
        {
            _pixel = (int)binary.at<uchar>(y,x);
            if (_pixel != 0)
            {
                _count++;
            }
        }
        if (_count==0)
        {
            _position = x ;
            break;
        }
        _count = 0 ; 
    }
    return _position;
}

// float Percentage(Mat crop)
// {
//     outsideBlack = Black_Outside(ptTop,ptBottom,ptLeft,ptRight,crop_img);
//     return ((float) WHITE(crop))/((float) (BLACK(crop)-50000))*100;
// }

float Percentage(int top, int bottom, int left, int right, Mat crop)
{
    /* Reject black pixel inside bounder */
    int _count = 0;
    int _pixel = 0;
    float _percent = 0;
    for (int i = 0; i<= abs(bottom-top); i++)
    {
        for (int j = 0; j <= abs(right-left); j++)
        {
            _pixel = (int)crop.at<uchar>(i,j);
            if (_pixel != 0)
            {
                break;
            }
            else
            {   
                _count++;
            }
        }
    }

    /* Calculate the percentage of vein */
    _percent= ((float) WHITE(crop))*2.5/((float) (BLACK(crop)-(float)_count))*100;
    return _percent;
}