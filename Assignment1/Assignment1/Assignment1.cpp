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
	Mat GrayImage = Image.clone(); // Gray
	Mat BW1Image(1000, 1000, CV_8UC1); // Dithering
	Mat BW2Image(500, 500, CV_8UC1); // Side Effect of Dithering
	
	int i, j;
	uchar g; // g是用來放三個顏色的平均

	// 轉成灰階
	for(i = 0; i < Image.cols; i++)
	{
		for(j = 0; j < Image.rows; j++)
		{
			g = (Image.at<Vec3b>(i, j)[0] + Image.at<Vec3b>(i, j)[1] + Image.at<Vec3b>(i, j)[2]) / 3;
			//if(i == 250)printf("(%d, %d) %u\n", i, j, g);
			GrayImage.at<Vec3b>(i, j)[0] = g;
			GrayImage.at<Vec3b>(i, j)[1] = g;
			GrayImage.at<Vec3b>(i, j)[2] = g;
		}
	}

	// 黑白Dithering
	for (i = 0; i < GrayImage.cols; i++)
	{
		for (j = 0; j < GrayImage.rows; j++)
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

	// 黑白Side Effect of Dithering
	int DitherMatrix[16] = {0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5};
	int x, y;
	for (i = 0; i < GrayImage.cols; i++)
	{
		for (j = 0; j < GrayImage.rows; j++)
		{
			x = i % 4;
			y = j % 4;
			if (GrayImage.at<Vec3b>(i, j)[0]> DitherMatrix[x * 4 + y] * 16)
				BW2Image.at<uchar>(i ,j) = 255;
			else BW2Image.at<uchar>(i, j) = 0;
		}
	}
	/* BEGIN
		for x = 0 to Xmax // columns
			for y = 0 to Ymax // rows
				i = x mod n;
				y = y mod n; // n = 4
				// I(x, y) is the Input, O(x, y) is the Output,
				// D is the dither matrix.
				If I(x, y) > D(i, j)
					O(x, y) = 1;
				else
					O(x, y) = 0;
		END */
	

	namedWindow("Image", WINDOW_AUTOSIZE);
	namedWindow("GrayImage", WINDOW_AUTOSIZE);
	namedWindow("BW1Image", WINDOW_AUTOSIZE);
	namedWindow("BW2Image", WINDOW_AUTOSIZE);
	imshow("Image", Image);
	imshow("Gray", GrayImage);
	imshow("Dithering", BW1Image);
	imshow("Side Effect of Dithering", BW2Image);
	waitKey(0);

	return 0;
}
