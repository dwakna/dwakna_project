#include "storageIO.h"
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
	DIR* dirp = opendir(pathName.c_str());
	struct dirent *dp=NULL;

	vector<string> fileList;

	if(dirp == NULL)
	{
		//T_LOG();
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
	this->length_ = ifs.tellg();
	ifs.seekg(0, ios::beg);
	char *buf = new char[length_];
	ifs.read(buf, length_);
	ifs.close();
	//char membuf[lengthaverae];

	membuf_ = new char[length_ + 1];
	memset(membuf_,  0, sizeof(membuf_));
	memcpy(membuf_, buf, length_);
	delete []buf;
}

void StorageIO::writeImg(string name)
{
	ofstream ofs;
	int num = name.find_last_of(".");
	string realName = name.substr(0, num);
	ofs.open("/home/ict01/workplace/OJT/StorageIO/copy/" + realName  + "_update.jpg" , ios::binary);

	//ofs.open("/home/ict01/workplace/OJT/StorageIO/copy/" + name , ios::binary);
	if(ofs.fail())
	{
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
bool StorageIO::checkFile()
{
	return true;
}

bool StorageIO::checkTime()
{
	const char *path = "";
	struct stat attr;

	if(stat(path, &attr) < 0)
	{
		cout << "stat error" << endl;
		exit(0);
	}
	time_t mtime = attr.st_mtime;
	cout << "Last modified time : " << ctime(&mtime) << endl;

	return true;
}
#endif
