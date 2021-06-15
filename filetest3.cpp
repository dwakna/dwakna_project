#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <string.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

int main()
{

    http_client client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/analyze?visualFeatures=Objects&language=en&model-version=latest"));

#if 0
    uri_builder builder(U("/vision"));
    builder.append_path(U("v3.2"));
    builder.append_path(U("analyze"));
    builder.append_query(U("visualFeatures"), U("Objects"));
    builder.append_query(U("language"), U("en"));
    builder.append_query(U("model-version"), U("latest"));
#endif

    http_request request(methods::POST);
    request.headers().add("Content-Type", "application/octet-stream");
    request.headers().add("Host", "dwakna.cognitiveservices.azure.com");
    request.headers().add("Ocp-Apim-Subscription-Key", "11149464811c4ef4be40e5439261a1e6");

#if 1
	//std::string str = "/home/ict01/workplace/OJT/StorageIO/img/images.png";
	//auto tmp = utility::conversions::to_string_t(str);
    Concurrency::streams::istream imgBody =
        fstream::open_istream("/home/ict01/workplace/OJT/StorageIO/img/images.png").get();
	
	//auto stream = fstream::open_istream(U("/home/ict01/workplace/OJT/StorageIO/img/images.png")).get();
	//request.body().read_to_end(stream.streambuf()).wait();
	//stream.close().get();
	/*std::ifstream ifs;
	ifs.open("/home/ict01/workplace/OJT/StorageIO/img/images.png", std::ios::binary);
	ifs.seekg(0, std::ios::end);
	int length = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    char *buf = new char[length];
    ifs.read(buf, length);
    ifs.close();
	*/
#if 0
    imgBody.seekg (0, ios::end);
    auto length = imgBody.tellg();
    imgBody.seekg (0, ios::beg);
#endif
    request.set_body(std::move(imgBody));
	//stream.close().get();	
	//delete []buf;
    std::cout << request.to_string() << "\n";
#endif
    http_response response = client.request(request).get();
    std::cout << response.status_code() << "\n";
    std::cout << response.to_string() << "\n";

    return 0;
}
