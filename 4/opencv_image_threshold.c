#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define IMG_Width 640
#define IMG_Height 480

int main(void)
{
	int img_width, img_height;
	img_width = IMG_Width;
	img_height = 480;

	Mat mat_image_org_color;
	Mat mat_image_org_gray;
	Mat mat_image_gray_result;
	Mat mat_image_binary;
	Mat image;

	Scalar GREEN(0,255,0);
	Scalar RED(0,0,255);
	Scalar BLUE(255,0,0);
	Scalar YELLOW(0,255,255);

	//VideoCapture cap(0); //usb연결되어있는 카메라
	mat_image_org_color = imread("/home/pi/KHT/OpenCV/4/road_sample.jpg");

	img_width = mat_image_org_color.size().width/2;
	img_height = mat_image_org_color.size().height/2;

	namedWindow("Display window", CV_WINDOW_NORMAL);
	resizeWindow("Display window", img_width, img_height);
	moveWindow("Display window", 10,10);

	namedWindow("Gray Image window", CV_WINDOW_NORMAL);
	resizeWindow("Gray Image window", img_width, img_height);
	moveWindow("Gray Image window", 700,10);

	namedWindow("Binary Image window", CV_WINDOW_NORMAL);
	resizeWindow("Binary Image window", img_width, img_height);
	moveWindow("Binary Image window", 10,500);

	while(1)
	{
		cv::cvtColor(mat_image_org_color,mat_image_org_gray,CV_RGB2GRAY);
		threshold(mat_image_org_gray,mat_image_binary,127,255,THRESH_BINARY); //127보다 큰지 작은지로 이진화
		if(mat_image_org_color.empty())
		{
			cerr<<"빈 영상입니다.\n";
			return -1;
		}

		imshow("Display window", mat_image_org_color);
		imshow("Gray Image window", mat_image_org_gray);
		imshow("Binary Image window", mat_image_binary);
		if(waitKey(10)>0)
		{
			break;
		}
	}
	destroyAllWindows();
	return 0;
}
