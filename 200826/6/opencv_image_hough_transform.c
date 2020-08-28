#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define IMG_Width 640
#define IMG_Height 480

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

	//VideoCapture cap(0); //usb연결되어있는 카메라
	mat_image_org_color = imread("/home/pi/KHT/OpenCV/5/road_picture.jpeg");
	cvtColor(mat_image_org_color,mat_image_org_gray,CV_RGB2GRAY);				/// gray file created

	img_width = mat_image_org_color.size().width*3/4;
	img_height = mat_image_org_color.size().height*3/4;

	namedWindow("Display window", CV_WINDOW_NORMAL);
	resizeWindow("Display window", img_width, img_height);
	moveWindow("Display window", 10,10);

/*	namedWindow("Gray Image window", CV_WINDOW_NORMAL);
	resizeWindow("Gray Image window", img_width, img_height);
	moveWindow("Gray Image window", 50+img_width,10);

	namedWindow("Canny Edge Image window", CV_WINDOW_NORMAL);
	resizeWindow("Canny Edge Image window", img_width, img_height);
	moveWindow("Canny Edge Image window", 10,50+img_height);
*/
	namedWindow("Hough Transform_3_3_1 Image window", CV_WINDOW_NORMAL);
	resizeWindow("Hough Transform_3_3_1 Image window", img_width, img_height);
	moveWindow("Hough Transform_3_3_1 Image window", 10,50+img_height);
	
	namedWindow("Hough Transform_7_3_4 Image window", CV_WINDOW_NORMAL);
	resizeWindow("Hough Transform_7_3_4 Image window", img_width, img_height);
	moveWindow("Hough Transform_7_3_4 Image window", 50+img_width, 10);
	
	namedWindow("Hough Transform_10_3_4 Image window", CV_WINDOW_NORMAL);
	resizeWindow("Hough Transform_10_3_4 Image window", img_width, img_height);
	moveWindow("Hough Transform_10_3_4 Image window", 50+img_width,50+img_height);
	//---------------------------figure setting ---/
	
	
	mat_image_canny_edge = Canny_Edge_Detection( mat_image_org_gray);

	mat_image_Hough_transform_1 = imread("/home/pi/KHT/OpenCV/5/road_picture.jpeg");
	mat_image_Hough_transform_2 = imread("/home/pi/KHT/OpenCV/5/road_picture.jpeg");
	mat_image_Hough_transform_3 = imread("/home/pi/KHT/OpenCV/5/road_picture.jpeg");
	
		vector<Vec4i> linesP;	//4개의 점을 int로
		vector<Vec4i> linesP1, linesP2, linesP3;
		///detecting line from original picture
		HoughLinesP(mat_image_canny_edge, linesP,	1, CV_PI/180,69,65,40);	
		HoughLinesP(mat_image_canny_edge, linesP1, 	1, CV_PI/180,69,70,40);//	3 3 1
		HoughLinesP(mat_image_canny_edge, linesP2, 	1, CV_PI/180,69,75,40);//	7 3 4
		HoughLinesP(mat_image_canny_edge, linesP3, 	1, CV_PI/180,69,80,40);//	10 3 4
		
		
		///drawing the lines on the original picture
		for(int i=0;i<linesP.size();i++)
		{
			Vec4i L = linesP[i];
			line(mat_image_org_color, Point(L[0],L[1]),Point(L[2],L[3]), Scalar(0,0,255), 3, LINE_AA);
		}	
			for(int i=0;i<linesP1.size();i++)
		{
			Vec4i L1 = linesP1[i];
			line(mat_image_Hough_transform_1, Point(L1[0],L1[1]),Point(L1[2],L1[3]), GREEN, 3, LINE_AA);
		}	
			for(int i=0;i<linesP2.size();i++)
		{	
			Vec4i L2 = linesP2[i];
			line(mat_image_Hough_transform_2, Point(L2[0],L2[1]),Point(L2[2],L2[3]), BLUE, 3, LINE_AA);
		}	
			for(int i=0;i<linesP3.size();i++)
		{
			Vec4i L3 = linesP3[i];
			line(mat_image_Hough_transform_3, Point(L3[0],L3[1]),Point(L3[2],L3[3]), YELLOW, 3, LINE_AA);
		
		}
		
		
	while(1)
	{
		

		if(mat_image_org_color.empty())
		{
			cerr<<"빈 영상입니다.\n";
			return -1;
		}
		imshow("Display window", mat_image_org_color);
/*		imshow("Gray Image window", mat_image_org_gray);
		imshow("Canny Edge Image window", mat_image_canny_edge);
*/
		imshow("Hough Transform_3_3_1 Image window", mat_image_Hough_transform_1);
		imshow("Hough Transform_7_3_4 Image window", mat_image_Hough_transform_2);
		imshow("Hough Transform_10_3_4 Image window", mat_image_Hough_transform_3);
		if(waitKey(10)>0)
		{
			break;
		}
	}
	destroyAllWindows();
	return 0;
}
