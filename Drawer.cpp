#include "Drawer.h"

extern int service_flag;

//Drawer 생성자
Drawer::Drawer()
{
	//Drawer thread
	drawerTh_ = std::thread(&Drawer::proc, this);

	std::string url = "10.10.10.142";
	std::string id = "twvsaas";
	std::string password_ = "qawsedrf12#";
	std::string dbName = "twvsaas";
	int port = 3306;

	if (!mysql_init(&db_))
	{
		T_LOG("mysql_ini fail");
		exit(1);
		return;
	}

	mysql_options(&db_, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&db_, MYSQL_INIT_COMMAND, "SET NAMES utf8");
	my_bool reconnect = true;
	mysql_options(&db_, MYSQL_OPT_RECONNECT, &reconnect);

	if (mysql_real_connect(&db_, url.c_str(), id.c_str(), password_.c_str(), dbName.c_str(), port, (char*)NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		T_LOG("mysql connect fail");
		mysql_close(&db_);
		exit(1);
		return;
	}
}

//Drawer 소멸자
Drawer::~Drawer()
{
    drawerCV_.notify_one();
	if(drawerTh_.joinable())
	{
   		drawerTh_.join();
	}
	T_LOG("end drawerTh_ join\n");
}

//처리할 이미지의 경로와 객체 좌표를 받아옴
void Drawer::receiveVec(vector<Data> coorData, string path, string stime)
{
	this->coorData_ = coorData;
	this->path_ = path;
	this->stime_ = stime;
	//처리할 이미지의 경로가 들어오면 thread에 notification을 보내줌
	drawerCV_.notify_all();
}

void Drawer::proc()
{
	while(1)
	{
		{
			std::unique_lock<std::mutex> lck3(drawerM_);
			drawerCV_.wait(lck3);
		}
		
		if(service_flag == 0)
		{
			T_LOG("Drawer service exit\n");
			break;
		}

		drawRectangle();
	}
}

//이미지에 bounding box를 그려줌
void Drawer::drawRectangle() 
{
	//이미지 읽어오기
	cv::Mat matImg;
	cv::Mat resizeImg;
	matImg = cv::imread(path_);

	//이미지 파일의 이름 파싱
	int num = path_.find_last_of("/");
    int num2 = path_.find_last_of(".");
	int num3 = path_.find_last_of("_");

	if((num == std::string::npos) || (num2 == std::string::npos) || (num3 == std::string::npos))
	{
		return;
	}
	std::string name = path_.substr(num+1, num2-num-1);
	std::string camid = path_.substr(num+1, (path_.size() - num) - (path_.size() - num3)- 1);

	T_LOG("Image Name : %s\n", name.c_str());
	//이미지 안에서 인식된 객체의 수 
	int size = coorData_.size();
	//T_LOG("The number of object : %d\n", size);

	if(size != 0)
	{
		for(int i = 0; i < size; i++)
		{
			std::cout << "Before rectangle" << std::endl;
			//바운딩 박스 그리기
			rectangle(matImg, Rect(coorData_[i].x_coor,coorData_[i].y_coor, coorData_[i].width, coorData_[i].height), Scalar(0, 0, 255), 6, 8, 0);
		}

		std::cout << "After rectangle" << std::endl;
		
		//이미지 축소
		resize(matImg, resizeImg, Size(262, 173));
		
		std::cout << "After resize" << std::endl;

		//이미지 저장
		std::string updateFullPath = "/data/EventImage/" + camid + "_update_" + stime_ + ".jpg";
		
		std::cout << "Before write" << std::endl;

		bool writeRet = cv::imwrite(updateFullPath, resizeImg);
		
		std::cout << "After write" << std::endl;
		//p
		//이미지 저장에 실패 했을 경우
		if(writeRet!=true)
		{
			T_LOG("Saving analyzed image fail\n\n");
		}
		else
		{
			T_LOG("Saving analyzed image success\n\n");
			this->sendToAim(updateFullPath, camid);
		}
	}
}

void Drawer::sendToAim(string fullPath, string camid)
{

	MYSQL_RES * resultRes;
	MYSQL_ROW row;
	std::string ruleId;
	std::string query = boost::str(boost::format("SELECT rule_id from tbl_rule where CAM_ID=%1%") % atoi(camid.c_str()));

	if (mysql_query(&db_, query.c_str()))
	{
		T_LOG("DB Query fail");
		return;
	}

	resultRes = mysql_store_result(&db_);
	int resnum = mysql_num_rows(resultRes);
	if(resnum == 0)
	{
		mysql_free_result(resultRes);
		T_LOG("result size is zero");
		return;
	}

	row = mysql_fetch_row(resultRes);
	if(row == NULL)
	{
		T_LOG("mysql fetch row fail");
	}

	ruleId = std::string(row[0]);
	int ruleid = atoi(ruleId.c_str());
	T_LOG("DB Result : %d\n", atoi(ruleId.c_str()));

    web::json::value objectBox;

    for(int i = 0; i<(int)coorData_.size(); i++)
    {
        web::json::value temp;

        temp["x"] = web::json::value::number(coorData_[i].x_coor);
        temp["y"] = web::json::value::number(coorData_[i].y_coor);
        objectBox[i] = temp;
    }

    web::json::value event;
    web::json::value temp;

    temp["evt_src"] = web::json::value::string("A");
    temp["evt_value_type"] = web::json::value::string("binary");
    temp["evt_value"] = web::json::value::string("X");
    temp["evt_id"] = web::json::value::number(0);
    temp["evt_type"] = web::json::value::number(1);
    temp["evt_status"] = web::json::value::number(1);
    temp["evt_roi_id"] = web::json::value::number(atoi(ruleId.c_str()));
    temp["object_id"] = web::json::value::number(0);
    temp["object_type"] = web::json::value::number(1);
    temp["object_box"] = objectBox;

    event[0] = temp;

    web::json::value event_info;
    event_info["cam_id"] = web::json::value::string(camid.c_str());
    event_info["svc"] = web::json::value::number(0);
    event_info["time"] = web::json::value::string(stime_);
    event_info["image_src"] = web::json::value::string(fullPath.c_str());
    event_info["event"] = event;
    
	web::json::value fullBody;
    fullBody["event_info"] = event_info;

    http_client client(U("http://10.10.10.142:7100/vsaas/v100/va_evt_result"));

    http_request request(methods::POST);
    request.headers().add("Content-Type", "application/json");
    request.headers().add("Host", "10.10.10.142:7100");

    request.set_body(fullBody);

    http_response response = client.request(request).get();
	
	std::string aimRes = response.to_string();
    T_LOG("AIM RES = %s\n", aimRes.c_str());
}
