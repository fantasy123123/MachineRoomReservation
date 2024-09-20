#pragma once
#include<iostream>
using namespace std;
#include"globlaFile.h"
#include<fstream>
#include<map>
#include<string>

//定义预约记录类
class OrderFile
{
public:
	//预约记录构造函数，获取预约记录的各项信息
	OrderFile();

	//更新预约记录，写入新的预约信息
	void updateOrder();

	//预约记录条数
	int m_size;

	//暂存预约记录的容器
	map<int, map<string, string>>m_orderData;

};