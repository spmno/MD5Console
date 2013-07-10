#include "FileMaker.h"
#include <fstream>
#include <iostream>

#include "md5.h"
#define MD5_KEY_MAX_LENGTH							64
const wstring APP_PACKAGE_FILE_NAME(L"\\AppMd5.json");
const char UPDATE_METHOD[] = "UpdateMethod";
const char MD5_CONTENT[] = "MD5Content";

using namespace std;

FileMaker::FileMaker(void) : 
	appFileDirName_(L""),
	updateMethodName_(L"")
{

}


FileMaker::~FileMaker(void)
{

}

void FileMaker::findFile_(const TCHAR* dirName)  
{  
	TCHAR targetDir[MAX_PATH] = {0};
	wcscpy_s(targetDir, dirName);

	if(targetDir[wcslen(targetDir) - 1] == TEXT('\\'))  
    {  
        wcscat_s(targetDir,  TEXT("*.*"));
    }  
    else  
    {  
       wcscat_s(targetDir,  TEXT("\\*.*"));
	}
  
    WIN32_FIND_DATA fd;  
    HANDLE hdFind;  
    hdFind = FindFirstFile(targetDir,&fd);  
    if(hdFind != INVALID_HANDLE_VALUE)  
    {  
        do{  
            //At winXP system the "." means current directory, the ".."means parent directory.  
            if((fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) != 0 && fd.cFileName[0] != TEXT('.'))  
            {         
                //It is directory     
	
				{
					TCHAR nextDir[MAX_PATH] = {0};
					wcscpy_s(nextDir, dirName);  
					if(nextDir[wcslen(nextDir) -1] != TEXT('\\'))  
					{
						wcscat_s(nextDir, TEXT("\\"));
					}
					wcscat_s(nextDir, fd.cFileName);
	                
					findFile_(nextDir);  
				}

            }  
            else if(fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY && fd.cFileName[0] != TEXT('.'))  
            {     
                //It is file   
				TCHAR filePath[MAX_PATH] = {0};
				wcscpy_s(filePath, dirName);
                if(filePath[wcslen(filePath) - 1] !=TEXT( '\\'))  
				{
					wcscat_s(filePath, TEXT("\\"));
				}
				wcscat_s(filePath,fd.cFileName);
				fileContainer_.push_back(filePath);
            }  
        }while(FindNextFile(hdFind,&fd));  
    }  
    FindClose(hdFind);  
 
}  

void FileMaker::createJsonFile(TCHAR* wfileName)
{
	appFileDirName_ = wfileName;
	
	findFile_(appFileDirName_.c_str());
	Json::Value wholeValue;
	Json::Value updateMethodValue;
	Json::Value md5ListValue;
	//createUpdateMethodSection(updateMethodValue);
	
	if (createMd5Section(md5ListValue) == false) {
		return ;
	}
	Json::FastWriter fastWriter;
	wstring outputFileName(appFileDirName_);
	outputFileName += APP_PACKAGE_FILE_NAME;
	char fileName[MAX_PATH] = {0};
	WideCharToMultiByte(GetACP(), 0, outputFileName.c_str(), outputFileName.size()*2, fileName, MAX_PATH, NULL, FALSE);
	ofstream outputJson(fileName);
	if (outputJson.is_open())
	{
		char updateMethod[MAX_PATH] = {0};
		WideCharToMultiByte(GetACP(), 0, updateMethodName_.c_str(), updateMethodName_.size()*2, updateMethod, MAX_PATH, NULL, FALSE);
		wholeValue[UPDATE_METHOD] = updateMethod;
		wholeValue[MD5_CONTENT] = md5ListValue;
		string tempString = fastWriter.write(wholeValue);
		outputJson << fastWriter.write(wholeValue);
		outputJson.close();
	}
}


unsigned int FileMaker::conv_(unsigned int a)
{
	unsigned int b=0;
	b|=(a<<24)&0xff000000;
	b|=(a<<8)&0x00ff0000;
	b|=(a>>8)&0x0000ff00;
	b|=(a>>24)&0x000000ff;
	return b;
}


bool FileMaker::createMd5Section(Json::Value& md5List)
{
	int lastSignPos = appFileDirName_.rfind(L'\\');
	wstring relativeDirPrefix = appFileDirName_.substr(0, lastSignPos+1);
	for (auto fileItem : fileContainer_)
	{
		FILE * fp = NULL;
		_wfopen_s(&fp, fileItem.c_str(), L"rb");

		if (fp == NULL)
		{
			//MessageBox(NULL, L"打开文件失败", NULL, MB_OK|MB_TOPMOST);
			cout << "cannot open file" << endl;
			return false;
		}
		MD5VAL val=md5File(fp);
		char md5_result[MD5_KEY_MAX_LENGTH] = {0};
		
		size_t relativeFirstPos = fileItem.find(relativeDirPrefix);
		wstring relativeFileName = fileItem.substr(relativeFirstPos+relativeDirPrefix.size());
		sprintf_s(md5_result, "%08x%08x%08x%08x",conv_(val.a),conv_(val.b),conv_(val.c),conv_(val.d));
		char fileName[MAX_PATH] = {0};
		WideCharToMultiByte(GetACP(), 0, relativeFileName.c_str(), relativeFileName.size()*2, fileName, MAX_PATH, NULL, FALSE);
		md5List[fileName] = md5_result;
		fclose(fp);
	}

	return true;
}
