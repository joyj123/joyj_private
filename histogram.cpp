/*
CV_BGR-> COlOR_BGR
CV_MINMAX->NORM_MINMAX
*/


#include <iostream>
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world450d.lib")
#else
#pragma comment(lib, "opencv_world450.lib")
#endif

using namespace cv;
using namespace std;

Mat imgA;

int main()
{
	imgA = imread("북유럽 거리.jpg");
	imshow("img1", imgA);

	int hbins = 30; //histogram x axis size, that is histSize,
					//ex)2->0~128, 129~256
	int channels[] = { 0 };
	int histSize[] = { hbins };
	float hranges[] = { 0,180 };//hue is 0~80
	const float* ranges[] = { hranges };

	Mat patch_HSV;
	MatND HistA, HistB;

	//cal histogram & normalization
	cvtColor(imgA, patch_HSV, COLOR_BGR2HSV);
	//Hue range is[0, 179], Saturation range is[0, 255] and Value range is[0,255]

	calcHist(&patch_HSV, 1, channels, Mat(),//MaskForHisto, // do use mask
		HistA, 1, histSize, ranges, true, // the histogram is uniform
		false);
	normalize(HistA, HistA, 0, 255, NORM_MINMAX);

	//Mat for drawing
	Mat histimg = Mat::zeros(200, 320, CV_8UC3);
	int binW = histimg.cols / hbins;

	Mat buf(1, hbins, CV_8UC3);
	//Set RGB color
	for (int i = 0; i < hbins; i++)
		buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i * 180. / hbins), 255, 255);
	cvtColor(buf, buf, COLOR_HSV2BGR);

	//drawing routine
	for (int i = 0; i < hbins; i++)
	{
		//int val=saturate_cast<int>(HistA.at<float>(i)*histimg.rows/255);
		int val = HistA.at<float>(i) * histimg.rows / 255;
		rectangle(histimg, Point(i * binW, histimg.rows),
			Point((i + 1) * binW, histimg.rows - val),
			Scalar(buf.at< Vec3b>(i)), -1, 8);

		int r, g, b;
		b = buf.at<Vec3b>(i)[0];
		g = buf.at<Vec3b>(i)[1];
		r = buf.at<Vec3b>(i)[2];
		//show bin and RGB value
		printf("[%d] r=%d, g=%d, b=%d, bins=%d \n", i, r, g, b, val);
	}
	imshow("Histogram", histimg);
	waitKey(0);

	return 0;
}