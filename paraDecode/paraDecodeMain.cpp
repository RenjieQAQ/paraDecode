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
	{0}
};
myopt optIR[] = {
	{ "-s",myopt_PARA ,myopt_NUM },
	{ "-a",myopt_PARA ,myopt_STR },
	{ "-c",myopt_NOPARA ,myopt_STR },
	{ 0 }
};

mycmd cmd[] = {
	{"fix",optFix,cmdline_fix },
	{"save",NULL,cmdline_save,myopt_PARA,myopt_NOOPT },
	{ "ir",optIR,cmdline_ir,myopt_NOPARA,myopt_OPT },
	{ "test",optIR,cmdline_test,myopt_NOPARA,myopt_NOOPT }
};
cmdDecode cmd_decode(cmd,4);
int main() {

	cout << "Hello" << endl;
	string line;
	while (1) {
		getline(cin, line);
		int id;
		while (id = cmd_decode.decode(line),id>0) {
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
				cout << "cmd error" << endl;
				break;
			}
		}
		;
	}
	system("PAUSE");
}
