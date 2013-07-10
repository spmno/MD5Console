// MD5Console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "FileMaker.h"

using namespace std;
const wstring SETTING_FILE_UPDATE_METHOD(L"SETTING");
const wstring COMPARE_FILE_UPDATE_METHOD(L"COMPARE");
const wstring ALL_REPLACE_UPDATE_METHOD(L"ALL");

int _tmain(int argc, _TCHAR* argv[])
{
	FileMaker fileMake;
	wstring updateMethod;
	if (argc == 2) {
		updateMethod = L"ALL";
		fileMake.setUpdateMethodName(updateMethod);
		cout << "Use default UpdateMethod=ALL" << endl;
	} else if (argc == 3) {
		if ((SETTING_FILE_UPDATE_METHOD == argv[2]) || (COMPARE_FILE_UPDATE_METHOD == argv[2]) || (ALL_REPLACE_UPDATE_METHOD == argv[2])) {
			updateMethod = argv[2];
			fileMake.setUpdateMethodName(updateMethod);
		} else {
			cout << "update method param error!" << endl;
			return -1;
		}
		
	} else {
		cout << "param error!" << endl;
		cout << "right style: 'MD5Console DirName' or 'MD5Console DirName UpdateMethod' "<< endl;
		cout << "Method : ALL SETTING COMPARE" << endl;
		return -1;
	}

	
	fileMake.createJsonFile(argv[1]);
	return 0;
}

