#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri_builder.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

int main()
{
    auto fileStream = std::make_shared<ostream>();

    pplx::task<void> requestTask = fstream::open_ostream(U("/home/ict01/workplace/OJT/StorageIO/img/images.png")).then([=](ostream outFile)
            {
            *fileStream = outFile;

            http_client_config conf;
            conf.set_timeout(seconds(5));
			
            //http_client client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/detect?model-version=latest"));
            http_client client(U("https://dwakna.cognitiveservices.azure.com/"));
			//http_client client(U("https://jayasou.cognitiveservices.azure.com/vision/v3.2/analyze?visualFeatures=Objects&language=en&model-version=latest"));
			//uri_builder builder(U("/search"));
			//uri_builder builder(U("https://dwakna.cognitiveservices.azure.com/"));
            //builder.append_path(U("/vision"));
			
			uri_builder builder(U("/vision"));
			builder.append_path(U("v3.2"));
			builder.append_path(U("detect"));
			//builder.append_query(U("visualFeatures"), U("Objects"));
			//builder.append_query(U("language"), U("en"));
			builder.append_query(U("model-version"), U("latest"));
			
			http_request request(methods::POST);
			
			//request.headers().add("Content-Type", "multipart/form-data");
			
			request.headers().add("Content-Type", "application/octet-stream");
    		request.headers().add("Host", "dwakna.cognitiveservices.azure.com");
    		request.headers().add("Ocp-Apim-Subscription-Key", "11149464811c4ef4be40e5439261a1e6");
			
			if(fileStream == NULL) std::cout << "error" << std::endl;
            //request.body().read_to_end(fileStream->streambuf()).wait();
			//request.set_body(fileStream);
			Concurrency::streams::istream imgBody = fstream::open_istream("/home/ict01/workplace/OJT/StorageIO/img/images.png").get();
			
			//std::cout << request.extract_string() << std::endl;
			std::cout << builder.to_string() << std::endl;
			//string_t str = request.extract_string().get();
			//std::wcout << str.c_str() << std::endl;
			//return client.request(methods::POST, builder.to_string(), imgBody, U("application/octet-stream"));
			return client.request(methods::POST, U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/detect?model-version=latest"), imgBody, U("application/octet-stream"));
			//return client.request(request);
            }).then([=](http_response response)
                {
                printf("Receive response status code:%u\n", response.status_code());
				std::string body = response.to_string();
				std::cout << body << std::endl;
                return response.body().read_to_end(fileStream->streambuf());
                }).then([=](size_t nVal)
                    {
                    printf("Size is %u\n", nVal);
					//std::string body = response.to_string();

                    return fileStream->close();
                    });
                try
                {
                    requestTask.wait();
                }
                catch (const std::exception &e)
                {
                    printf("Error exception:%s\n", e.what());
                }

                return 0;
}
