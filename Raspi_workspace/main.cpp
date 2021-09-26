#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

#define WHITE(X)        (countNonZero(X))
#define BLACK(X)        ((X.rows * X.cols) - countNonZero(X))

#define WIDTH(X)        X.cols
#define HEIGHT(X)       X.rows

#define MID_WIDTH(X)    (WIDTH(X)/2)
#define MID_HEIGHT(X)   (HEIGHT(X)/2)

String PATH= "G:/Classification_Machine/Picture";
Mat origin_img, gray_img, blur_img, resize_img, bin_img, skel_img;
Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));

int bottom(Mat src, Mat binary);

int main()
{
    origin_img = imread(PATH+"/2.jpg",1);

    resize(origin_img, resize_img, Size(WIDTH(origin_img)*0.4, HEIGHT(origin_img)*0.4),0,0, INTER_LINEAR);

    cvtColor(resize_img,gray_img,COLOR_BGR2GRAY);

    GaussianBlur(gray_img, blur_img, Size(5,5),0,0);

    adaptiveThreshold(blur_img, bin_img, 225, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 9, 10);
    morphologyEx(bin_img,bin_img, MORPH_CLOSE, element);
    
    cout << "WHITE: " << WHITE(bin_img) << endl;
    cout << "BLACK: " << BLACK(bin_img) << endl;
    cout << "Percent: " << ((float) WHITE(bin_img))/((float) BLACK(bin_img))*100<<endl;

    bottom(resize_img, bin_img);
    imshow("Blur", blur_img);
    imshow("Binary", bin_img);
    imshow("Origin", resize_img);
    waitKey(0);
    return 0;
}

int bottom(Mat src, Mat binary)
{
    int _position = 0;
    static int pixel;
    int count = 0;
    for (int y = MID_HEIGHT(src); y < HEIGHT(src); y++)
    {
        for (int x = MID_WIDTH(src); x < WIDTH(src); x++)
        {
            pixel = (int)binary.at<uchar>(y,x);
            if (pixel != 0)
            {
                count++;
            }
        }
        if (count==0)
        {
            *(&_position) = y-1 ;
            break;
        }
        count = 0 ; 
    }
    cout << "Y = " << *(&_position) <<endl;
    line(src, Point(MID_WIDTH(src),*(&_position)), Point(WIDTH(src),*(&_position)), Scalar(0, 0, 255), 2, 8);
    return *(&_position);
}