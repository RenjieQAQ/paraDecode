#pragma once

#include <string>
using namespace std;
enum {
	myopt_PARA=0,
	myopt_NOPARA
};

enum {
	myopt_OPT = 0,
	myopt_NOOPT
};

enum {
	myopt_NUM = 0,
	myopt_STR
};

class myopt {
public:
	const char *name;
	int id;
	int noPara;
	int paraType;/*0:Êý×Ö,1:×Ö·û´®*/
public:
	myopt(const char * name,int arg1= myopt_PARA,int arg2= myopt_NUM) {
		this->name = name;
		noPara = arg1;
		paraType = arg2;
		if (name == NULL)
			id = -1;
		else if (strcmp(name, "null") == 0)
			id = 0;
		else 
			id = name[1];
	}
};

class mycmd{
	string cmdname;
	int noPara;
	//int noOpt;
	myopt *options;
	myopt *curopt;
	int id;

	bool find(string str) {
		int i = 0;
		int temp = 0;
		while (options[i].name != NULL)
		{
			if (options[i].name == NULL)
				return 0;
			if (str.compare(options[i].name) == 0) {
				temp ++;
				curopt = options + i;
				break;
			}
			i++;
		}
		return temp;
	}
public:
	friend class cmdDecode;
	mycmd(char *name) {
		cmdname = "";
		options = NULL;
		id = 0;
		curopt = NULL;
	}
	mycmd(string name,myopt opts[],int id=0) {
		this->cmdname = name;
		options = opts;
		//noPara = paracfg;
		//noOpt = optcfg;
		this->id = id;
		curopt = NULL;
		if (opts == NULL) {
			noPara = 1;
			return;
		}
		if (find("null"))
			noPara = 1;
		else
			noPara = 0;
	}
	int decode(string line);
	string name() {
		return cmdname;
	}
	bool match(string str) {
		if (str == cmdname)
			return true;
		else
			return false;
	}
};

/***********************************/
class cmdDecode {
	mycmd *cmd;
	mycmd *curcmd;
	//myopt *curopt;
	int cmdNUm;
	int flag;
	//int curCmdIndex;

	int id[10];
	int _data[10];
	int id_num;
	int id_index;
private:
	int checkPatch(string &str);
	bool find(string &str) {
		int match = 0;
		for (int i = 0; i < cmdNUm; i++) {
			if (cmd[i].match(str)) {
				curcmd = cmd+i;//curCmdIndex = i;
				match++;
				break;
			}
		}
		return match;
	}
public:
	cmdDecode(mycmd cmds[]) {
		cmd = cmds;
		int i = 0;
		while (cmd[i++].cmdname!="");
		cmdNUm = i-1;
		flag = 0;
		curcmd = NULL;
	}
	int decode(string line);
	int getid() {
		if (id_index < id_num)
			return id[id_index++];
		else
			return 0;
	}
	int data() {
		if (id_index <= id_num)
			return _data[id_index-1];
		else
			return 0;
	}
};


