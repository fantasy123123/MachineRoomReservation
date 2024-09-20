#pragma once
using namespace std;
#include"identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globlaFile.h"
#include"orderFile.h"

//定义学生类
class Student :public Identity 
{
public:
	//无参构造函数
	Student();

	//学生ID
	int m_id;

	//有参构造函数
	Student(int id, string name, string pwd);

	//功能展示界面
	virtual void openMenu();

	//申请预约
	void applyOrder();

	//展示预约记录
	void showMyOrder();

	//展示所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	vector<computerRoom>vCom;
};