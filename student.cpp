#include"student.h"

//�޲ι��캯��
Student::Student() 
{

}

//�вι��캯��
Student::Student(int id, string name, string pwd)
{
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;

	//д��ѧ����Ϣ
	ifstream ifs;
	ifs.open(computerFile, ios::in);
	computerRoom com;
	while (ifs >> com.m_comId && ifs >> com.m_maxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
}

//����ԤԼ
void Student::applyOrder() 
{

	int date = 0;
	int interval = 0;
	int room = 0;

	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼʱ�䣺" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;
	while(1)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}
	
	cout << "����������ԤԼ��ʱ���" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	while (1)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_comId << "�Ż�������Ϊ��" << vCom[i].m_maxNum << endl;
	}
	cout << "��ѡ������ţ�" << endl;

	while (1)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "�����������������룺" << endl;
	}

	cout << "ԤԼ�ɹ��������..." << endl;

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

//չʾԤԼ��¼
void Student::showMyOrder() 
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "���ԤԼ��¼���£�" << endl;
	bool iforder = 0;
	for (int i = 0; i < of.m_size; i++)
	{
		if (atoi(of.m_orderData[i]["stuId"].c_str())==this->m_id )
		{
			iforder = 1;
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << "  ";
			cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << "  ";
			cout << "�����ţ�" << of.m_orderData[i]["roomId"] << "  ";
			string status = "״̬��";

			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}

			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}

			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}

			else
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}
	if (iforder == 0)
	{
		cout << "����δԤԼ������" << endl;
	}
	system("pause");
	system("cls");
}

//չʾ����ԤԼ��¼
void Student::showAllOrder() 
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����ԤԼ��¼���£�" << endl;
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "��";
		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << "  ";
		cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << "  ";
		cout << "ѧ�ţ�" << of.m_orderData[i]["stuId"] << "  ";
		cout << "������" << of.m_orderData[i]["stuName"] << "  ";
		cout << "�����ţ�" << of.m_orderData[i]["roomId"] << "  ";
		string status = "״̬��";

		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}

		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}

		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}

		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

//ȡ��ԤԼ
void Student::cancelOrder() 
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "���ԤԼ��¼��" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << "  ";
				cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << "  ";
				cout << "�����ţ�" << of.m_orderData[i]["roomId"] << "  ";
				string status = "״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status+="�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}


	cout << "������ȡ���ļ�¼��0�����أ�" << endl;
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

				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}

		cout << "�����������������룺" << endl;
	}



	system("pause");
	system("cls");
	return;
}

//ѧ�����ܽ���
void Student::openMenu() {
	cout << "��ӭѧ������" << this->m_name << "��¼��" << endl;
	cout << "---------------------------------" << endl;
	cout << "��ѡ���ܣ�" << endl;
	cout << "1.����ԤԼ" << endl;
	cout << "2.�鿴�ҵ�ԤԼ" << endl;
	cout << "3.�鿴����ԤԼ" << endl;
	cout << "4.ȡ��ԤԼ" << endl;
	cout << "0.ע����¼" << endl;
	cout << "---------------------------------" << endl;
	cout << "��ѡ�����Ĳ�����" << endl;
}
