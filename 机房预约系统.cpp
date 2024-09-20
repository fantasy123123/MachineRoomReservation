#include<iostream>
using namespace std;
#include"globlaFile.h"
#include"identity.h"
#include<fstream>
#include<string>
#include"manager.h"
#include"teacher.h"
#include"student.h"
#include<set>

//展示管理员功能界面
void managerMenu(Identity*& manager);

//展示学生功能界面
void studentMenu(Identity*& student)
{
	while (1)
	{
		student->openMenu();

		Student* stu = (Student*)student;

		int select = 0;
	again:

		cin >> select;

		switch (select)
		{
		case 1:
			system("cls");
			stu->applyOrder();
			break;
		case 2:
			system("cls");
			stu->showMyOrder();
			break;
		case 3:
			system("cls");
			stu->showAllOrder();
			break;
		case 4:
			system("cls");
			stu->cancelOrder();
			break;
		case 0:
			delete student;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新输入：" << endl;
			goto again;
		}
		
	}
}


//展示教师功能界面
void teacherMenu(Identity*& teacher)
{
	while (1)
	{
		teacher->openMenu();

		Teacher* tea = (Teacher*)teacher;

		int select = 0;

		cin >> select;

		if (select == 1)
		{
			system("cls");
			tea->showAllOrder();
		}
		else if (select == 2)
		{
			system("cls");
			tea->validOder();
	
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;

		}
	}
}


//初始化数据
void initVector()
{
	vector<Student>vStu;

	vector<Teacher>vTea;

	vector<Manager>vMan;
	vStu.clear();
	vTea.clear();
	vMan.clear();
	ifstream ifs;
	ifs.open("studentSignIn.txt", ios::in);
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


	ifs.close();


	ifs.open("teacherSignIn.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "教师文件读取失败" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_empid && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		vTea.push_back(t);
	}


	ifs.close();

	ifs.open("adminSignIn.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "管理员文件读取失败" << endl;
		return;
	}

	Manager m;
	while (ifs >> m.m_name && ifs >> m.m_pwd)
	{
		vMan.push_back(m);
	}

	ifs.close();
}

//登录界面
void login(string fileName, int type)
{
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);
	if ( !ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;

	if (type == 1)
	{
		cout << "请输入学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入职工号：" << endl;
		cin >> id;
	}
	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	if (type == 1)
	{
		int Fid;
		string Fname;
		string Fpwd;
		while (ifs >> Fid && ifs >> Fname && ifs >> Fpwd)
		{
			if (Fid == id && Fname == name && Fpwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生身份子菜单
				studentMenu(person);

				return;
			}
		}
	}
	else if (type == 2)
	{
		int Fid;
		string Fname;
		string Fpwd;
		while (ifs >> Fid && ifs >> Fname && ifs >> Fpwd)
		{
	        if (Fid == id && Fname == name && Fpwd == pwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师身份子菜单
				teacherMenu(person);

				return;
			}
		}
	}
	else if (type == 3)
	{
		string Fname;
		string Fpwd;
		while (ifs >> Fname && ifs >> Fpwd)
		{
			if (Fname == name && Fpwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//进入管理员身份子菜单
				managerMenu(person);

				return;
			}
		}
	}

	cout << "登陆失败" << endl;
	system("pause");
	system("cls");
	return;
}

//选择注册时，检测用户名是否已被注册
bool CheckRepeat1(int id, int type)
{
	vector<Student>vStu;
	vector<Teacher>vTea;

	vStu.clear();
	vTea.clear();


	ifstream ifs;
	ifs.open(studentFile, ios::in);

	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		vStu.push_back(s);
	}
	ifs.close();

	ifs.open(teacherFile, ios::in);

	Teacher t;
	while (ifs >> t.m_empid && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		vTea.push_back(t);
	}
    ifs.close();


	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_id)
			{
				return 1;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_empid)
			{
				return 1;
			}
		}
	}

	return 0;
}

//选择注册时，检测用户名是否已被注册
bool CheckRepeat2(string name)
{
	vector<Manager>vMan;
	vMan.clear();

	ifstream ifs;
	ifs.open(adminFile, ios::in);

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

//选择注册时，检测用户名是否已被注册
bool CheckRepeat3(int id, int type)
{
	vector<Student>vStu;
	vector<Teacher>vTea;

	vStu.clear();
	vTea.clear();


	ifstream ifs;
	ifs.open("studentSignIn.txt", ios::in);

	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		vStu.push_back(s);
	}
	ifs.close();

	ifs.open("teacherSignIn.txt", ios::in);

	Teacher t;
	while (ifs >> t.m_empid && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		vTea.push_back(t);
	}
	ifs.close();


	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_id)
			{
				return 1;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_empid)
			{
				return 1;
			}
		}
	}

	return 0;
}

//选择注册时，检测用户名是否已被注册
bool CheckRepeat4(string name)
{
	vector<Manager>vMan;
	vMan.clear();

	ifstream ifs;
	ifs.open("adminSignIn.txt", ios::in);

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

//注册界面
void signin() {
	cout << "------------欢迎注册！--------------" << endl;
	cout << "请选择您的身份：" << endl;
	cout << "1.学生代表" << endl;
	cout << "2.老师" << endl;
	cout << "3.管理员" << endl;
	cout << "------------------------------------" << endl;
	ofstream ofs;
	int slct;

again:
	
	cin >> slct;
	if (slct == 1)
	{
		int fid;
		string fname;
		string fpwd;
        ofs.open("studentSignIn.txt", ios::out | ios::app);

		cout << endl << "请输入学号：";
		cin >> fid;

		bool ret1 = CheckRepeat1(fid, slct);
		bool ret2 = CheckRepeat3(fid, slct);
		if (ret1 == 1||ret2==1)
		{
			cout << "此学号已经注册！" << endl;
			system("pause");
			system("cls");
			return;
		}

		ofs << fid << " ";

		cout << "请输入姓名：";
		cin >> fname;
		ofs << fname << " ";

		cout << "请输入密码：";
		cin >> fpwd;
		ofs << fpwd << endl; 

		cout << "注册成功,等待管理员验证！" << endl;

		ofs.close();
		initVector();
	}
	else if (slct == 2)
	{
		int fid;
		string fname;
		string fpwd;

		ofs.open("teacherSignIn.txt", ios::out | ios::app);
		cout << endl << "请输入职工号：";
		cin >> fid;

		bool ret1 = CheckRepeat1(fid, slct);
		bool ret2 = CheckRepeat3(fid, slct);
		if (ret1 == 1||ret2==1)
		{
			cout << "此职工号已经注册！" << endl;
			system("pause");
			system("cls");
			return;
		}

		ofs<< fid << " ";

		cout << "请输入姓名：";
		cin >> fname;
		ofs << fname << " ";

		cout << "请输入密码：";
		cin >> fpwd;
		ofs << fpwd << endl;

		cout << "注册成功,等待管理员验证！" << endl;

		ofs.close();
		initVector();
	}
	else if (slct == 3)
	{
		string fname;
		string fpwd;

		ofs.open("adminSignIn.txt", ios::out | ios::app);
	
        cout << "请输入姓名：";
		cin >> fname;

		bool ret1 = CheckRepeat2(fname);
		bool ret2 = CheckRepeat4(fname);
		if (ret1 == 1||ret2==1)
		{
			cout << "此管理员姓名已经注册！" << endl;
			system("pause");
			system("cls");
			return;
		}
		
		ofs<<endl<< fname << " ";

		cout << "请输入密码：";
		cin >> fpwd;
		ofs << fpwd << endl;

		cout << "注册成功,等待管理员验证！" << endl;

		ofs.close();
		initVector();
	}
	else
	{
		cout << "输入有误，请重新输入身份：" ;
		goto again;
	}

	
	system("pause");
	system("cls");
	return;
}


//管理员功能界面
void managerMenu(Identity*& manager)
{
	while (1)
	{
		manager->openMenu();

		Manager* man = (Manager*)manager;
		int slct = 0;
	again:
		
		cin >> slct;

		if (slct == 1)
		{
			system("cls");
			//cout << "添加账号" << endl;

			man->addPerson();
		}
		else if (slct == 2)
		{
			system("cls");
			//cout << "查看账号" << endl;

			man->showPerson();
		}
		else if (slct == 3)
		{
			system("cls");
			//cout << "查看机房" << endl;
			
			man->showComputer();
		}
		else if (slct == 4)
		{
			system("cls");
			//cout << "清空预约" << endl;
			
			man->clearFlie();
		}
		else if (slct == 5)
		{
			system("cls");
			//cout << "验证注册" << endl;
		
			man->checkSignIn();
		}
		else if (slct == 0)
		{
			delete manager;
			cout << "注销登录成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "输入有误，请重新输入：" << endl;
			goto again;
		}
        
	}
}



//主函数
int main()
{

	ofstream ofs1;
	ifstream ifs1;
	ofs1.open("studentSignIn.txt", ios::out | ios::app);
	ifs1.open("studentSignIn.txt", ios::in);
	char ch1;
	ifs1 >> ch1;
	if (ifs1.eof())
	{
		//ofs1 << ":";
	}
	ifs1.putback(ch1);
	ofs1.close();
	ifs1.close();

	ofstream ofs2;
	ifstream ifs2;
	ofs2.open("teacherSignIn.txt", ios::out | ios::app);
	ifs2.open("teacherSignIn.txt", ios::in);
	char ch2;
	ifs2 >> ch2;
	if (ifs2.eof())
	{
		//ofs2<< ":";
	}
	ifs2.putback(ch2);
	ofs2.close();
	ifs2.close();

	ofstream ofs3;
	ifstream ifs3;
	ofs3.open("adminSignIn.txt", ios::out | ios::app);
	ifs3.open("adminSignIn.txt", ios::in);
	char ch3;
	ifs3 >> ch3;
	if (ifs3.eof())
	{
		//ofs3<< ":";
	}
	ifs3.putback(ch3);
	ofs3.close();
	ifs3.close();


	//选择身份
	int slc = 0;
	while (1)
	{
		cout << "----------欢迎使用机房预约系统---------------" << endl;
		cout << "请输入您的身份" << endl;
		cout << "1.学生代表" << endl;
		cout << "2.老师" << endl;
		cout << "3.管理员" << endl;
		cout << "----------或者您可选择：---------------------" << endl;
		cout << "4.注册" << endl;
		cout << "0.退出" << endl;
		cout << "---------------------------------------------" << endl;

		cin >> slc;

		switch (slc)
		{case 1:
			login(studentFile, 1);
			break;
		case 2:
			login(teacherFile, 2);
			break;
		case 3:
			login(adminFile, 3);
			break;
		case 4:
			signin();
			break;
		case 0:
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}



