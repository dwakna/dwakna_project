#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Drawer
{
	vector<Data> vec_;
	void drawRectangle(char* buffer, int length);
public:
	Drawer();
	Drawer(vector<Data> &vec);
};
