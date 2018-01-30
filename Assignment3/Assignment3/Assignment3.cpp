// Assignment3.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
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
	printf("2. 2D logarithm search.\n"); // 2D logarithm search
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
						if((x + i) < 0 || (y + j) < 0 || (x + i) >= target.rows
							|| (y + j) >= target.cols)break; // 如果已超出圖片範圍就無需運算
						else
						{
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