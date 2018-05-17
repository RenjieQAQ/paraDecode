#include <iostream>
#include <string>
using namespace std;
#include <stdio.h>
#include "optDecode.h"


myopt optFix[] = {
	{ "-a",myopt_PARA ,myopt_NUM },
	{ "-B",myopt_PARA ,myopt_STR },
	{ "-x",myopt_NOPARA ,myopt_STR },
	{0}
};
myopt optIR[] = {
	{ "-s",myopt_PARA ,myopt_NUM },
	{ "-a",myopt_PARA ,myopt_STR },
	{ "-c",myopt_NOPARA ,myopt_STR },
	{ 0 }
};

mycmd cmd[] = {
	{"fix",optFix},
	{"save",NULL,myopt_PARA,myopt_NOOPT },
	{ "ir",optIR,myopt_NOPARA,myopt_OPT },
	{ "test",optIR,myopt_NOPARA,myopt_NOOPT }
};
cmdDecode cmd_decode(cmd,4);
int main() {

	cout << "Hello" << endl;
	string line;
	while (1) {
		getline(cin, line);
		cmd_decode.decode(line);
	}
	system("PAUSE");
}
//
//int main()
//{
//	string str1 = "fix -a 234243";
//	string::size_type iLatter  = 0;
//	string::size_type iFormer = string::npos;
//
//	while(1)
//	{
//		iLatter= str1.find_first_not_of(' ', iLatter);
//		if(string::npos== iLatter)
//		{
//			break;
//		}
//		iFormer = str1.find_first_of(' ', iLatter + 1);
//		if(string::npos == iFormer)
//		{
//			iFormer = str1.length();
//		}
//
//		// str2, str3, str4
//		string strNew(str1, iLatter, iFormer - iLatter);
//
//		cout<< strNew << endl;
//
//		iLatter = iFormer + 1;
//	}
//
//	getchar();
//}