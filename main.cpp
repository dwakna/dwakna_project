#include "storageIO.h"

int main()
{
    StorageIO sio("config.txt");
    vector<string> pathList = sio.pathList_;


    for(auto &path : pathList)
    {


        vector<string> fileList = sio.getFileList(path);
#if 1
        for(int i = 0; i < fileList.size(); i++)
        {
            string finalPath = path + "/" + fileList[i];
            sio.readImg(finalPath);
            sio.writeImg(fileList[i]);
        }
#endif
    }


    return 0;
}
