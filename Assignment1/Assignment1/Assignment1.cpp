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
	Mat DitheringImage(1000, 1000, CV_8UC1); // Dithering
	Mat DitherMatrixImage0(500, 500, CV_8UC1);
	Mat DitherMatrixImage1(500, 500, CV_8UC1);
	Mat DitherMatrixImage2(500, 500, CV_8UC1);
	Mat DitherMatrixImage3(500, 500, CV_8UC1);
	
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
				DitheringImage.at<uchar>(2 * i, 2 * j) = 255;
				DitheringImage.at<uchar>(2 * i, 2 * j + 1) = 255;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j) = 255;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j + 1) = 255;
			} // 全白
			else if(GrayImage.at<uchar>(i, j) >= 151)
			{
				DitheringImage.at<uchar>(2 * i, 2 * j) = 0;
				DitheringImage.at<uchar>(2 * i, 2 * j + 1) = 255;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j) = 255;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j + 1) = 255;
			} // 點黑第0格
			else if(GrayImage.at<uchar>(i, j) >= 101)
			{
				DitheringImage.at<uchar>(2 * i, 2 * j) = 0;
				DitheringImage.at<uchar>(2 * i, 2 * j + 1) = 255;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j) = 255;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			} // 點黑第0、3格
			else if(GrayImage.at<uchar>(i, j) >= 51)
			{
				DitheringImage.at<uchar>(2 * i, 2 * j) = 0;
				DitheringImage.at<uchar>(2 * i, 2 * j + 1) = 0;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j) = 255;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			} // 點黑第0、1、3格
			else
			{
				DitheringImage.at<uchar>(2 * i, 2 * j) = 0;
				DitheringImage.at<uchar>(2 * i, 2 * j + 1) = 0;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j) = 0;
				DitheringImage.at<uchar>(2 * i + 1, 2 * j + 1) = 0;
			} // 全黑
		}
	}

	// 黑白Side Effect of Dithering
	int DitherMatrix[4][16] = {
		{ 0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5},
		{ 0, 12, 3, 15, 8, 4, 11, 7, 2, 14, 1, 13, 10, 6, 9, 5 },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
		{ 0, 7, 5, 2, 8, 15, 13, 10, 11, 12, 14, 9, 3, 4, 6, 1}
	}; // 0是原本的，1是行列相反，2是0~1照順序，3是集中於中間
	int x, y, k;
	for (i = 3; i >= 0; i--)
	{
		for (j = 0; j < GrayImage.cols; j++)
		{
			for (k = 0; k < GrayImage.rows; k++)
			{
				x = j % 4;
				y = k % 4;
				if (GrayImage.at<uchar>(j, k) > DitherMatrix[i][x * 4 + y] * 16)
					DitherMatrixImage0.at<uchar>(j, k) = 255;
				else DitherMatrixImage0.at<uchar>(j, k) = 0;
			}
		}
		if (i == 1)DitherMatrixImage1 = DitherMatrixImage0.clone();
		else if (i == 2)DitherMatrixImage2 = DitherMatrixImage0.clone();
		else if (i == 3)DitherMatrixImage3 = DitherMatrixImage0.clone();
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
	namedWindow("GrayImage", WINDOW_AUTOSIZE);
	namedWindow("DitheringImage", WINDOW_AUTOSIZE);
	namedWindow("DitherMatrixImage0", WINDOW_AUTOSIZE);
	namedWindow("DitherMatrixImage1", WINDOW_AUTOSIZE);
	namedWindow("DitherMatrixImage2", WINDOW_AUTOSIZE);
	namedWindow("DitherMatrixImage3", WINDOW_AUTOSIZE);
	imshow("Image", Image);
	imshow("Gray", GrayImage);
	imshow("DitheringImage", DitheringImage);
	imshow("DitherMatrixImage0", DitherMatrixImage0);
	imshow("DitherMatrixImage1", DitherMatrixImage1);
	imshow("DitherMatrixImage2", DitherMatrixImage2);
	imshow("DitherMatrixImage3", DitherMatrixImage3);
	waitKey(0);

	return 0;
}
