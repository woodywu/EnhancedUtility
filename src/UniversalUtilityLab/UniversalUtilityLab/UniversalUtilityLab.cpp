// UniversalUtilityLab.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace EnhancedUtility;

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::string> result;
	EnhancedIOStream::readAllLines("D:\\AA_v3.log", result);
	EnhancedIOStream::appendAllText("D:\\BB_v3.log", result[0]);

	return 0;
}

