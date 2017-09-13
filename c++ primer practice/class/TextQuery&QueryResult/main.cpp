#include "main.h"
using namespace std;

TextQuery::TextQuery(ifstream &infile)
{
	string s;
	size_t lineNum = 0;
	while (getline(infile, s))
	{
		m_text.push_back(s);
		stringstream ss(s);             //�ַ���
		string word;
		while (ss >> word)
		{
			auto it = m_line.find(word);
			if (it != m_line.end())     //���map������
				it->second.insert(lineNum);
			else
			{
				m_line.insert(make_pair(word, set<size_t>{lineNum}));
			}
		}
		lineNum++;
	}
}

QueryResult TextQuery::query(string &s)
{
	auto it = this->m_line.find(s);
	shared_ptr<vector<string>> data = make_shared<vector<string>>(this->m_text);
	shared_ptr<set<size_t>> line;
	if (it != this->m_line.end())
		line = make_shared<set<size_t>>(it->second);
	else
		line = make_shared<set<size_t>>();          //ָ���set
	return QueryResult(s, line, data);

}


void runQueries(ifstream &infile)
{
	// infile��һ��ifstream��ָ��������Ҫ������ļ�
	TextQuery tq(infile);
	// ���û���������ʾ�û�����Ҫ��ѯ�ĵ��ʣ���ɲ�ѯ����ӡ���
	while (true)
	{
		cout << "enter word to look for, or q to quit: ";
		string s;
		// �������ļ�β���û�������'q'ʱѭ����ֹ
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s)) << endl;
	}
}

ostream& print(ostream& os, const QueryResult &qr)
{
	os << "element occyrs " << qr.m_row->size() << " times" << endl;
	for (set<size_t>::iterator it = qr.m_row->begin(); it != qr.m_row->end(); it++)
	{
		size_t l = *it;
		os << "( " << l + 1 << " )\t";
		os << qr.m_data->at(l) << endl;
	}
	return os;
}

int main()
{
	ifstream infile("�ļ�.txt");
	runQueries(infile);
}