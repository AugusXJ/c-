#include "ex14_16_StrVec.h"

using namespace std;
void StrVec::push_back(const string &s)
{
	chk_n_alloc();          //ȷ���пռ�����Ԫ��
							// ��first_freeָ���Ԫ���й���s�ĸ���
	alloc.construct(first_tree++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string*e)
{
	//����ռ䱣�������Χ�ڵ�Ԫ��
	auto data = alloc.allocate(e - b);
	//��ʼ��������һ��pair����pair��data��uninitialized_copy�ķ���ֵ����
	return { data, uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
	//���ܴ��ݸ�deallocateһ����ָ�룬���ellementΪ0������ʲôҲ����
	if (elements)
	{
		for (auto p = first_tree; p != elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec &s)
{
	//����alloc_n_copy����ռ���������s��һ�����Ԫ��
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_tree = newdata.second;
	cap = newdata.second;
}

StrVec::~StrVec()
{
	free();
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
	//�ͷ�ԭ�ڴ�
	free();
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newdata.first;
	first_tree = newdata.second;
	return *this;
}

void StrVec::reallocate()
{
	//���ǽ����䵱ǰ��С�����Ŀռ�
	auto newcapacity = size() ? 2 * size() : 1;
	//�������ڴ�
	auto newdata = alloc.allocate(newcapacity);
	//�����ݴӾ��ڴ��Ƶ����ڴ���
	auto dest = newdata;            //ָ������������һ������λ��
	auto elem = elements;           //ָ�����������һ��Ԫ��
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, move(*elem++));
	//�ͷž��ڴ�ռ�
	free();
	elements = newdata;
	first_tree = dest;
	cap = elements + newcapacity;
}

bool operator==(const StrVec &sv1, const StrVec &sv2)
{
	return(sv1.size() == sv2.size() && equal(sv1.begin(), sv1.end(), sv2.begin()));
}
bool operator!=(const StrVec &sv1, const StrVec &sv2)
{
	return !(sv1 == sv2);
}
bool operator<(const StrVec &sv1, const StrVec &sv2)
{
	return sv1.size() < sv2.size();
}
bool operator>(const StrVec &sv1, const StrVec &sv2)
{
	return sv1.size() > sv2.size();
}