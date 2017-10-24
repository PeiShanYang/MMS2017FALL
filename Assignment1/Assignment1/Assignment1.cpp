// Assignment1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	Mat Image = imread("000.jpg");
	Mat GrayImage = Image.clone();
	Mat BW1Image(1000, 1000, CV_8UC1);
	Mat BW2Image(500, 500, CV_8U, Scalar(100));
	
	int i, j;
	uchar g; // g是用來放三個顏色的平均
	for(i = 0; i < Image.rows; i++)
	{
		for(j = 0; j < Image.cols; j++)
		{
			g = (Image.at<Vec3b>(i, j)[0] + Image.at<Vec3b>(i, j)[1] + Image.at<Vec3b>(i, j)[2]) / 3;
			if(i == 250)printf("(%d, %d) %u\n", i, j, g);
			GrayImage.at<Vec3b>(i, j)[0] = g;
			GrayImage.at<Vec3b>(i, j)[1] = g;
			GrayImage.at<Vec3b>(i, j)[2] = g;
		}
	}
	for (i = 0; i < GrayImage.rows; i++)
	{
		for (j = 0; j < GrayImage.cols; j++)
		{
			if (GrayImage.at<Vec3b>(i, j)[0] >= 201)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 255;
			}
			else if (GrayImage.at<Vec3b>(i, j)[0] >= 151)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 255;
			}
			else if (GrayImage.at<Vec3b>(i, j)[0] >= 101)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			}
			else if (GrayImage.at<Vec3b>(i, j)[0] >= 51)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 0;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			}
			else
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 0;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			}
		}
	}
	

	namedWindow("Image", WINDOW_AUTOSIZE);
	namedWindow("GrayImage", WINDOW_AUTOSIZE);
	namedWindow("BW1Image", WINDOW_AUTOSIZE);
	imshow("Image", Image);
	imshow("GrayImage", GrayImage);
	imshow("BW1Image", BW1Image);
	waitKey(0);

	return 0;
}