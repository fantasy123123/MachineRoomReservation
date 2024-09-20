#include"manager.h"

//�޲ι��캯��
Manager::Manager() 
{

}

//�вι��캯��
Manager::Manager(string name, string pwd) 
{
	this->m_name = name; 
	this->m_pwd = pwd;

	this->initVector();


	//д�����Ա��Ϣ
	ifstream ifs;
	ifs.open(computerFile, ios::in);
	computerRoom com;
	while (ifs >> com.m_comId && ifs >> com.m_maxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();

}


//����Ա���ܽ���
void Manager::openMenu()
{
	cout << "��ӭ����Ա" << this->m_name << "��¼��" << endl;
	cout << "---------------------------------"<<endl;
	cout << "��ѡ���ܣ�" << endl;
	cout << "1.����˺�" << endl;
	cout << "2.�鿴�˺�" << endl;
	cout << "3.�鿴����" << endl;
	cout << "4.���ԤԼ" << endl;
	cout << "5.��֤ע��" << endl;


	//�����µ�ע����Ϣ���������ʾ
	ifstream ifs1;
	ifs1.open("studentSignIn.txt", ios::in);
	char ch1[2];
	ifs1 >> ch1[0];
	ifs1 >> ch1[1];
	if (!ifs1.eof())
	{
		cout << "���µ�ѧ��ע����֤��Ϣ��" << endl;
	}
	ifs1.putback(ch1[0]);
	ifs1.putback(ch1[1]);
	ifs1.close();

	ifstream ifs2;
	ifs2.open("teacherSignIn.txt", ios::in);
	char ch2[2];
	ifs2 >> ch2[0];
	ifs2 >> ch2[1];
	if (!ifs2.eof())
	{
		cout << "���µĽ�ʦע����֤��Ϣ��" << endl;
	}
	ifs2.putback(ch2[0]);
	ifs2.putback(ch2[1]);
	ifs2.close();

	ifstream ifs3;
	ifs3.open("adminSignIn.txt", ios::in);
	char ch3[2];
	ifs3 >> ch3[0];
	ifs3 >> ch3[1];
	if (!ifs3.eof())
	{
		cout << "���µĹ���Աע����֤��Ϣ��" << endl;
	}
	ifs3.putback(ch3[0]);
	ifs3.putback(ch3[1]);
	ifs3.close();

	cout << "0.ע����¼" << endl;
	cout << "---------------------------------" << endl;
	cout << "��ѡ�����Ĳ�����" << endl;
}


//����˺�
void Manager::addPerson()
{
	string filename;
	string tip;
	ofstream ofs;
	string errorTip;
	int select = 0;
	int con;
	string name;
	string pwd;
	int id;
	

again:
	cout << "����������˺����ͣ�" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;
	cout << "3.��ӹ���Ա" << endl;

	cin >> select;

	if (select == 1)
	{
		filename = studentFile;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ��ѧ���ظ�����ѧ����ע�ᣡ";
	}
	else if (select == 2)
	{
		filename = teacherFile;
		tip = "������ְ���ţ�";
		errorTip = "��ʦְ�����ظ�����ְ������ע�ᣡ";
	}
	else if (select == 3)
	{
		ofs.open("admin.txt", ios::out | ios::app);

		cout << "������������" << endl;
		cin >> name;

		bool ret = CheckRepeat2(name);
		if (ret == 1)
		{
			cout << "�˹���Ա�����ѱ�ע�ᣡ" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "���������룺";
		cin >> pwd;

		ofs << endl<< name << " " << pwd << " " << endl;
		cout << "��ӳɹ�!" << endl;
		ofs.close();
		
		this->initVector();

		cout << "-----�Ƿ���Ҫ������ӣ�-----" << endl;
		cout << "1.��Ҫ" << endl;
		cout << "2.����Ҫ" << endl;
		cin >> con;

		if (con == 1)
		{
			system("cls");
			goto again;
		}
		else
		{
			system("pause");
			system("cls");
			return;
		}

	}
	else
	{
		cout << "������������������!" << endl;
		goto again;
	}

	

	ofs.open(filename, ios::out | ios::app);
	
	cout << tip ;

	cin >> id;
	
	//�ж��Ƿ��Ѵ����˺�
	bool ret = this->checkRepeat(id, select);
	if (ret==true)
	{
		cout << errorTip<< endl;
		system("pause");
		system("cls");
		return;
	}
	
	
	cout << "������������";
	cin >> name;

	cout << "���������룺";
	cin >> pwd;

	ofs<<endl<<id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�!" << endl;
	ofs.close();

	this->initVector();
	
	cout << "-----�Ƿ���Ҫ������ӣ�-----" << endl;
	cout << "1.��Ҫ" << endl;
	cout << "2.����Ҫ" << endl;
	cin >> con;

	if (con == 1)
	{
		goto again;
	}
	else
	{
		system("pause");
		system("cls");
		return;
	}
}

//չʾ������Ϣ
void Manager::showComputer() 
{
	cout << "������Ϣ���£�" << endl;

	for (vector<computerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ�" << it->m_comId << "  �������������" << it->m_maxNum << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::clearFlie() 
{
	ofstream ofs;
	ofs.open(orderFile, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}

//��֤ע����Ϣ
void Manager::checkSignIn() 
{
	ifstream ifs1,ifs2,ifs3;
	//ifs1:student   ifs2:teacher  ifs3:admin
	ifs1.open("studentSignIn.txt", ios::in);
	ifs2.open("teacherSignIn.txt", ios::in);
	ifs3.open("adminSignIn.txt", ios::in);

		string infor1;
		vector<string>v1;
		int i1 = 0;
		
		while (ifs1 >> infor1)
		{
			v1.push_back(infor1);
			cout << infor1 << " ";
			i1++;
			if (i1 % 3 == 0)
			{
				int choice1;
			again1:
				cout << endl << "��ע����ϢΪѧ��ע����Ϣ��" << endl;
				cout << "�Ƿ���֤ͨ����ѧ��ע����Ϣ��" << endl;
				cout << "1.��" << endl;
				cout << "2.��" << endl;
			
				cin >> choice1;
				if (choice1 == 1)
				{
					ofstream ofsa;
					ofsa.open("student.txt", ios::out| ios::app);
					for (int j = 0; j < 3; j++)
					{
						ofsa << v1[j] << " ";
					}
					ofsa << endl;
					ofsa.close();
					cout << "��ѧ��ע����Ϣ��ͨ����" << endl;
				}
				else if (choice1 == 2)
				{
					cout << "��ѧ����֤��Ϣδ����ͨ����" << endl;
				}
				else
				{
					cout << "�����������������룡" << endl;
					goto again1;
				}
				v1.clear();
            }

		}
		cout << "û���µ�ѧ��ע����֤��Ϣ�ˣ�" << endl << endl;;
		ifs1.close();
		ofstream ofs1;
		ofs1.open("studentSignIn.txt", ios::out|ios::trunc);
		ofs1.close();
		system("pause");
		system("cls");

		string infor2;
		vector<string>v2;
		int i2 = 0;

		while (ifs2 >> infor2)
		{
			v2.push_back(infor2);
			cout << infor2 << " ";
			i2++;
			if (i2 % 3 == 0)
			{
				int choice2;
			again2:
				cout << endl << "��ע����ϢΪ��ʦע����Ϣ��" << endl;
				cout << "�Ƿ���֤ͨ���ý�ʦע����Ϣ��" << endl;
				cout << "1.��" << endl;
				cout << "2.��" << endl;
				
				cin >> choice2;
				if (choice2 == 1)
				{
					ofstream ofsb;
					ofsb.open("teacher.txt", ios::out | ios::app);
					for (int j = 0; j < 3; j++)
					{
						ofsb << v2[j] << " ";
					}
					ofsb << endl;
					ofsb.close();
					cout << "�ý�ʦע����Ϣ��ͨ����" << endl;
				}
				else if (choice2 == 2)
				{
					cout << "�ý�ʦ��֤��Ϣδ����ͨ����" << endl;
				}
				else
				{
					cout << "�����������������룡" << endl;
					goto again2;
				}
				v2.clear();
			}

		}
		cout << "û���µĽ�ʦע����֤��Ϣ�ˣ�" << endl ;
		ifs2.close();
		ofstream ofs2;
		ofs2.open("teacherSignIn.txt", ios::out | ios::trunc);
		ofs2.close();
		system("pause");
		system("cls");

		string infor3;
		vector<string>v3;
		int i3 = 0;

		while (ifs3 >> infor3)
		{
			v3.push_back(infor3);
			cout << infor3 << " ";
			i3++;
			if (i3 % 2 == 0)
			{
				int choice3;
			again3:
				cout <<endl<<"��ע����ϢΪ����Աע����Ϣ��" << endl;
				cout << "�Ƿ���֤ͨ���ù���Աע����Ϣ��" << endl;
				cout << "1.��" << endl;
				cout << "2.��" << endl;
			
				cin >> choice3;
				if (choice3 == 1)
				{
					ofstream ofsc;
					ofsc.open("admin.txt", ios::out | ios::app);
					for (int j = 0; j < 2; j++)
					{
						ofsc << v3[j] << " ";
					}
					ofsc << endl;
					ofsc.close();
					cout << "�ù���Աע����Ϣ��ͨ����" << endl;
				}
				else if (choice3 == 2)
				{
					cout << "�ù���Ա��֤��Ϣδ����ͨ����" << endl;
				}
				else
				{
					cout << "�����������������룡" << endl;
					goto again3;
				}
				v3.clear();
			}

		}
		cout << "û���µĹ���Աע����֤��Ϣ�ˣ�" << endl;
		ifs3.close();
		ofstream ofs3;
		ofs3.open("adminSignIn.txt", ios::out | ios::trunc);
		ofs3.close();

		system("pause");
		system("cls");
		return;
}
       
//��ȡѧ������ʦ�����Ա��Ϣ
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	vMan.clear();
	ifstream ifs;
	ifs.open(studentFile, ios::in);
	if (!ifs.is_open())
	{
		cout << "ѧ���ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		vStu.push_back(s);
	}

	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();


	ifs.open(teacherFile, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ʦ�ļ���ȡʧ��" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_empid && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		vTea.push_back(t);
	}

	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();

	ifs.open(adminFile, ios::in);
	if (!ifs.is_open())
	{
		cout << "��ʦ�ļ���ȡʧ��" << endl;
		return;
	}

	Manager m;
	while (ifs >> m.m_name && ifs >> m.m_pwd)
	{
		vMan.push_back(m);
	}
	cout << "��ǰ����Ա����Ϊ��" << vMan.size() << endl;
	ifs.close();
}


//���ѧ����Ϣ���ʦ��Ϣ�Ƿ����ظ�
bool Manager::checkRepeat(int id,int type)
{


	if (type == 1)
	{
		//���ѧ��
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_empid)
			{
				return true;
			}
		}
	}

	return false;
}


//������Ա��Ϣ�Ƿ����ظ�
bool Manager::CheckRepeat2(string name)
{
	ifstream ifs;
	ifs.open(adminFile, ios::in);

	vector<Manager>vMan;
	vMan.clear();

	Manager m;
	while (ifs >> m.m_name && ifs >> m.m_pwd)
	{
		vMan.push_back(m);
	}
	ifs.close();

	for (vector<Manager>::iterator it = vMan.begin(); it != vMan.end(); it++)
	{
		if (name == it->m_name)
		{
			return 1;
		}
	}

	return 0;
}

//��ӡѧ����Ϣ
void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_id << "  ������" << s.m_name << "  ���룺" << s.m_pwd << endl;
}

//��ӡ��ʦ��Ϣ
void printTeacher(Teacher& s)
{
	cout << "ְ���ţ�" << s.m_empid << "  ������" << s.m_name << "  ���룺" << s.m_pwd << endl;
}

//�鿴ѧ�����ʦ��Ϣ
void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1.�鿴����ѧ��" << endl;
	cout << "2.�鿴������ʦ" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else 
	{
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
	return;
}