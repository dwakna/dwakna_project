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
            fileList.push_back(dp->d_name);
        }
    }
    closedir(dirp);
    return fileList;
}

void StorageIO::readImg(string fileName)
{
    ifstream ifs;
    cout << fileName << endl;
    ifs.open(fileName, ios::binary);
    ifs.seekg(0, ios::end);
    length_ = ifs.tellg();
    ifs.seekg(0, ios::beg);
    char *buf = new char[length_];
    ifs.read(buf, length_);
    ifs.close();
    //char membuf[lengthaverage];
    memset(membuf_, 0, sizeof(membuf_));
    memcpy(membuf_, buf, sizeof(buf));
    delete []buf;
}

void StorageIO::writeImg(string name)
{
    ofstream ofs;
    int num = name.find_last_of(".");
    string realName = name.substr(0, num);
    ofs.open("/home/ict01/workplace/OJT/StorageIO/copy/" + realName  + "_update.jpg" , ios::binary);
    //ofs.write(buf, length);
"storageIO.cpp" 105L, 1797C                                                                                                         79,2-5        38%

    while((dp=readdir(dirp)) != NULL)
    {
        string fileName = dp->d_name;
        if(IsImg(fileName)==true)
        {
            fileList.push_back(dp->d_name);
        }
    }
    closedir(dirp);
    return fileList;
}

void StorageIO::readImg(string fileName)
{
    ifstream ifs;
    cout << fileName << endl;
    ifs.open(fileName, ios::binary);
    ifs.seekg(0, ios::end);
    length_ = ifs.tellg();
    ifs.seekg(0, ios::beg);
    char *buf = new char[length_];
    ifs.read(buf, length_);
    ifs.close();
    //char membuf[lengthaverage];
    memset(membuf_, 0, sizeof(membuf_));
    memcpy(membuf_, buf, sizeof(buf));
    delete []buf;
}

void StorageIO::writeImg(string name)
{
    ofstream ofs;
    int num = name.find_last_of(".");
    string realName = name.substr(0, num);
    ofs.open("/home/ict01/workplace/OJT/StorageIO/copy/" + realName  + "_update.jpg" , ios::binary);
    //ofs.write(buf, length);
    ofs.write(membuf_[0], length_);
    ofs.close();
}

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
    }
}
