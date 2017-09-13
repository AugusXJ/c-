#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>

using namespace std;


class StrBlob
{
	friend class StrBlobPtr;
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

StrBlob::StrBlob(initializer_list<string> il)
{
	data = make_shared<vector<string>>(vector<string>{il});
}
StrBlob::StrBlob(string il)
{
	data = make_shared<vector<string>>(vector<string>{il});
}

void StrBlob::check(size_type i, const string &msg) const
{
	if (i >= data->size())
		throw out_of_range(msg);
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
string& StrBlob::front() const
{
	check(0, "pop_back on empty StrBlob");
	return data->front();
}
string& StrBlob::back() const
{
	check(0, "pop_back on empty StrBlob");
	return data->back();
}


class StrBlobPtr
{
public:
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

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}

int main()
{
	StrBlob str = { "first", "second", "third" };
	StrBlobPtr ptr = StrBlobPtr(str);
	cout << ptr.deref() << endl;				//cout "first"
	ptr.icur();
	cout << ptr.deref() << endl;				//cout "second"


	system("pause");
	return 0;
}