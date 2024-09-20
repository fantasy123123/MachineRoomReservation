#include"student.h"

//无参构造函数
Student::Student() 
{

}

//有参构造函数
Student::Student(int id, string name, string pwd)
{
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;

	//写入学生信息
	ifstream ifs;
	ifs.open(computerFile, ios::in);
	computerRoom com;
	while (ifs >> com.m_comId && ifs >> com.m_maxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
}

//申请预约
void Student::applyOrder() 
{

	int date = 0;
	int interval = 0;
	int room = 0;

	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约时间：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	while(1)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}
	
	cout << "请输入申请预约的时间段" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	while (1)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}

	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_comId << "号机房容量为：" << vCom[i].m_maxNum << endl;
	}
	cout << "请选择机房号：" << endl;

	while (1)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入：" << endl;
	}

	cout << "预约成功！审核中..." << endl;

	ofstream ofs;
	ofs.open(orderFile, ios::app | ios::out);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");
}

//展示预约记录
void Student::showMyOrder() 
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "你的预约记录如下：" << endl;
	bool iforder = 0;
	for (int i = 0; i < of.m_size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str())==this->m_id )
		{
			iforder = 1;
			cout << "预约日期：周" << of.m_orderData[i]["date"] << "  ";
			cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
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
	}
	if (iforder == 0)
	{
		cout << "你暂未预约机房！" << endl;
	}
	system("pause");
	system("cls");
}

//展示所有预约记录
void Student::showAllOrder() 
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "所有预约记录如下：" << endl;
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

//取消预约
void Student::cancelOrder() 
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "你的预约记录：" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_orderData[i]["date"] << "  ";
				cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << "  ";
				cout << "机房号：" << of.m_orderData[i]["roomId"] << "  ";
				string status = "状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status+="审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}


	cout << "请输入取消的记录，0代表返回：" << endl;
	int select = 0;

	while (1)
	{
		cin >> select;

		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";

				of.updateOrder();

				cout << "已取消预约" << endl;
				break;
			}
		}

		cout << "输入有误，请重新输入：" << endl;
	}



	system("pause");
	system("cls");
	return;
}

//学生功能界面
void Student::openMenu() {
	cout << "欢迎学生代表" << this->m_name << "登录！" << endl;
	cout << "---------------------------------" << endl;
	cout << "请选择功能：" << endl;
	cout << "1.申请预约" << endl;
	cout << "2.查看我的预约" << endl;
	cout << "3.查看所有预约" << endl;
	cout << "4.取消预约" << endl;
	cout << "0.注销登录" << endl;
	cout << "---------------------------------" << endl;
	cout << "请选择您的操作：" << endl;
}
