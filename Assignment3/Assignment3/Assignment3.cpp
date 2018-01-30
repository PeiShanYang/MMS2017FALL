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
	printf("1. Sequential search.\n");
	printf("2. 2D logarithm search.\n");
	printf("Others. Exist.\n");

	scanf_s("%d", &select);

	if(select == 1)
	{
		// Sequential search是依原始座標中心一塊一塊與周邊16*16比較
		int x, y; // 原始圖片座標參數
		int centerx, centery;
		for(x = 0; x < target.rows; x = x + 16)
		{
			for(y = 0; y < target.cols; y = y + 16)
			{
				double minMAD = DBL_MAX;
				int minu = 0, minv = 0; // 紀錄差異最小的
				int u, v; // 比較圖片座標用相對去加減
				centerx = x + 8, centery = y + 8;
				for(u = -8; u < 9; u++)
				{
					for(v = -8; v < 9; v++)
					{
						double temp = 0;
						if((centerx + u) < 0 || (centery + v) < 0
							|| (centerx + u) >= target.rows || (centery + v) >= target.cols)
							break;
						else
						{
							temp = target.at<Vec3b>(centerx + u, centery + v)[0] - reference.at<Vec3b>(centerx, centery)[0];
							temp = abs(temp);
						}
						if(temp < minMAD)
						{
							minMAD = temp;
							minu = u;
							minv = v;
						}
					}
				}
				int i, j;
				for (i = -8; i < 9; i++)
				{
					for (j = -8; j < 9; j++)
					{
						if ((centerx + i) >= 0 && (centery + j) >= 0 && (centerx + minu + i) >= 0 && (centery + minv + j) >= 0 && (centerx + i) < target.rows && (centery + j) < target.cols && (centerx + minu + i) < target.rows && (centery + minv + j) < target.cols)
						{
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