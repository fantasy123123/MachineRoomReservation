#include"teacher.h"

//无参构造函数
Teacher::Teacher() 
{

}


//有参构造函数
Teacher::Teacher(int empid, string name, string pwd) 
{
	this->m_empid = empid;
	this->m_name = name;
	this->m_pwd = pwd;
}


//教师端功能界面
void Teacher::openMenu() 
{
	cout << "欢迎教师" << this->m_name << "登录！" << endl;
	cout << "---------------------------------" << endl;
	cout << "请选择功能：" << endl;
	cout << "1.查看所有预约" << endl;
	cout << "2.审核预约" << endl;
	cout << "0.注销登录" << endl;
	cout << "---------------------------------" << endl;
	cout << "请选择您的操作：" << endl;
}


//展示所有的预约记录
void Teacher::showAllOrder() 
{

	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "预约记录如下：" << endl;

	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：周" << of.m_orderData[i]["date"] << "  ";
		cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
		cout << "学号：" << of.m_orderData[i]["stuId"] << "  ";
		cout << "姓名：" << of.m_orderData[i]["stuName"] << "  ";
		cout << "机房号：" << of.m_orderData[i]["roomId"] << "  ";
		string status = "状态：";

		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}

		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}

		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}

		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}


//展示待审核的预约记录
void Teacher::validOder() 
{
	OrderFile of;

	vector<int>v;
	int index ;
	int select = 0;
	int ret = 0;

again:
	v.clear();
	index = 1;
	cout << "待审核的预约如下：" << endl;

	//展示待审核的预约记录
	for (int i = 0; i < of.m_size; i++)
	{
			if (of.m_orderData[i]["status"] == "1" )
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_orderData[i]["date"] << "  ";
				cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
				cout << "机房号：" << of.m_orderData[i]["roomId"] << "  ";
				string status = "状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				cout << status << endl;
			}
	}

	if (v.empty())
	{
		cout << "无待审核的预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	while (1)
	{
		cout << "请输入审核的预约记录，0代表返回：" << endl;
		cin >> select;
	
		//审核预约
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "此记录审核完毕！" << endl;
				system("pause");
				system("cls");
				goto again;
				
			}
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
		}
	}

	system("pause");
	system("cls");
}
