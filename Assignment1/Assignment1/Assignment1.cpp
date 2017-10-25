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
	Mat GrayImage(500, 500, CV_8UC1); // Gray
	Mat BW1Image(1000, 1000, CV_8UC1); // Dithering
	Mat BW2Image(500, 500, CV_8UC1); // Side Effect of Dithering
	
	int i, j;

	// 轉成灰階
	for(i = 0; i < Image.cols; i++)
	{
		for(j = 0; j < Image.rows; j++)
		{
			GrayImage.at<uchar>(i, j) = (Image.at<Vec3b>(i, j)[0] + Image.at<Vec3b>(i, j)[1] + Image.at<Vec3b>(i, j)[2]) / 3;
		}
	} // gray = (Green + Red + Blue) / 3

	// 黑白Dithering
	for(i = 0; i < GrayImage.cols; i++)
	{
		for(j = 0; j < GrayImage.rows; j++)
		{
			if(GrayImage.at<uchar>(i, j) >= 201)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 255;
			} // 全白
			else if(GrayImage.at<uchar>(i, j) >= 151)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 255;
			} // 點黑第0格
			else if(GrayImage.at<uchar>(i, j) >= 101)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			} // 點黑第0、3格
			else if(GrayImage.at<uchar>(i, j) >= 51)
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 0;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 255;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			} // 點黑第0、1、3格
			else
			{
				BW1Image.at<uchar>(2 * i, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i, 2 * j + 1) = 0;
				BW1Image.at<uchar>(2 * i + 1, 2 * j) = 0;
				BW1Image.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			} // 全黑
		}
	}

	// 黑白Side Effect of Dithering
	int DitherMatrix[16] = {0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5};
	int x, y;
	for(i = 0; i < GrayImage.cols; i++)
	{
		for(j = 0; j < GrayImage.rows; j++)
		{
			x = i % 4;
			y = j % 4;
			if(GrayImage.at<uchar>(i, j) > DitherMatrix[x * 4 + y] * 16)
				BW2Image.at<uchar>(i ,j) = 255;
			else BW2Image.at<uchar>(i, j) = 0;
		}
	}
	/* Algo.
	BEGIN
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
	namedWindow("Gray", WINDOW_AUTOSIZE);
	namedWindow("Dithering", WINDOW_AUTOSIZE);
	namedWindow("Side Effect of Dithering", WINDOW_AUTOSIZE);
	imshow("Image", Image);
	imshow("Gray", GrayImage);
	imshow("Dithering", BW1Image);
	imshow("Side Effect of Dithering", BW2Image);
	waitKey(0);

	return 0;
}
