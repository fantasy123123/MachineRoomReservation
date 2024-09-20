#pragma once
#include<iostream>
using namespace std;

//定义人物类
class Identity {
public:
	//功能界面
	virtual void openMenu() = 0;

	//用户名
	string m_name;
	//密码
	string m_pwd;
};
