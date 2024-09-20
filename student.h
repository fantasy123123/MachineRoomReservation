#pragma once
using namespace std;
#include"identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globlaFile.h"
#include"orderFile.h"

//����ѧ����
class Student :public Identity 
{
public:
	//�޲ι��캯��
	Student();

	//ѧ��ID
	int m_id;

	//�вι��캯��
	Student(int id, string name, string pwd);

	//����չʾ����
	virtual void openMenu();

	//����ԤԼ
	void applyOrder();

	//չʾԤԼ��¼
	void showMyOrder();

	//չʾ����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	vector<computerRoom>vCom;
};