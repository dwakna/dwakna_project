#include<iostream>
#include<cpprest/http_client.h>
#include<cpprest/filestream.h>
#include<cpprest/uri.h>
#include<cpprest/json.h>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<json/json.h>
#include<json/reader.h>
#include<json/writer.h>
#include<json/value.h>
//#include<voms_log.h>

#include "Drawer.h"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace json;

class AnalyzeImg
{
private:
	std::mutex azM_;
	std::condition_variable azCV_;
	bool stopFlag_;
	std::thread azTh_;
	std::queue<std::string> pathStr_;
	void proc();
	std::string requestAzure(std::string str);
	Drawer *dro;
	std::string stime;
public:
	AnalyzeImg();
	~AnalyzeImg();
	void setFilePath(std::string imgPath, std::string stime);
};
