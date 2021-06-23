#include "Parser.h"

//AnalyzeImg에서 받은 이미지 분석 string을 멤버변수로 설정
Parser::Parser(string objectStr)
{
	this->objectStr_ = objectStr;
}

//건네받은 문자열에서 객체의 좌표를 파싱
vector<Data> Parser::parsing()
{
	//이미지 안에서 인식된 객체 좌표를 담을 vector
	vector<Data> objCoor;
	vector<Data>().swap(objCoor);

	//std::cout << objectStr_ << std::endl;
	//객체의 좌표 정보 있는 body 부분만 자르기
    int num = objectStr_.find_first_of("{");
	//인식된 객체가 없을 경우
	if(num == std::string::npos)
	{
		//비어있는 vector 반환
		return objCoor;
	}
    std::string objStr = objectStr_.substr(num);

	//parsing을 위한 객체와 포인터 선언
    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::CharReader *reader(builder.newCharReader());

    //json parsing
    bool parsingSuccessful = reader->parse(objStr.c_str(), objStr.c_str()+objStr.length(), &root, nullptr);

	//응답으로 받은 json에서 object 배열을 가져옴
	Json::Value objList = root["objects"];
	Json::ValueIterator it = objList.begin();
	
	while(it != objList.end())
	{
		//객체별로 좌표 생성
		if(it->isObject())
		{
            int x =  (*it)["rectangle"]["x"].asInt();
            int y = (*it)["rectangle"]["y"].asInt();
            int w = (*it)["rectangle"]["w"].asInt();
            int h = (*it)["rectangle"]["h"].asInt();
			
			std::string objName =(*it)["object"].asCString();
			
			T_LOG("Object : %s\n", objName.c_str());	
			
			if(objName != "person")
			{
				++it;
				continue;
			}
			T_LOG("Detect person\n");
			objCoor.push_back(Data(x,y,w,h));
        }
        ++it;
	}
	delete reader;
	
	//객체의 좌표정보를 담은 vector 반환
	return objCoor;
}
