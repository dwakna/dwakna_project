#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<opencv2/opencv.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include "mysql.h"
#include "Parser.h"
#include "voms_log.h"

using namespace std;
using namespace cv;

class Drawer
{
private:
	std::mutex drawerM_;
	std::condition_variable drawerCV_;
	std::thread drawerTh_;
	std::vector<Data> coorData_;
	std::string path_;
	std::string stime_;
	bool stopFlag_;
	void proc();
	void drawRectangle();
	void sendToAim(std::string path, std::string camid);
	
	MYSQL db_;
public:
	Drawer();
	~Drawer();
	void receiveVec(vector<Data> coorData, string path, string stime);	
};
