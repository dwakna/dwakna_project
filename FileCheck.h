#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<string>
#include<vector>
#include<chrono>
#include<string>
#include<fstream>
#include<filesystem>
#include<sys/types.h>
#include<dirent.h>
#include<cstring>
#include<cerrno>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<cstdlib>
#include<dirent.h>
#include<sys/stat.h>

#include "AnalyzeImg.h"




#if 0
struct PathStruct
{
	string fileName, string filePath;
	PathStruct() {};
	PathStruct(string fileName, filePath)
	{
		this->fileName = fileName;
		this->filePath = filePath;
	}
};
#endif

class FileCheck
{
private:
	std::thread fileTh_;
	std::mutex fileM_;
	std::condition_variable fileCV_;
	std::vector<std::string> pathList_;
	std::string stime;
	void init();
	void proc();
	void getFileList(std::string folderName);
	bool IsImg(std::string fileName);
	bool IsOrg(std::string fileName);
	bool checkTime(std::string filePath);
	AnalyzeImg *azo;
public:
	FileCheck();
	~FileCheck();
	void run();
};
