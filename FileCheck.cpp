#include "FileCheck.h"
mutex lockProcessExit;
condition_variable cvProcessExit;

static int received_signal = -1;
static void s_exit_handler(int signo);

int service_flag = 1;

int main()
{
	T_LOG_INIT("ODT");
	
	/* signal handling */
	try
	{
		signal(SIGINT, s_exit_handler);
		signal(SIGTERM, s_exit_handler);
		signal(SIGQUIT, s_exit_handler);

		FileCheck *fc = new FileCheck();
		fc->run();

		if(fc) delete fc;
	}
	catch(...)
	{
		exit(1);
	}

	return 0;
}

//FileCheck 생성자
FileCheck::FileCheck()
{
	//처리할 폴더명이 들어있는 vec 비우기
	std::vector<std::string>().swap(pathList_);

	//config 파일 읽어오기
	std::ifstream ifs;
	ifs.open("/home/ict01/workplace/OJT/StorageIO/dwakna_project/config.txt");
	std::string line;
	
	while(ifs.peek() != EOF)
	{	
		getline(ifs, line);
		pathList_.push_back(line);
	}
	ifs.close();

	//이미지 분석을 처리할 폴더가 있을 경우
	if(pathList_.size() != 0)
	{
		azo = new AnalyzeImg();
		FileCheck::init();
	}
}

//FileCheck 소멸자
FileCheck::~FileCheck()
{
	if(fileTh_.joinable())
	{
		fileTh_.join();
	}

	T_LOG("end fileTh_ join\n");
	if(azo)
	{
		delete azo;
		azo = nullptr;
	}
}

void FileCheck::run()
{
	unique_lock<mutex> lock(lockProcessExit);
	cvProcessExit.wait(lock);
	fileCV_.notify_all();
}

void FileCheck::init()
{
	fileTh_ = std::thread(&FileCheck::proc, this);
}

//FileCheck thread 실행
void FileCheck::proc()
{
	while (1)
	{
		{
			std::unique_lock<std::mutex> lck(fileM_);
			fileCV_.wait_for(lck, std::chrono::seconds(1));
		}

		if(service_flag == 0)
		{
			T_LOG("FileCheck service exit\n");
			break;
		}

		for(int i = 0; i < pathList_.size(); i++)
		{
			//처리할 폴더 경로를 하나씩 넘겨줌
			FileCheck::getFileList(pathList_[i]);
		}
	}
}

//처리할 폴더에 존재하는 모든 파일 경로를 읽어옴
void FileCheck::getFileList(std::string folderName)
{
	DIR* dirp = opendir(folderName.c_str());
	struct dirent *dp = NULL;

	if(dirp != NULL)
	{
		while((dp=readdir(dirp)) != NULL)
		{
			//파일의 이름을 하나씩 가져와서 처리
			std::string fileName = dp->d_name;
			std::string filePath = folderName + "/" + fileName;
			if((IsImg(fileName) == true)&&(IsOrg(fileName) == true)&&(checkTime(filePath) == true))
			{
				//AnalyzeImg에 분석할 이미지의 경로를 보냄
				azo->setFilePath(filePath, stime);
			}
		}
	}
	//폴더에 파일이 존재하지 않을 때
	else
	{
		T_LOG("분석할 이미지가 없습니다.\n");
		return;
	}
	closedir(dirp);
}

//org 파일인지 판별
bool FileCheck::IsOrg(std::string fileName)
{
	if(fileName.find("org") != std::string::npos) return true;
	else return false;
}

//폴더에서 읽어온 파일이 이미지 파일인지 판별
bool FileCheck::IsImg(std::string fileName)
{
    if(fileName.find("jpg") != std::string::npos) return true;
	else return false;
}

//새로 생성된 썸네일인지 판별
bool FileCheck::checkTime(std::string filePath)
{
	//처리된 이미지가 저장되는 폴더
	std::string updateFolder = "/data/EventImage/";
	std::string lastFile;
    DIR* dirp = opendir(updateFolder.c_str());
    struct dirent *dp = NULL;

    if(dirp != NULL)
    {
        while((dp=readdir(dirp)) != NULL)
        {
			//마지막으로 처리된 이미지 파일의 이름을 가져옴
            lastFile = dp->d_name;
        }
		std::string updateFilePath = updateFolder + "/" + lastFile;
        struct stat attr;

        stat(updateFilePath.c_str(), &attr);
        time_t mtime1 = attr.st_mtime;
        stat(filePath.c_str(), &attr);
        time_t mtime2 = attr.st_mtime;
		
		struct tm* pTimeInfo;
        pTimeInfo = localtime(&mtime1);

        int year = pTimeInfo->tm_year + 1900;
        int month = pTimeInfo->tm_mon + 1;
        int day = pTimeInfo->tm_mday;
        int hour = pTimeInfo->tm_hour;
        int min = pTimeInfo->tm_min;
        int sec = pTimeInfo->tm_sec;

		std::string syear = to_string(year);
		std::string smonth, sday, shour, smin, ssec;

        if(month < 10) smonth = "0" + to_string(month);
		else smonth = to_string(month);
		if(day < 10) sday = "0" + to_string(day);
		else sday = to_string(day);
		if(hour < 10) shour = "0" + to_string(hour);
		else shour = to_string(hour);
		if(min < 10) smin = "0" + to_string(min);
		else smin = to_string(min);
		if(sec < 10) ssec = "0" + to_string(sec);
		else ssec = to_string(sec);

        this->stime = syear+smonth+sday+shour+smin+ssec;

		//마지막으로 처리된 사진과 이제 처리할 사진의 저장 시간이 3초이상 차이나면 true 반환
        double diff = difftime(mtime2, mtime1);

        if(diff >= 2) return true;
        else return false;
    }
    else
    {
		//이전에 처리된 사진이 없으면(프로그램이 처음 돌아간 것이면) true 반환
        return true;
    }
}

static void s_exit_handler(int signo)
{
	service_flag = 0;
	cvProcessExit.notify_all();
	T_LOG("signo : %d\n", signo);

	return;
}
