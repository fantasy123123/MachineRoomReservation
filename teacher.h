#pragma once
using namespace std;
#include"identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globlaFile.h"
#include"orderFile.h"

//�����ʦ��
class Teacher :public Identity {
public:
	//�޲ι��캯��
	Teacher();

	//�вι��캯��
	Teacher(int empid, string nmae, string pwd);

	//��ʦID
	int m_empid;

	//����������
	virtual void openMenu();

	//չʾ����ԤԼ��¼
	void showAllOrder();

	//���ԤԼ
	void validOder();
};
