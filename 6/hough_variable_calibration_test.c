#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define IMG_Width 640
#define IMG_Height 480

const char* window_name_th = "Edge Map th";
const char* window_name_min = "Edge Map min";
const char* window_name_max = "Edge Map max";
static void houghThreshold(int, void*)
{
}

static void houghMin(int, void*)
{
}

static void houghMax(int, void*)
{
}

Mat Canny_Edge_Detection(Mat img)
{
	Mat mat_blur_img, mat_canny_img, mat_image_gray;
	
	//cvtColor(img,mat_image_gray,CV_RGB2GRAY);
	blur(img, mat_blur_img, Size(3,3));
	Canny(mat_blur_img,mat_canny_img,117,351,3);
	return mat_canny_img;
}

Mat Canny_Edge_Detection(Mat img, int minv)
{
	///desired value 117 / 351
	Mat mat_blur_img, mat_canny_img;
	blur(img, mat_blur_img, Size(3,3));
	Canny(mat_blur_img,mat_canny_img,minv,minv*3,3);
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
	Mat mat_image_Hough_transform_1;
	Mat mat_image_Hough_transform_2;
	Mat mat_image_Hough_transform_3;
	Mat image;

	Scalar GREEN(0,255,0);
	Scalar RED(0,0,255);
	Scalar BLUE(255,0,0);
	Scalar YELLOW(0,255,255);

	VideoCapture cap(0); //usb연결되어있는 카메라
	//mat_image_org_color = imread("/home/pi/KHT/OpenCV/5/road_picture.jpeg");
	if(!cap.isOpened())
	{
		cerr << "dksehl";
		return -1;
	}
	
	///cvtColor(mat_image_org_color,mat_image_org_gray,CV_RGB2GRAY);				/// gray file created

	img_width = 1280;
	img_height = 640;
	cap.set(CV_CAP_PROP_FRAME_WIDTH, img_width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, img_height);

	namedWindow("Display window", CV_WINDOW_NORMAL);
	resizeWindow("Display window", img_width, img_height);
	moveWindow("Display window", 10,10);

	//---------------------------figure setting ---/
	
	
	
	int threshold_val = 0;
	int min_val = 0;
	int max_val = 0;
	namedWindow( window_name_th, WINDOW_AUTOSIZE );
	namedWindow( window_name_min, WINDOW_AUTOSIZE );
	namedWindow( window_name_max, WINDOW_AUTOSIZE );
	createTrackbar( "Threshold:", window_name_th, &threshold_val, 200, houghThreshold );
	createTrackbar( "Min:", window_name_min, &min_val, 200, houghMin );
	createTrackbar( "Max:", window_name_max, &max_val, 200, houghMax );
	while(1)
	{
		
		
		
		
		cout<<threshold_val <<'\t'<<max_val<<'\t'<<min_val <<'\t'<<'\n';

		if(!cap.isOpened())
		{
			cerr<<"빈 영상입니다.\n";
			return -1;
		}
		cap.read(mat_image_org_color);
		cvtColor(mat_image_org_color,mat_image_org_gray,CV_RGB2GRAY);		
		mat_image_canny_edge = Canny_Edge_Detection( mat_image_org_gray);
	
		vector<Vec4i> linesP;	//4개의 점을 int로

		///detecting line from original picture
		HoughLinesP(mat_image_canny_edge, linesP,	1, CV_PI/180,threshold_val,min_val,max_val);
	
		///drawing the lines on the original picture
		for(int i=0;i<linesP.size();i++)
		{
			Vec4i L = linesP[i];
			line(mat_image_org_color, Point(L[0],L[1]),Point(L[2],L[3]), Scalar(0,0,255), 3, LINE_AA);
		}	

		
		
		
		
		
		imshow("Display window", mat_image_org_color);

		if(waitKey(10)>0)
		{
			break;
		}
	}
	destroyAllWindows();
	return 0;
}
