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

using namespace std;

int main()
{
	const char *path = "/home/ict01/workplace/OJT/StorageIO/img/img1.jpg";
	const char *path2 = "/home/ict01/workplace/OJT/StorageIO/img/img2.jpg";
    struct stat attr;

    if(stat(path, &attr) < 0)
    {
        cout << "stat error" << endl;
        exit(0);
    }
    time_t mtime = attr.st_mtime;

	if(stat(path2, &attr) < 0)
    {
        cout << "stat error" << endl;
        exit(0);
    }
    time_t mtime2 = attr.st_mtime;
    cout << "img1 Last modified time : " << ctime(&mtime) << endl;
	cout << "img2 Last modified time : " << ctime(&mtime2) << endl;

	double diff = difftime(mtime2, mtime);
	cout << diff << endl;
    return true;
}
