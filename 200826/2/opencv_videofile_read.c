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
	img_width = 640;
	img_height = 480;

	Mat mat_image_org_color;
	Mat mat_image_org_gray;
	Mat mat_image_gray_result;
	Mat image;

	Scalar GREEN(0,255,0);
	Scalar RED(0,0,255);
	Scalar BLUE(255,0,0);
	Scalar YELLOW(0,255,255);

	//VideoCapture cap(0); //usb연결되어있는 카메라
	VideoCapture cap("/home/pi/KHT/OpenCV/2/track-s.avi");	//동영상 열기
	cap.set(CV_CAP_PROP_FRAME_WIDTH, img_width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, img_height);

	if(!cap.isOpened())
	{
		cerr<<"에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}
	cap.read(mat_image_org_color);

	printf("Image size[%3d, %3d]\n", img_width, img_height);
	namedWindow("Display window", CV_WINDOW_NORMAL);
	resizeWindow("Display window", img_width, img_height);
	moveWindow("Display window", 10,10);

	while(1)
	{
		cap.read(mat_image_org_color);
		if(mat_image_org_color.empty())
		{
			cerr<<"빈 영상입니다.\n";
			return -1;
		}

		imshow("Display window", mat_image_org_color);
		if(waitKey(10)>0)
		{
			break;
		}
	}
	
	cap.release();
	destroyAllWindows();
	return 0;
}
