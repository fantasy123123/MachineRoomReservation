#include"orderFile.h"

//ԤԼ��¼���캯������ȡԤԼ��¼�ĸ�����Ϣ
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(orderFile, ios::in);

	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	this->m_size = 0;

	//����ԤԼ��Ϣ
	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		string key;
		string value;
		map<string, string>m;

		//ͨ������":"����һ������Ϣ��һ�ָ��ԤԼ��¼��һ������Ϣ�������ݴ�ԤԼ��¼��������
		int pos=date.find(":");
		if (pos !=  -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));

		}
	
		//ͨ������":"����һ������Ϣ��һ�ָ��ԤԼ��¼��һ������Ϣ�������ݴ�ԤԼ��¼��������
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));

		}

		//ͨ������":"����һ������Ϣ��һ�ָ��ԤԼ��¼��һ������Ϣ�������ݴ�ԤԼ��¼��������
		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
			
		}

		//ͨ������":"����һ������Ϣ��һ�ָ��ԤԼ��¼��һ������Ϣ�������ݴ�ԤԼ��¼��������
		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));

		}

		//ͨ������":"����һ������Ϣ��һ�ָ��ԤԼ��¼��һ������Ϣ�������ݴ�ԤԼ��¼��������
		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));

		}

		//ͨ������":"����һ������Ϣ��һ�ָ��ԤԼ��¼��һ������Ϣ�������ݴ�ԤԼ��¼��������
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));

		}

		this->m_orderData.insert(make_pair(this->m_size, m));
		this->m_size++;
	}
	ifs.close();

//	for (map<int, map<string, string>>::iterator it = this->m_orderData.begin(); it != this->m_orderData.end(); it++)
//{
//	cout << "date:" << it->second["date"] << " ";
//cout << "interval:" << it->second["interval"] << " ";
//cout << "stuId:" << it->second["stuId"] << " ";
//	cout << "stuName:" << it->second["stuName"] << " ";
//	cout << "roomId:" << it->second["roomId"] << " ";
//cout << "status:" << it->second["status"] << endl;
//}
}


//����ԤԼ��¼��д���µ�ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{
		return;
	}

	ofstream ofs(orderFile, ios::out | ios::trunc);

	for (int i = 0; i < this->m_size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}

	ofs.close();

}
