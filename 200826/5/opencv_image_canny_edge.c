#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define IMG_Width 640
#define IMG_Height 480

Mat Canny_Edge_Detection(Mat img, int minv, int maxv)
{
	Mat mat_blur_img, mat_canny_img;
	blur(img, mat_blur_img, Size(3,3));
	Canny(mat_blur_img,mat_canny_img,minv,maxv,3);
	return mat_canny_img;
}


int main(void)
{
	int img_width, img_height;
	img_width = 640;
	img_height = 480;

	Mat mat_image_org_color;
	Mat mat_image_org_gray;
	Mat mat_image_gray_result;
	Mat mat_image_canny_edge;
	Mat mat_image_canny_edge1;
	Mat mat_image_canny_edge2;
	Mat mat_image_canny_edge3;
	
	Mat image;

	Scalar GREEN(0,255,0);
	Scalar RED(0,0,255);
	Scalar BLUE(255,0,0);
	Scalar YELLOW(0,255,255);

	//VideoCapture cap(0); //usb연결되어있는 카메라
	mat_image_org_color = imread("/home/pi/KHT/OpenCV/5/road_picture.jpeg");

	img_width = mat_image_org_color.size().width*3/5;
	img_height = mat_image_org_color.size().height*3/5;

	namedWindow("Display window", CV_WINDOW_NORMAL);
	resizeWindow("Display window", img_width, img_height);
	moveWindow("Display window", 10,10);
		
	namedWindow("Display window1", CV_WINDOW_NORMAL);
	resizeWindow("Display window1", img_width, img_height);
	moveWindow("Display window1", 10,50 + img_height);
	
	namedWindow("Display window2", CV_WINDOW_NORMAL);
	resizeWindow("Display window2", img_width, img_height);
	moveWindow("Display window2", 50 + img_width,10);
		
	namedWindow("Display window3", CV_WINDOW_NORMAL);
	resizeWindow("Display window3", img_width, img_height);
	moveWindow("Display window3", 50 + img_width,50 + img_height);
	
/*
	namedWindow("Gray Image window", CV_WINDOW_NORMAL);
	resizeWindow("Gray Image window", img_width, img_height);
	moveWindow("Gray Image window", 50+img_width,10);

	namedWindow("Canny Edge Image window", CV_WINDOW_NORMAL);
	resizeWindow("Canny Edge Image window", img_width, img_height);
	moveWindow("Canny Edge Image window", 10,50+img_height);
*/

	cvtColor(mat_image_org_color,mat_image_org_gray,CV_RGB2GRAY);
	mat_image_canny_edge  = Canny_Edge_Detection( mat_image_org_gray ,117,351);
	mat_image_canny_edge1 = Canny_Edge_Detection( mat_image_org_gray ,200,250);
	mat_image_canny_edge2 = Canny_Edge_Detection( mat_image_org_gray ,170,250);
	mat_image_canny_edge3 = Canny_Edge_Detection( mat_image_org_gray ,200,250);
	
	while(1)
	{
		//mat_image_org_color = imread("");
		vector<Vec4i> linesP;	//4개의 점을 int로
		
		//HoughLinesP(mat_image_canny_edge, linesP, 1, CV_PI/180,30,30,10);
		//Gray Image Processing


		for(int i=0;i<linesP.size();i++)
		{
			Vec4i L = linesP[i];
			line(mat_image_org_color, Point(L[0],L[1]),Point(L[2],L[3]), Scalar(0,0,255), 3, LINE_AA);
		}

		if(mat_image_org_color.empty())
		{
			cerr<<"빈 영상입니다.\n";
			return -1;
		}
//		imshow("Display window", mat_image_org_color);
/*		imshow("Gray Image window", mat_image_org_gray);
		imshow("Canny Edge Image window", mat_image_canny_edge);
*/
imshow("Display window", mat_image_canny_edge);
imshow("Display window1", mat_image_canny_edge1);
imshow("Display window2", mat_image_canny_edge2);
imshow("Display window3", mat_image_canny_edge3);


		if(waitKey(10)>0)
		{
			break;
		}
	}
	destroyAllWindows();
	return 0;
}
