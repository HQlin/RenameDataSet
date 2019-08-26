// RenameDataSet.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <windows.h>
#include <vector>
#include <sstream>

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

int renameDataSet(char *format, char *preName)
{
	_chdir("dataSet/");
	WIN32_FIND_DATA data;
	HANDLE h;

	std::stringstream ss;
	ss << "*" << format;
	h = FindFirstFile(stringToLPCWSTR(ss.str()), &data);

	int count = 1;

	std::vector<std::string> list;

	if (h != INVALID_HANDLE_VALUE)
	{
		int numOfFiles = 0;

		do
		{
			char*  nPtr = new char[lstrlen(data.cFileName) + 1];

			for (int i = 0; i < lstrlen(data.cFileName); i++)
				nPtr[i] = char(data.cFileName[i]);

			nPtr[lstrlen(data.cFileName)] = '\0';

			list.push_back(nPtr);

		} while (FindNextFile(h, &data));

		for (int i = 0; i<list.size(); i++)
		{
			std::stringstream path1, path2;
			path1 << list[i];

			path2 << preName;

			if (count < 10)
				path2 << '0';

			path2 << count << format;

			(char *)data.cFileName;

			bool a = rename(path1.str().c_str(), path2.str().c_str());

			std::cout << path1.str().c_str() << " to " << path2.str().c_str() << "\n";

			count++;

		}
		while (FindNextFile(h, &data) && count <= numOfFiles);
	}
	else
		std::cout << "Error: No such folder." << std::endl;

	FindClose(h);

	return 0;
}

int main(int argc, char** argv)
{
	//�������RenameDataSet.exe .txt book
	//�ļ�����ʽ��book01.jpg
	//argc = 3;
	//argv[1] = ".jpg";//�ļ���չ��
	//argv[2] = "book";//�ļ���ǰ׺

	renameDataSet(argv[1], argv[2]);
	return 0;
}



