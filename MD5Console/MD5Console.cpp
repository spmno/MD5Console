// MD5Console.cpp : �������̨Ӧ�ó������ڵ㡣
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

