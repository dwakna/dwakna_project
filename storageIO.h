#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sys/types.h>
#include<dirent.h>
#include<filesystem>
#include<cstring>
#include<cerrno>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sys/types.h>
#include<dirent.h>
#include<filesystem>
#include<cstring>
#include<cerrno>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<cstdlib>
//#include "vomslog"

using namespace std;

class StorageIO
{
    char *membuf_;
    bool IsImg(string fileName);
    //bool checkTime();
public:
    vector<string> getFileList(string pathName);
    StorageIO(){}
    StorageIO(string config);
    vector<string> pathList_;
    int length_;
    void readImg(string fileName);
    void writeImg(string name);
   // bool checkFile();
};

