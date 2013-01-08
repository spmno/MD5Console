#pragma once
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

class FileMaker
{
public:
	void CreateJsonFile(TCHAR* fileName);
	FileMaker(void);
	~FileMaker(void);
private:
	unsigned int conv_(unsigned int a);
	void FindFile_(const TCHAR* dirName);  
	vector<wstring> fileContainer_;
	wstring appFileDirName_;
};

