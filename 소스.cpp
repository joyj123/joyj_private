#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat mtx2;
	mtx2 = Mat(3, 3, CV_32F);
	Mat cmtx2;
	cmtx2 = Mat(10, 1, CV_64FC2);
	cmtx2.setTo(10);
	cout << cmtx2 << endl;
	return 0;
}