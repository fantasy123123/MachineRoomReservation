#pragma once
using namespace std;
#include"identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globlaFile.h"
#include"orderFile.h"

//定义教师类
class Teacher :public Identity {
public:
	//无参构造函数
	Teacher();

	//有参构造函数
	Teacher(int empid, string nmae, string pwd);

	//教师ID
	int m_empid;

	//功能主界面
	virtual void openMenu();

	//展示所有预约记录
	void showAllOrder();

	//审核预约
	void validOder();
};
