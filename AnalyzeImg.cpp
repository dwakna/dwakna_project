#include "AnalyzeImg.h"

//AnalyzeImg 생성자
extern int service_flag;
AnalyzeImg::AnalyzeImg():stopFlag_(false)
{
	dro = new Drawer();
	azTh_ = std::thread(&AnalyzeImg::proc, this);
}

//AnalyzeImg 소멸자
AnalyzeImg::~AnalyzeImg()
{	
	if(dro) delete dro;

	azCV_.notify_one();
	if(azTh_.joinable())
	{
		azTh_.join();
	}
	
	T_LOG("end azThread join\n");
}

//FileCheck 클래스를 통해 받은 파일의 경로를 queue에 push
void AnalyzeImg::setFilePath(std::string str, std::string stime)
{
	pathStr_.push(str);
	this->stime = stime;
	std::lock_guard<std::mutex> lck(azM_);
	azCV_.notify_all();
}

//thread 실행
void AnalyzeImg::proc()
{
	while (1)
	{
		{
			std::unique_lock<std::mutex> lck2(azM_);
			azCV_.wait(lck2);
		}

		if(service_flag == 0)
		{
			T_LOG("AnalyzeImg service exit\n");
			break;
		}
		
		//건네받은 파일경로가 한개도 없을 때
		if(pathStr_.size() == 0)
		{
			return;
		}
		std::string path = pathStr_.front();

		auto response = requestAzure(path);

		//이미지 분석에 성공 했을 때
		if(response != "err")
		{
			Parser parser(response);
			auto data = parser.parsing();
			dro->receiveVec(data, path, stime);	

			azM_.lock();
			pathStr_.pop();
			azM_.unlock();
		}
		else
		{
			continue;
		}
	}
}

//Azure서버에 이미지 파일을 보내서 분석을 요청
std::string AnalyzeImg::requestAzure(std::string imgPath)
{
	//이미지 분석을 위해 파일을 보낼 url
	http_client client(U("https://dwakna.cognitiveservices.azure.com/vision/v3.2/analyze?visualFeatures=Objects&language=en&model-version=latest"));
	
	//이미지 분석 요청을 위해 필요한 헤더 설정
    http_request request(methods::POST);
    request.headers().add("Content-Type", "application/octet-stream");
    request.headers().add("Host", "dwakna.cognitiveservices.azure.com");
    request.headers().add("Ocp-Apim-Subscription-Key", "11149464811c4ef4be40e5439261a1e6");

    //이미지의 버퍼를 읽어서 body에 넣어줌
    Concurrency::streams::istream imgBody = concurrency::streams::fstream::open_istream(imgPath).get();
    request.set_body(std::move(imgBody));

	T_LOG("Request to Azure\n");
	//Azure에서 온 응답 수신
    http_response response = client.request(request).get();
	
	//이미지 분석이 정상적으로 진행되지 않았을 때
    if(response.status_code() != 200)
    {
        //T_LOG("이미지 분석 요청 실패");
		return "err";
		 T_LOG("Object detection fail\n");
    }
	T_LOG("Object detection success\n");
	
	//Azure에서 받은 이미지 분석 정보 return
    return response.to_string();
}
