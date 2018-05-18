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
	id_index = 0;
	id_num = 0;
	id[0] = 0;
	curcmd = 0;
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
		if (checkPatch(strNew) < 0)
			break;
		//cout << strNew << endl;

		iLatter = iFormer + 1;
	}
	if (id[0] == -1) {//无此命令
		return -1;
	}
	if (flag == 2) {
		cout << "error:命令" << curcmd->name() <<" " <<curcmd ->curopt->name<< "缺少参数" << endl;
		id[0] = -1;
		return -1;
	}
	if (id_num == 0) {//判断无参命令
		if (curcmd == NULL) return 0;
		if (curcmd->noPara == 1) {
			id[0] = curcmd->id << 8;
			id_num++;
			return id[0];
		}
		else {
			cout << "error:命令" << curcmd->name() << "缺少选项与参数"<< endl;
			id[0] = -1;
			return -1;
		}
	}

	return id[0];
}

int cmdDecode::checkPatch(string &str) {
	if (flag == 0) {//检查命令名称
		if (find(str) == 0) {
			cout << "error:没有此命令" << str << endl;
			id[0] = -1;
			return -1;
		}
		else {
			id[0] = (curcmd->id << 8);
			flag = 1;;
		}
	}
	else if (flag == 1) {//检查选项名称
		if (int optid= curcmd->find(str)) {//有匹配选项
			id[id_num] = (curcmd->id << 8)+ curcmd->curopt->id;
			if (curcmd->curopt->noPara == myopt_NOPARA){//无参
				_data[id_num] = atoi(str.data());
				id_num++;
				flag = 1;
			}
			else{//有参
				flag = 2;
			}
		}
		else {//无匹配选项
			if (curcmd->noPara == 1) {//直接参数
				_data[id_num] = atoi(str.data());
				id[id_num]= curcmd->id << 8;
				id_num++;
				flag = 1;
			}
			else {
				cout << "命令" << curcmd->cmdname << "没有选项参数" << str << endl;
				id[0] = -1;
				return -1;
			}
		}
	}
	else if (flag == 2) {//参数
		_data[id_num] = atoi(str.data());
		id_num++;
		flag = 1;
	}
	return 0;
}
//
//int cmdDecode::getid() {
//	return 0;
//}