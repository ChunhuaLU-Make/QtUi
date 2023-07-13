#include <iostream>
#include <string>


using namespace std;

class DirLevAnaly
{
public:
	DirLevAnaly(string inputStr);

	int GetDirLev(void);

private:
	string strDir;
	bool dirInvild;

	bool GetStartIsNum(string sourceStr);

	bool GetDirNum(string str);

};
