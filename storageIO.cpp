#include "storageIO.h"

StorageIO::StorageIO()
{
	T_LOG("설정파일 없음");
}

StorageIO::StorageIO(string config)
{
	ifstream fin;
	fin.open(config);
	string line;
	
	//while(!fin.eof())
	while(fin.peek() != EOF)
	{
		getline(fin, line);
		pathList_.push_back(line);
	}
	fin.close();
}

bool StorageIO::IsImg(string fileName)
{
	//폴더의 파일 중에서 jpg 형식인것만 확인	
	string ext = fileName.substr(fileName.find_last_of(".") + 1);
	if(ext == "jpg")
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<string> StorageIO::getFileList(string pathName)
{
	//폴더에 있는 모든 파일의 이름 가져오기
	
	DIR* dirp = opendir(pathName.c_str());
	struct dirent *dp=NULL;

	vector<string> fileList;

	if(dirp == NULL)
	{
		T_LOG("폴더 내에 파일이 없습니다.");
		return fileList;
	}
	while((dp=readdir(dirp)) != NULL)
	{
		string fileName = dp->d_name;
		if(IsImg(fileName)==true)
		{
			fileList.push_back(fileName);
		}
	}
	closedir(dirp);
	return fileList;
}

void StorageIO::readImg(string fileName)
{
	ifstream ifs;
	ifs.open(fileName, ios::binary);
	ifs.seekg(0, ios::end);
	int length = ifs.tellg();
	ifs.seekg(0, ios::beg);
	char *buf = new char[length];
	ifs.read(buf, length);
	ifs.close();
	//char membuf[lengthaverae];

	membuf_ = new char[length + 1];
	memset(membuf_,  0, sizeof(membuf_));
	memcpy(membuf_, buf, length);
	delete []buf;
}

void StorageIO::writeImg(string name)
{
	ofstream ofs;
	//가져온 파일 이름에서 확장자 잘라내기
	int num = name.find_last_of(".");
	string realName = name.substr(0, num);
	ofs.open("/home/ict01/workplace/OJT/StorageIO/copy/" + realName  + "_update.jpg" , ios::binary);

	if(ofs.fail())
	{
		T_LOG("파일 저장 실패");
		cerr << "Error : " << strerror(errno)<<endl;
	}

	ofs.write(membuf_, length_);
	ofs.close();

	if(membuf_)
	{
		delete []membuf_;
		membuf_ = nullptr;
	}
}

# if 0

//storage에 생성된 마지막 파일과 이미지 분석 처리 후 저장한 사진파일의 시간이 3초 이상 차이가 나는지 확인
bool StorageIO::checkTimeci(const char *path1, const char *path2)
{
	struct stat attr;

	if(stat(path1, &attr) < 0)
	{
		cout << "stat error" << endl;
		exit(0);
	}
	time_t mtime1 = attr.st_mtime;

	if(stat(path2, &attr) < 0)
    {
        cout << "stat error" << endl;
        exit(0);
    }
    time_t mtime2 = attr.st_mtime;

	double diff = difftime(mtime2, mtime1);
	
	if(diff >= 3) return true;
	else return false;
}
#endif
