#pragma once
#include<iostream>
using namespace std;

//����������
class Identity {
public:
	//���ܽ���
	virtual void openMenu() = 0;

	//�û���
	string m_name;
	//����
	string m_pwd;
};
