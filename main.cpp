#include "storageIO.h"
#include "requestAzure.h"
#include "drawer.h"

#include "voms_log.h"

int main()
{
	//T_LOG_INIT("VH");
	std::string procName = "VH";
	std::string logPath = "/home/ict01/log/";
	voms_log_init((char*) procName.c_str(), (char*)logPath.c_str(), E_VOMS_LOG_UNIT_HOUR);
	T_LOG("VH Process Start");
	StorageIO sio("config.txt");
	vector<string> pathList = sio.pathList_;

	for(auto &path : pathList)
	{
		vector<string> fileList = sio.getFileList(path);
		for(int i = 0; i < fileList.size(); i++)
		{
			string finalPath = path + "/" + fileList[i];
			sio.readImg(finalPath);
			//requestToAzure
			//parsing
			//drawBoundingBox
			sio.writeImg(fileList[i]);
		}
	}
	return 0;
}
