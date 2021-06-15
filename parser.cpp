#include "parser.h"

Parser::Parser(string objectrStr)
{
	//requestAzure에서 받은 이미지분석 string을 멤버변수로 설정
	this->objectStr_ = objectStr;
}

void Parser::parsing()
{
	//string으로 받은 좌표를 json으로 변환하는 과정 필요
	
	Json::Value root;
	Json::Value objList = root["objects"];
	Json::ValueIterator it = objList.begin();

	while(it != objList.end())
	{
		if(it->isObject())
		{
			 //객체별로 좌표 생성
            int x =  (*it)["rectangle"]["x"].asInt();
            int y = (*it)["rectangle"]["y"].asInt();
            int w = (*it)["rectangle"]["w"].asInt();
            int h = (*it)["rectangle"]["h"].asInt();
            this->objCoor_.push_back(Data(x,y,w,h));
        }
        ++it;
	}
}
