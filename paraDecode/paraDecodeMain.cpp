#include <iostream>
#include <string>
using namespace std;
#include <stdio.h>
#include "optDecode.h"
#include "command.h"


myopt optFix[] = {
	{ "-a",myopt_PARA ,myopt_NUM },
	{ "-B",myopt_PARA ,myopt_STR },
	{ "-x",myopt_NOPARA ,myopt_STR },
	{ "null",myopt_NOPARA ,myopt_STR },
	{0}
};
myopt optIR[] = {
	{ "-s",myopt_PARA ,myopt_NUM },
	{ "-a",myopt_PARA ,myopt_STR },
	{ "-c",myopt_NOPARA ,myopt_STR },
	{ "null",myopt_PARA ,myopt_STR },
	{ 0 }
};
myopt optTest[] = {
	{ "-s",myopt_PARA ,myopt_NUM },
	{ "-a",myopt_PARA ,myopt_STR },
	{ "-c",myopt_NOPARA ,myopt_STR },
//{ "null",myopt_PARA ,myopt_STR },
	{ 0 }
};

mycmd cmd[] = {
	{"fix",optFix,cmdline_fix },
	//{"save",NULL,cmdline_save, },
	{ "ir",optIR,cmdline_ir},
	{ "test",optTest,cmdline_test},
	{0}
};
cmdDecode cmd_decode(cmd);
int main() {

	cout << "Hello" << endl;
	string line;
	while (1) {
		getline(cin, line);
		int id = cmd_decode.decode(line);
		if ((id >> 8) < 0) {
			cout << "cmd error" << endl;
			continue;
		}
		if ((id >> 8) == 0) {
			cout << "please input cmd" << endl;
			continue;
		}
		cout << "------------" << endl;
		while (id = cmd_decode.getid() ,id>0) {
			switch (id >> 8) {
			case cmdline_fix:
				cout << "fix:" <<(id &0xff)<< endl;
				cout << "data:" << cmd_decode.data() << endl;
				break;
			case cmdline_save:
				cout << "save:" << (id & 0xff) << endl;
				cout << "data:" << cmd_decode.data() << endl;
				break;
			case cmdline_ir:
				cout << "ir:" << (id & 0xff) << endl;
				cout << "data:" << cmd_decode.data() << endl;
				break;
			case cmdline_test:
				cout << "test:" << (id & 0xff) << endl;
				cout << "data:" << cmd_decode.data() << endl;
				break;
			default:
				cout << "emmmmmm" << endl;
				break;
			}
		}
		;
	}
	system("PAUSE");
}
