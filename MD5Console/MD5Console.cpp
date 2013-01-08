// MD5Console.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "FileMaker.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		cout << "param error!" << endl;
		cout << "right style: MD5Console DirName" << endl;
		return -1;
	}

	FileMaker fileMake;
	fileMake.CreateJsonFile(argv[1]);
	return 0;
}

