#include<iostream>
#include<cpprest/http_client.h>
#include<cpprest/filestream.h>
#include<cpprest/uri.h>
#include<cpprest/json.h>
#include<voms_log.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
//using namespace concurrency::system;


class requestAzure
{
	void requestImg();
	string responseJson();
public:
	string responseJson;	
};
