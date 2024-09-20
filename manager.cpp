#include"manager.h"

//无参构造函数
Manager::Manager() 
{

}

//有参构造函数
Manager::Manager(string name, string pwd) 
{
	this->m_name = name; 
	this->m_pwd = pwd;

	this->initVector();


	//写入管理员信息
	ifstream ifs;
	ifs.open(computerFile, ios::in);
	computerRoom com;
	while (ifs >> com.m_comId && ifs >> com.m_maxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();

}


//管理员功能界面
void Manager::openMenu()
{
	cout << "欢迎管理员" << this->m_name << "登录！" << endl;
	cout << "---------------------------------"<<endl;
	cout << "请选择功能：" << endl;
	cout << "1.添加账号" << endl;
	cout << "2.查看账号" << endl;
	cout << "3.查看机房" << endl;
	cout << "4.清空预约" << endl;
	cout << "5.验证注册" << endl;


	//若有新的注册信息，则进行提示
	ifstream ifs1;
	ifs1.open("studentSignIn.txt", ios::in);
	char ch1[2];
	ifs1 >> ch1[0];
	ifs1 >> ch1[1];
	if (!ifs1.eof())
	{
		cout << "有新的学生注册验证信息！" << endl;
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
		cout << "有新的教师注册验证信息！" << endl;
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
		cout << "有新的管理员注册验证信息！" << endl;
	}
	ifs3.putback(ch3[0]);
	ifs3.putback(ch3[1]);
	ifs3.close();

	cout << "0.注销登录" << endl;
	cout << "---------------------------------" << endl;
	cout << "请选择您的操作：" << endl;
}


//添加账号
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
	cout << "请输入添加账号类型：" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;
	cout << "3.添加管理员" << endl;

	cin >> select;

	if (select == 1)
	{
		filename = studentFile;
		tip = "请输入学号：";
		errorTip = "学生学号重复，此学号已注册！";
	}
	else if (select == 2)
	{
		filename = teacherFile;
		tip = "请输入职工号：";
		errorTip = "教师职工号重复，此职工号已注册！";
	}
	else if (select == 3)
	{
		ofs.open("admin.txt", ios::out | ios::app);

		cout << "请输入姓名：" << endl;
		cin >> name;

		bool ret = CheckRepeat2(name);
		if (ret == 1)
		{
			cout << "此管理员姓名已被注册！" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "请输入密码：";
		cin >> pwd;

		ofs << endl<< name << " " << pwd << " " << endl;
		cout << "添加成功!" << endl;
		ofs.close();
		
		this->initVector();

		cout << "-----是否需要继续添加？-----" << endl;
		cout << "1.需要" << endl;
		cout << "2.不需要" << endl;
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
		cout << "输入有误，请重新输入!" << endl;
		goto again;
	}

	

	ofs.open(filename, ios::out | ios::app);
	
	cout << tip ;

	cin >> id;
	
	//判断是否已存在账号
	bool ret = this->checkRepeat(id, select);
	if (ret==true)
	{
		cout << errorTip<< endl;
		system("pause");
		system("cls");
		return;
	}
	
	
	cout << "请输入姓名：";
	cin >> name;

	cout << "请输入密码：";
	cin >> pwd;

	ofs<<endl<<id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功!" << endl;
	ofs.close();

	this->initVector();
	
	cout << "-----是否需要继续添加？-----" << endl;
	cout << "1.需要" << endl;
	cout << "2.不需要" << endl;
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

//展示机房信息
void Manager::showComputer() 
{
	cout << "机房信息如下：" << endl;

	for (vector<computerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_comId << "  机房最大容量：" << it->m_maxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::clearFlie() 
{
	ofstream ofs;
	ofs.open(orderFile, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

//验证注册信息
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
				cout << endl << "该注册信息为学生注册信息！" << endl;
				cout << "是否验证通过该学生注册信息？" << endl;
				cout << "1.是" << endl;
				cout << "2.否" << endl;
			
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
					cout << "该学生注册信息已通过！" << endl;
				}
				else if (choice1 == 2)
				{
					cout << "该学生验证信息未给予通过！" << endl;
				}
				else
				{
					cout << "输入有误，请重新输入！" << endl;
					goto again1;
				}
				v1.clear();
            }

		}
		cout << "没有新的学生注册验证消息了！" << endl << endl;;
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
				cout << endl << "该注册信息为教师注册信息！" << endl;
				cout << "是否验证通过该教师注册信息？" << endl;
				cout << "1.是" << endl;
				cout << "2.否" << endl;
				
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
					cout << "该教师注册信息已通过！" << endl;
				}
				else if (choice2 == 2)
				{
					cout << "该教师验证信息未给予通过！" << endl;
				}
				else
				{
					cout << "输入有误，请重新输入！" << endl;
					goto again2;
				}
				v2.clear();
			}

		}
		cout << "没有新的教师注册验证消息了！" << endl ;
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
				cout <<endl<<"该注册信息为管理员注册信息！" << endl;
				cout << "是否验证通过该管理员注册信息？" << endl;
				cout << "1.是" << endl;
				cout << "2.否" << endl;
			
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
					cout << "该管理员注册信息已通过！" << endl;
				}
				else if (choice3 == 2)
				{
					cout << "该管理员验证信息未给予通过！" << endl;
				}
				else
				{
					cout << "输入有误，请重新输入！" << endl;
					goto again3;
				}
				v3.clear();
			}

		}
		cout << "没有新的管理员注册验证消息了！" << endl;
		ifs3.close();
		ofstream ofs3;
		ofs3.open("adminSignIn.txt", ios::out | ios::trunc);
		ofs3.close();

		system("pause");
		system("cls");
		return;
}
       
//读取学生、教师与管理员信息
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	vMan.clear();
	ifstream ifs;
	ifs.open(studentFile, ios::in);
	if (!ifs.is_open())
	{
		cout << "学生文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		vStu.push_back(s);
	}

	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();


	ifs.open(teacherFile, ios::in);
	if (!ifs.is_open())
	{
		cout << "老师文件读取失败" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_empid && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		vTea.push_back(t);
	}

	cout << "当前老师数量为：" << vTea.size() << endl;
	ifs.close();

	ifs.open(adminFile, ios::in);
	if (!ifs.is_open())
	{
		cout << "老师文件读取失败" << endl;
		return;
	}

	Manager m;
	while (ifs >> m.m_name && ifs >> m.m_pwd)
	{
		vMan.push_back(m);
	}
	cout << "当前管理员数量为：" << vMan.size() << endl;
	ifs.close();
}


//检测学生信息或教师信息是否有重复
bool Manager::checkRepeat(int id,int type)
{


	if (type == 1)
	{
		//检测学生
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


//检测管理员信息是否有重复
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

//打印学生信息
void printStudent(Student& s)
{
	cout << "学号：" << s.m_id << "  姓名：" << s.m_name << "  密码：" << s.m_pwd << endl;
}

//打印教师信息
void printTeacher(Teacher& s)
{
	cout << "职工号：" << s.m_empid << "  姓名：" << s.m_name << "  密码：" << s.m_pwd << endl;
}

//查看学生或教师信息
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有老师" << endl;
	int select = 0;
	cin >> select;

	if (select == 1)
	{
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else 
	{
		cout << "所有老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
	return;
}