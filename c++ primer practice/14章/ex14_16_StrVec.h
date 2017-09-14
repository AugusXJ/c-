#include <allocators>
#include <memory>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;
// ��vector���ڴ������Եļ�ʵ��
class StrVec
{
	friend bool operator==(const StrVec &sv1, const StrVec &sv2);
	friend bool operator!=(const StrVec &sv1, const StrVec &sv2);
public:
	StrVec() :elements(nullptr), first_tree(nullptr), cap(nullptr) {}        //Ĭ�ϳ�ʼ��
	StrVec(const StrVec&);                                                  //�������캯��
	~StrVec();                                                              //��������
	StrVec &operator=(const StrVec&);                                       //������ֵ�����
	void push_back(const string&);                                          //����Ԫ��
	size_t size() const { return first_tree - elements; }
	size_t capacity() const { return cap - elements; }
	string *begin() const { return elements; }
	string *end() const { return first_tree; }

private:
	allocator<string> alloc;                                            //����Ԫ��
																		//�����Ԫ�صĺ���ʹ��
	void chk_n_alloc()
	{
		if (size() == capacity())
			reallocate();
	}
	// ���ߺ��������������캯������ֵ�����������������ʹ��
	pair<string*, string*> alloc_n_copy(const string*, const string*);
	void free();                                                            //����Ԫ�ز��ͷ��ڴ�
	void reallocate();                                                      //��ø����ڴ沢��������Ԫ��
	string *elements;                                                       //ָ��������Ԫ�ص�ָ��
	string *first_tree;                                                     //ָ�������һ������Ԫ�ص�ָ��
	string *cap;                                                            //ָ������β��ָ���λ��
};