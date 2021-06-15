#include "Drawer.h"

Drawer::Drawer()
{
	//인식된 객체가 없을 때 오류처리하기
}

Drawer::Drawer(vector<Data> &vec)
{
	//인식된 객체의 좌표들 벡터 설정
	vec_=vec;
}

void drawRectangle(char* buffer, int length)
{
	//buffer로 받은 이미지를 mat 형식으로 변환
	Mat matImg;
	matImg = cv::imdecode(cv::Mat(1, bufferLength, CV_8UC1, buffer), -1);

	//객체 수만큼
	for(int i = 0; i < vec.size(); i++)
	{
		//바운딩 박스 그려주기
		rectangle(matImg, Rect(vec[i].x_coor,vec[i].y_coor, vec[i].width, vec[i].height), Scalar(0, 0, 255), 5, 8, 0);
	}
}
