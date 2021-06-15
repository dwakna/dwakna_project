#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <string>
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>


using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace json;
using namespace concurrency::streams;

/*
struct coorData
{
	int x_coor, y_coor, width, height;
	coorData(int x, y, w, h)
	{
		x_coor = x;
		y_coor = y;
		width = w;
		height = h;
	}
};
*/
int main()
{

	http_client client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/detect?model-version=latest"));

	http_request request(methods::POST);

	request.headers().add("Content-Type", "application/json");
	request.headers().add("Host", "dwakna.cognitiveservices.azure.com");
	request.headers().add("Ocp-Apim-Subscription-Key", "d98268d6e46a43f49bdf5a96b3050cf5");
	//request.set_body("url", "http://img.vogue.co.kr/vogue/2019/11/style_5dd79199b1aa6-1200x832.png");
	//request.set_body("url = http://img.vogue.co.kr/vogue/2019/11/style_5dd79199b1aa6-1200x832.png");
	value postData;
	//postData["file"] = json::value::string("/home/ict01/workplace/OJT/StorageIO/img/copy0/jpg");
	postData["url"] = value::string(U("http://img.vogue.co.kr/vogue/2019/11/style_5dd79199b1aa6-1200x832.png"));
	request.set_body(postData.serialize());
	
	//file_stream<unsighned char>::open_istream(L"/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg");
	//client.request(methods::POST, L"myfile", filestream);
	http_response response = client.request(request).get();
	//if(response.status_code() == status_coeds::OK) std::cout << "ok" << std::endl;
	std::cout << response.status_code() << std::endl;
	//fileStream.close();
	std::string responseBody = response.to_string();
	
	int num = responseBody.find_first_of("{");
	int num2 = responseBody.find_last_of("}");
	std::string body = responseBody.substr(num, num2); // json 부분만 자름

	std::cout << body << std::endl;


	//std::ofstream stream;
	//stream.open("test2.json");
	//stream << body;
	
	//std::ifstream stream2;
	//stream2.open("test.json");

	Json::Value root;
#if 0
	Json::Reader reader;
	reader.parse(body, root);
#else
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	std::string errors;
	bool parsingSuccessful = reader->parse((const char*)body.c_str(), (const char*)body.c_str()+body.size(), &root, &errors);
	//stream2 >> root;
	delete reader;
#endif
	//Json::Value root;
	Json::Value olist = root["objects"];
	Json::ValueIterator it = olist.begin();

	//std::vector<coorData> object;

	while(it != olist.end())
	{
		if(it->isObject())
		{
			//객체별로 좌표 생성
			int x =  (*it)["rectangle"]["x"].asInt();
			int y = (*it)["rectangle"]["y"].asInt();
			int w = (*it)["rectangle"]["w"].asInt();
			int h = (*it)["rectangle"]["h"].asInt();
			std::cout << x << std::endl;
		}
		++it;
	}
#if 0
	Json::CharReaderBuilder builder;
	Json::CharReader *reader(builder.newCharReader());


	Json::Value root;
	std::string  str;
	
	char const* begin = body.data();
	char const* end = begin + body.size();
	std::cout << "d" << std::endl;
	bool parsingSuccessful = reader->parse(begin, end, &root, &str);
	
	if(!parsingSuccessful)
	{
		std::cout << "실패" << std::endl;
	}
	else
	{
		std::cout << "성공" << std::endl;
	}
	delete reader;
#endif
	return 0;
}
