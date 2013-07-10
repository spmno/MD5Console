#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "jsoncpp\json\json.h"
using namespace std;

class FileMaker
{
public:
	void createJsonFile(TCHAR* fileName);
	FileMaker(void);
	~FileMaker(void);
	void setUpdateMethodName(wstring& name)
	{
		updateMethodName_ = name;
	}
private:
	unsigned int conv_(unsigned int a);
	void findFile_(const TCHAR* dirName);  
	bool createMd5Section(Json::Value& jsonValue);
	//bool createUpdateMethodSection(Json::Value& jsonValue);
	vector<wstring> fileContainer_;
	wstring appFileDirName_;
	wstring updateMethodName_;
};

