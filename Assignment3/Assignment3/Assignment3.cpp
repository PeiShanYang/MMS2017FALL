// Assignment3.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat reference, target, i2p;
	reference = imread("i1.pgm");
	target = imread("i2.pgm");
	i2p = target.clone();

	int select; // 給使用者輸入選項
	
	printf("Please enter the number to select the function.\n");
	printf("1. Sequential search.\n"); // Sequential search
	printf("2. 2D logarithmic search.\n"); // 2D logarithm search
	printf("3. SNR.\n"); // 2D logarithm search
	printf("Others. Exist.\n");

	scanf_s("%d", &select);

	if(select == 1)
	{
		// Sequential search是依原始座標中心一塊一塊與周邊16*16比較
		int x, y; // 原始圖片座標參數
		for(x = 0; x < target.rows; x = x + 16)
		{
			for(y = 0; y < target.cols; y = y + 16)
			{
				double minMAD = DBL_MAX;
				int u = 0, v = 0; // 紀錄差異最小的
				int i, j; // 比較用的參數，紀錄相對座標
				for(i = -15; i < 16; i++)
				{
					for(j = -15; j < 16; j++)
					{
						double temp = 0;
						if((x + i) >= 0 && (y + j) >= 0 && (x + i) < target.rows
							&& (y + j) < target.cols)
						{
							// 如果已超出圖片範圍就無需運算
							int m, n; // 累積周遭用的參數
							for(m = 0; m < 16; m++)
							{
								for(n = 0; n < 16; n++)
								{
									if((x + i + m) >= 0 && (y + j + n) >= 0
										&& (x + i + m) < target.rows && (y + j + n) < target.cols)
									{ // 如果沒超出圖片範圍才需運算
										temp = temp + abs(target.at<Vec3b>(x + m, y + n)[0]
											- reference.at<Vec3b>(x + i + m, y + j + n)[0]);
										// 將target與reference差異的motion累積起
									}
								}
							}
							temp = temp / (16*16); // 平均
						}
						if(temp < minMAD)
						{
							minMAD = temp;
							u = i;
							v = j;
						} // 如果比最小值還小，即替換
					}
				}
				// 整理輸出結果
				u = x + u; // 將u轉變為絕對位置
				v = y + v; // 將v轉變為絕對位置
				for (i = 0; i < 16; i++)
				{
					for (j = 0; j < 16; j++)
					{
						if ((x + i) >= 0 && (y + j) >= 0 && (u + i) >= 0 && (v + j) >= 0
							&& (x + i) < target.rows && (y + j) < target.cols
							&& (u + i) < target.rows && (v + j) < target.cols)
						{
							// 如果沒超出圖片範圍才需運算
							// 整理三通道
							i2p.at<Vec3b>(x + i, y + j)[0] = target.at<Vec3b>(u + i, v + j)[0];
							i2p.at<Vec3b>(x + i, y + j)[1] = target.at<Vec3b>(u + i, v + j)[1];
							i2p.at<Vec3b>(x + i, y + j)[2] = target.at<Vec3b>(u + i, v + j)[2];
						}
					}
				}
			}
		}
	}
	
	else if(select == 2)
	{
		// 2D logarithmic search 為沿著最小施針方向進行運算
		int x, y; // 原始圖片座標參數
		for (x = 31; x < target.rows; x = x + 16)
		{
			for (y = 31; y < target.cols; y = y + 16)
			{
				int offset = ceil(31 / 2);
				int u = x, v = y; // 紀錄目前位置
				
				// 以自己為中心，以鄰近一格運算
				vector<Point> macroblock;
				macroblock.push_back(Point(u - offset, v - offset));
				macroblock.push_back(Point(u - offset, v));
				macroblock.push_back(Point(u - offset, v + offset));
				macroblock.push_back(Point(u, v - offset));
				macroblock.push_back(Point(u, v));
				macroblock.push_back(Point(u, v + offset));
				macroblock.push_back(Point(u + offset, v - offset));
				macroblock.push_back(Point(u + offset, v));
				macroblock.push_back(Point(u + offset, v + offset));
				
				bool last = false; // 若offset為1，轉回為真
				while (last != true)
				{
					int minx, miny;
					double minMAD = DBL_MAX;
					double temp = 0;
					int i;
					for (i = 0; i < 9; i++)
					{
						int m, n; // 累積周遭用的參數
						for (m = 0; m < 16; m++)
						{
							for (n = 0; n < 16; n++)
							{
								if ((x + macroblock[i].x + m) >= 0 && (y + macroblock[i].y + n) >= 0
									&& (x + macroblock[i].x + m) < target.rows && (y + macroblock[i].y + n) < target.cols)
								{ // 如果沒超出圖片範圍才需運算
									temp = temp + abs(target.at<Vec3b>(x + m, y + n)[0]
										- reference.at<Vec3b>(x + macroblock[i].x + m, y + macroblock[i].y + n)[0]);
									// 將target與reference差異的motion累積起，找附近九宮格
								}
							}
						}
						temp = temp / 16 / 16; // 平均
						if (temp < minMAD)
						{
							// 替換最小
							minMAD = temp;
							minx = macroblock[i].x;
							miny = macroblock[i].y;
						}
					}
					// 將u、v替換為失真最小座標
					u = minx;
					v = miny;
					// 進行到沒有offset只剩最後一個時，轉為真，並在做最後一次
					if(offset == 1)last = true;
					offset = ceil(offset / 2);
					macroblock.clear();
					macroblock.push_back(Point(u - offset, v - offset));
					macroblock.push_back(Point(u - offset, v));
					macroblock.push_back(Point(u - offset, v + offset));
					macroblock.push_back(Point(u, v - offset));
					macroblock.push_back(Point(u, v));
					macroblock.push_back(Point(u, v + offset));
					macroblock.push_back(Point(u + offset, v - offset));
					macroblock.push_back(Point(u + offset, v));
					macroblock.push_back(Point(u + offset, v + offset));
				}
				int i, j;
				for (i = 0; i < 16; i++)
				{
					for (j = 0; j < 16; j++)
					{
						if ((x + i) >= 0 && (y + j) >= 0 && (u + i) >= 0
							&& (v + j) >= 0 && (x + i) < target.rows && (y + j) < target.cols
							&& (u + i) < target.rows && (v + j) < target.cols)
						{
							// 整理三通道
							i2p.at<Vec3b>(x + i, y + j)[0] = target.at<Vec3b>(u + i, v + j)[0];
							i2p.at<Vec3b>(x + i, y + j)[1] = target.at<Vec3b>(u + i, v + j)[1];
							i2p.at<Vec3b>(x + i, y + j)[2] = target.at<Vec3b>(u + i, v + j)[2];
						}
					}
				}
			}
		}
	}
	else if (select == 3)
	{
		// 引入reference和兩結果的jpg檔
		IplImage *src1 = cvLoadImage("reference.jpg");
		IplImage *seq = cvLoadImage("sequentialsearch.jpg");
		IplImage *tdl = cvLoadImage("2Dlogarithmicsearch.jpg");
		IplImage *src2;
		src2 = seq;

		// 參數設定
		long long int sigma = 0;
		long long int squre = 0;
		double SNR = 0.0;
		int frameSize = src1->height*src1->width * 3;
		// 三通道的累積先設為0
		int blue1 = 0, blue2 = 0;
		int green1 = 0, green2 = 0;
		int red1 = 0, red2 = 0;

		int i, j, k;
		for(k = 0; k < 2; k++)
		{
			if(k == 1)
			{
				src2 = tdl;
			}
			for(i = 0; i < src1->height; i++)
			{
				for(j = 0; j < src1->widthStep; j = j + 3)
				{
					//藍色
					blue1 = (int)(uchar)src1->imageData[i*src1->widthStep + j];
					blue2 = (int)(uchar)src2->imageData[i*src2->widthStep + j];

					// 綠色
					green1 = (int)(uchar)src1->imageData[i*src1->widthStep + j + 1];
					green2 = (int)(uchar)src2->imageData[i*src2->widthStep + j + 1];

					// 紅色
					red1 = (int)(uchar)src1->imageData[i*src1->widthStep + j + 2];
					red2 = (int)(uchar)src2->imageData[i*src2->widthStep + j + 2];

					// 分母
					sigma = sigma + (blue1 - blue2) * (blue1 - blue2)
						+ (green1 - green2) * (green1 - green2)
						+ (red1 - red2) * (red1 - red2);
					// 分子
					squre = squre + (blue1 * blue1) + (green1 * green1) + (red1 * red1);
				}
			}
			SNR = 10 * log10(squre / sigma);
			if(k == 0)printf("Sequential Search SNR : %f\n", SNR);
			else if (k == 1)printf("2D Logarithmic Search SNR : %f\n", SNR);
		}
		cvWaitKey(0);
		system("pause");
		return 0;
	}

	else return 0;

	// 建立視窗，顯示影像
	namedWindow("reference", WINDOW_AUTOSIZE);
	namedWindow("target", WINDOW_AUTOSIZE);
	namedWindow("i2p", WINDOW_AUTOSIZE);
	imshow("reference", reference);
	imshow("target", target);
	imshow("i2p", i2p);

	waitKey(0);

	// 釋放影像，關閉視窗
	reference.release();
	target.release();
	i2p.release();
	destroyAllWindows();

	return 0;
}