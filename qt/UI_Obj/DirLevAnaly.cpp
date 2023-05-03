#include <regex>
#include "DirLevAnaly.h"

DirLevAnaly::DirLevAnaly(string inputStr)
{
	this->dirInvild = GetDirNum(inputStr);
}	

int DirLevAnaly::GetDirLev(void)
{
	int countCh = 0;

	if (this->dirInvild == false)
	{
		return 0;
	}

	for (int i = 0; i < this->strDir.size(); i++)
	{
		if (this->strDir[i] == '.')
		{
			countCh++;
		}
	}
	return countCh;
}



bool DirLevAnaly::GetStartIsNum(string sourceStr)
{
	const char chStr[] = { '1', '2','3','4', '5', '6', '7', '8', '9' };

	for (int i = 0; i < sizeof(chStr); i++)
	{
		if (sourceStr[0] == chStr[i] && sourceStr[1] == '.')
		{
			return true;
		}
	}
	return false;
};

bool DirLevAnaly::GetDirNum(string str)
{
	if (true == GetStartIsNum(str))
	{
		bool ret = false;
		const char* first = str.c_str();
		const char* last = first + strlen(first);

		std::cmatch mr;
		std::regex rx("(\\d{0,9}\\.){1,9}");
		ret = regex_search(first, last, mr, rx);
		if (ret)
		{
			strDir = mr.str();
		}
		return ret;
	}
	return false;
}
