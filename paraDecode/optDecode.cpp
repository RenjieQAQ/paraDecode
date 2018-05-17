#include "optDecode.h"
#include <iostream>
#include <string>
using namespace std;

int mycmd::decode(string line) {
	return 0;
}

int cmdDecode::decode(string line) {
	string::size_type iLatter = 0;
	string::size_type iFormer = string::npos;
	flag = 0;
	while (1)
	{
		iLatter = line.find_first_not_of(' ', iLatter);
		if (string::npos == iLatter)
		{
			break;
		}
		iFormer = line.find_first_of(' ', iLatter + 1);
		if (string::npos == iFormer)
		{
			iFormer = line.length();
		}

		// str2, str3, str4
		string strNew(line, iLatter, iFormer - iLatter);
		if(checkPatch(strNew)<0)
			break;
		//cout << strNew << endl;

		iLatter = iFormer + 1;
	}
	if(flag==0)
		return id;
	if (flag == -1)
		return 0;
}

int cmdDecode::checkPatch(string &str){
	if (flag == 0) {
		int match = 0;
		for (int i = 0; i < cmdNUm; i++) {
			if (cmd[i].match(str)) {
				curCmdIndex = i;
				match++;
				break;
			}
		}
		if (match == 0) {
			cout << "没有此命令" << str << endl;
			id = -1;
			return -1;
		}
		else {
			//if((cmd[curCmdIndex].noPara==1) && (cmd[curCmdIndex].noOpt==1))
			id = (cmd[curCmdIndex].id << 8);
		}
		flag++;
	}
	return 0;
}