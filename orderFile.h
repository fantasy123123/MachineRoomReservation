#pragma once
#include<iostream>
using namespace std;
#include"globlaFile.h"
#include<fstream>
#include<map>
#include<string>

//����ԤԼ��¼��
class OrderFile
{
public:
	//ԤԼ��¼���캯������ȡԤԼ��¼�ĸ�����Ϣ
	OrderFile();

	//����ԤԼ��¼��д���µ�ԤԼ��Ϣ
	void updateOrder();

	//ԤԼ��¼����
	int m_size;

	//�ݴ�ԤԼ��¼������
	map<int, map<string, string>>m_orderData;

};