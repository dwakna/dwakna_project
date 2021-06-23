#include<iostream>
#include<vector>
#include<string>
#include<mutex>
#include<thread>
#include<condition_variable>
#include<chrono>
#include<cpprest/http_client.h>
#include<cpprest/filestream.h>
#include<cpprest/uri.h>
#include<cpprest/json.h>
#include<json/json.h>
#include<json/reader.h>
#include<json/writer.h>
#include<json/value.h>
#include "Header.h"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace json;
using namespace concurrency::streams;
using namespace std;

//객체의 좌표를 담기 위한 구조체
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
	Parser() {}
	Parser(string objectStr);
	vector<Data> parsing();
};
