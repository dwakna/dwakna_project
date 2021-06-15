#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
using namespace cv;

int main()
{
	string imgPath = "/home/ict01/workplace/OJT/StorageIO/img/img1.jpg";
	ifstream ifs;
	ifs.open(imgPath, ios::binary);
	ifs.seekg(0, std::ios::end);
	int bufferLength = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	char *buffer = new char[bufferLength];
	ifs.read(buffer, bufferLength);
	cv::Mat matImg;
	matImg = cv::imdecode(cv::Mat(1, bufferLength, CV_8UC1, buffer), -1);
	imwrite("/home/ict01/workplace/OJT/StorageIO/img/test.jpg", matImg);
	delete []buffer;
	return 0;
}
