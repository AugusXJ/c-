#include <allocators>
#include <memory>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
class String
{
	friend ostream& operator<<(ostream &os, const String s);
public:
	String() :begin(nullptr), end(nullptr) {}
	String(const char *s)
	{
		char* s1 = const_cast<char*>(s);
		while (*s1) ++s1;
		auto newdata = alloc_n_copy(s, s1);
		begin = newdata.first;
		end = newdata.second;
	}
	String(const String &s)		//��������
	{
		auto newdata = alloc_n_copy(s.begin, s.end);
		begin = newdata.first;
		end = newdata.second;
	}
	String &operator=(const String &s)
	{
		free();
		auto newdata = alloc_n_copy(s.begin, s.end);
		begin = newdata.first;
		end = newdata.second;
		return *this;
	}
	~String()
	{
		free();
	}
	void free()//�ͷ��ڴ�  
	{
		if (begin)
		{
			for_each(begin, end, [this](char &rhs) {alloc.destroy(&rhs); });
			alloc.deallocate(begin, end - begin);
		}
	}
private:
	allocator<char> alloc;											//����Ԫ��
	pair<char*, char*> alloc_n_copy(const char*b, const char*e)
	{
		//����ռ䱣�������Χ�ڵ�Ԫ��
		auto data = alloc.allocate(e - b);
		//��ʼ��������һ��pair����pair��data��uninitialized_copy�ķ���ֵ����
		return { data, uninitialized_copy(b,e,data) };
	}
	char *begin;
	char *end;
};

ostream &operator << (ostream &os, const String s)
{
	for (auto i = s.begin; i != s.end; i++)
		os << *i;
	return os;
}

int main()
{
	String s1("ddd");
	cout << s1 << endl;
	system("pause");
	return 0;
}