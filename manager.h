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

//�������Ա��
class Manager :public Identity 
{
public:
	//�޲ι��캯��
	Manager();

	//�вι��캯��
	Manager(string name, string pwd);

	//���ܽ���
	virtual void openMenu();

	//���������Ϣ
	void addPerson();

	//չʾ������Ϣ
	void showPerson();

	//չʾ������Ϣ
	void showComputer();

	//���ԤԼ
	void clearFlie();

	//��֤ע��
	void checkSignIn();

	//��ʼ������
	void initVector();

	vector<Student>vStu;

	vector<Teacher>vTea;

	vector<Manager>vMan;

	vector<computerRoom>vCom;

	//���������Ϣ�Ƿ��ظ�
	bool checkRepeat(int id, int type);
	bool CheckRepeat2(string name);
};
