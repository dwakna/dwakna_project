#include <iostream>
#include <vector>

using namespace std;

struct Data
{
	int x_coor, y_coor, width, height;
	Data() {};
	Data(int x_coor, int y_coor, int width, int height)
	{
		this->x_coor = x_coor;
		this->y_coor = y_coor;
		this->width = width;
		this->height = height;
	}
};

class Parser
{
	string objectStr_;
public:
	vector<Data> objCoor_;
	Parser() {}
	Parser() {string objectStr};
	void parsing();
}
