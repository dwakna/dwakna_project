#include "requestAzure.h"

void requestAzure::requestImg()
{
	http_client client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/analyze?visualFeatures=Objects&language=en&model-version=latest"));

	http_request request(methods::POST);
    request.headers().add("Content-Type", "application/octet-stream");
    request.headers().add("Host", "dwakna.cognitiveservices.azure.com");
    request.headers().add("Ocp-Apim-Subscription-Key", "11149464811c4ef4be40e5439261a1e6");

	Concurrency::streams::istream imgBody =                                                                                                                                                       fstream::open_istream("/home/ict01/workplace/OJT/StorageIO/img/images.png").get();

	request.set_body(std::move(imgBody));
	http_response response = client.request(request).get();
}



void requestAzure::responseJson()
{
	http_response response;

	if(response.status_code() != 200) 
	{
			T_LOG("이미지 분석 요청 싪패");
	}
	else
	{
		responseJson = response.body().to_string();

		//객체의 좌표 정보 있는 body 부분만 자르기
		int num = responseJson.find_first_of("{");
		int num2 = responseJson.find_last_of("}");
		std::string objStr = responseJson.substr(num, num2);
	}
}
