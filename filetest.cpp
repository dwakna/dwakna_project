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
#if 1
	http_client client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/detect?model-version=latest"));
	
	auto fileStream = std::make_shared<Concurrency::streams::ostream>();
	std::string tmp2 = "/home/ict01/workplace/OJT/StorageIO/img/img1.jpg";
	//utility::string_t tstring;
	//tstring.assign(tmp.begin(), tmp.end());
	auto tmp = utility::conversions::to_string_t(tmp2);
	http_request request(methods::POST);

    request.headers().add("Content-Type", "multipart/form-data");
    request.headers().add("Host", "dwakna.cognitiveservices.azure.com");
    request.headers().add("Ocp-Apim-Subscription-Key", "d98268d6e46a43f49bdf5a96b3050cf5");
	*fileStream = Concurrency::streams::fstream::open_ostream(tmp).get();
	request.body().read_to_end(fileStream->streambuf()).wait();
	//client.request(methods::POST, "/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg", fileStream);
	fileStream->close();

	/*
	std::ifstream ifs;
    ifs.open("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg", std::ios::binary);
    ifs.seekg(0, std::ios::end);
    int length_ = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    char *buf = new char[length_];http_request request(methods::POST);
    ifs.read(buf, length_);
    ifs.close();
	*/

	//*fileStream = Concurrency::streams::fstream::open_ostream(tmp).get();
	//request.body().read_to_end(fileStream->streambuf()).wait();
	//std::string filepath = "/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg";
	//concurrency::streams::istream input_stream = concurrency::streams::file_stream<uint8_t>::open_istream(U(filepath)).get();
	//auto fileStream = fstream::open_ostream(utility::conversions::to_string_t("/home/ict01/workplace/OJT/StorageIO/img/copy0.jpg"), std::ios::out | std::ios::binary).get();
	//auto fileStream = std::make_shared<Concurrency::streams::ostream> ();
   
	http_response response = client.request(request).get();
    //if(response.status_code() == status_coeds::OK) std::cout << "ok" << std::endl;
    std::cout << response.status_code() << std::endl;
    //fileStream.close();
#endif
#if 0
    std::string responseBody = response.to_string();

    int num = responseBody.find_first_of("{");
    int num2 = responseBody.find_last_of("}");
    std::string body = responseBody.substr(num, num2); // json 부분만 자름

    "https://dwakna.cognitiveservices.azure.com/vision/v3.2/detect?model-version=latestContent-TyperContent-Typemultipart/form-dataHosdwakna.cognitiveservices.azure.comOcp-Apim-Subscription-Keyd98268d6e46a43f49bdf5a96b3050cf5std::cout << body << std::endl;
#endif
	return 0;
}
