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
	int noPara;
	int paraType;/*0:Êý×Ö,1:×Ö·û´®*/
public:
	myopt(const char * name,int arg1= myopt_PARA,int arg2= myopt_NUM) {
		this->name = name;
		noPara = arg1;
		paraType = arg2;
	}
};

class mycmd{
	string cmdname;
	int noPara;
	int noOpt;
	myopt *options;
public:
	friend class cmdDecode;
	mycmd(string name,myopt opts[],int paracfg= myopt_PARA,int optcfg= myopt_OPT) {
		this->cmdname = name;
		options = opts;
		noPara = paracfg;
		noOpt = optcfg;
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

class cmdDecode {
	mycmd *cmd;
	int cmdNUm;
	int flag;
	int curCmdIndex;
public:
	cmdDecode(mycmd cmds[],int num) {
		cmd = cmds;
		cmdNUm = num;
		flag = 0;
		curCmdIndex = -1;
	}
	int decode(string line);
	int checkPatch(string &str);
};


