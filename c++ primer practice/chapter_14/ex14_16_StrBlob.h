#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>

using namespace std;


class StrBlob
{
	friend class StrBlobPtr;
	friend bool operator==(const StrBlob &, const StrBlob &);
	friend bool operator!=(const StrBlob &s1, const StrBlob &s2);
	StrBlobPtr begin();
	StrBlobPtr end();
public:
	typedef vector<string>::size_type size_type;
	StrBlob() : data(make_shared<vector<string>>()) {}
	StrBlob(initializer_list<string> il);
	StrBlob(string il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//��Ӻ�ɾ��Ԫ��
	void push_back(const string &t) { data->push_back(t); }
	void pop_back();
	//Ԫ�ط���
	string& front() const;
	string& back() const;
private:
	shared_ptr<vector<string>> data;
	//���data[i]���Ϸ����׳�һ���쳣
	void check(size_type i, const string &msg) const;
};

class StrBlobPtr
{
public:
	friend bool operator==(const StrBlobPtr &s1, const StrBlobPtr &s2);
	friend bool operator!=(const StrBlobPtr &s1, const StrBlobPtr &s2);
	friend bool operator>(const StrBlobPtr &s1, const StrBlobPtr &s2);
	friend bool operator<(const StrBlobPtr &s1, const StrBlobPtr &s2);
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	string& deref() const
	{
		auto p = check(curr, "deference past end");
		return (*p)[curr];
	}
	StrBlobPtr& icur()			//ǰ׺����
	{
		auto p = check(curr, "deference past end");
		++curr;
		return *this;
	}
private:
	//������ɹ���check����һ��ָ��vector��shared_ptr
	shared_ptr<vector<string>> check(size_t i, const string& msg) const
	{
		auto ret = wptr.lock();
		if (!ret)
			throw runtime_error("unbound StrBolbPtr");
		if (i >= ret->size())
		{
			throw out_of_range(msg);
		}
		return ret;
	}
	//����һ��weak_ptr����ζ�ŵײ�vector���ܱ�����
	weak_ptr<vector<string>> wptr;
	size_t curr;
};
