#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<string>
#include<fstream>
#include"globlaFile.h"
#include<vector>
#include<algorithm>
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

//定义管理员类
class Manager :public Identity 
{
public:
	//无参构造函数
	Manager();

	//有参构造函数
	Manager(string name, string pwd);

	//功能界面
	virtual void openMenu();

	//添加人物信息
	void addPerson();

	//展示人物信息
	void showPerson();

	//展示机房信息
	void showComputer();

	//清空预约
	void clearFlie();

	//验证注册
	void checkSignIn();

	//初始化容器
	void initVector();

	vector<Student>vStu;

	vector<Teacher>vTea;

	vector<Manager>vMan;

	vector<computerRoom>vCom;

	//检测人物信息是否重复
	bool checkRepeat(int id, int type);
	bool CheckRepeat2(string name);
};
