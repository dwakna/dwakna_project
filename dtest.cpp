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
#include <fstream>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace json;
using namespace concurrency::streams;

int main()
{
//	http_client client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/detect?model-version=latest"));
	/*	
	std::ifstream ifs;
    ifs.open("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg", std::ios::binary);
    ifs.seekg(0, std::ios::end);
    int length_ = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    char *buf = new char[length_];
    ifs.read(buf, length_);
 	*/
	/*
    http_request request(methods::POST);
   
	request.headers().add("Content-Type", "multipart/form-data");
	request.headers().add("Host", "dwakna.cognitiveservices.azure.com");
	request.headers().add("Ocp-Apim-Subscription-Key", "d98268d6e46a43f49bdf5a96b3050cf5");
	*/
	//uri_builder builder = uri_builder(U("api")).append_query(U("Content-Type"), U("multipart/form-data")).append_query(U("Ocp-Apim-Subscription-Key"), U("d98268d6e46a43f49bdf5a96b3050cf5"));
	
	//auto fileStream = fstream::open_ostream(utility::conversions::to_string_t("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg"), std::ios::out | std::ios::binary).get();
	//auto fileStream = std::make_shared<Concurrency::streams::ostream>();
	//*fileStream = Concurrency::streams::fstream::open_ostream("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg").get();
	
	//std::wstring filePath = L"/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg";
	//client.request(methods::POST, L"filePath", *buf);
	//auto fileStream = std::make_shared<Concurrency::streams::ostream>();
	//utility::string_t tmp = L"/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg";
	
	//ifs.close();

	auto httpClient = http_client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/detect?model-version=latest"));
	
	uri_builder builder(U("/search"));
	builder.append_query(U("Content-Type"), U("multipart/form-data"));
	builder.append_query(U("Host"), U("dwakna.cognitiveservices.azure.com"));
	builder.append_query(U("Ocp-Apim-Subscription-Key"), U("d98268d6e46a43f49bdf5a96b3050cf5"));
	Concurrency::streams::istream imgBody = fstream::open_istream("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg").get();
	auto result = httpClient.request(methods::POST, builder.to_string(), imgBody, U("multipart/form-data"));

	http_response response;
	std::cout << response.status_code() << std::endl;
	//std::cout << result << std::endl;
	//*fileStream = Concurrency::streams::fstream::open_ostream(tmp).get();
	//request.body().read_to_end(fileStream->streambuf()).wait();
	//std::string filepath = "/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg";
	//concurrency::streams::istream input_stream = concurrency::streams::file_stream<uint8_t>::open_istream(U(filepath)).get();
	//auto fileStream = fstream::open_ostream(utility::conversions::to_string_t("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg"), std::ios::out | std::ios::binary).get();
	//auto fileStream = std::make_shared<Concurrency::streams::ostream> ();
	//string_t tmp = L"/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg";
    // Get body from request
	//*fileStream = Concurrency::streams::fstream::open_ostream("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg").get();
	//request.body().read_to_end(fileStream->streambuf()).wait();
	//fileStream.close();
    //auto bodyStream = request.body();

    // Write input from request body directly to output filestream
    //bodyStream.read_to_end(buf.streambuf()).wait();
   // fileStream.close().wait();

	//std::cout << result << std::endl;
	//http_response response = httpClient.request(request).get();
    //if(response.status_code() == status_coeds::OK) std::cout << "ok" << std::endl;
    //std::cout << response.status_code() << std::endl;
    //fileStream.close();
#if 0
    std::string responseBody = response.to_string();

    int num = responseBody.find_first_of("{");
    int num2 = responseBody.find_last_of("}");
    std::string body = responseBody.substr(num, num2); // json 부분만 자름

    std::cout << body << std::endl;
#endif
	return 0;
}
