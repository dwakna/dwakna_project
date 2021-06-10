#include "storageIO.h"
#include "voms_log.h"

int main()
{
	StorageIO sio("config.txt");
	vector<string> pathList = sio.pathList_;

	for(auto &path : pathList)
	{
		vector<string> fileList = sio.getFileList(path);
		for(int i = 0; i < fileList.size(); i++)
		{
			string finalPath = path + "/" + fileList[i];
			sio.readImg(finalPath);
			sio.writeImg(fileList[i]);
		}
	}
	return 0;
}
