#include"teacher.h"

//�޲ι��캯��
Teacher::Teacher() 
{

}


//�вι��캯��
Teacher::Teacher(int empid, string name, string pwd) 
{
	this->m_empid = empid;
	this->m_name = name;
	this->m_pwd = pwd;
}


//��ʦ�˹��ܽ���
void Teacher::openMenu() 
{
	cout << "��ӭ��ʦ" << this->m_name << "��¼��" << endl;
	cout << "---------------------------------" << endl;
	cout << "��ѡ���ܣ�" << endl;
	cout << "1.�鿴����ԤԼ" << endl;
	cout << "2.���ԤԼ" << endl;
	cout << "0.ע����¼" << endl;
	cout << "---------------------------------" << endl;
	cout << "��ѡ�����Ĳ�����" << endl;
}


//չʾ���е�ԤԼ��¼
void Teacher::showAllOrder() 
{

	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "ԤԼ��¼���£�" << endl;

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


//չʾ����˵�ԤԼ��¼
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
	cout << "����˵�ԤԼ���£�" << endl;

	//չʾ����˵�ԤԼ��¼
	for (int i = 0; i < of.m_size; i++)
	{
			if (of.m_orderData[i]["status"] == "1" )
			{
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << "  ";
				cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << "  ";
				cout << "�����ţ�" << of.m_orderData[i]["roomId"] << "  ";
				string status = "״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				cout << status << endl;
			}
	}

	if (v.empty())
	{
		cout << "�޴���˵�ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	while (1)
	{
		cout << "��������˵�ԤԼ��¼��0�����أ�" << endl;
		cin >> select;
	
		//���ԤԼ
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "��������˽��" << endl;
				cout << "1.ͨ��" << endl;
				cout << "2.��ͨ��" << endl;
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
				cout << "�˼�¼�����ϣ�" << endl;
				system("pause");
				system("cls");
				goto again;
				
			}
		}
		else
		{
			cout << "�����������������룡" << endl;
		}
	}

	system("pause");
	system("cls");
}
