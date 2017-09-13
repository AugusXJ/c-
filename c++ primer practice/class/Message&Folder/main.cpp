#include "main.h"
using namespace std;

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

//����Message��ӵ�ָ��m��Folder��
void Message::add_to_Folders(const Message &m)
{
	for (auto i : m.folders)
	{
		i->addMsg(this);
	}
}

//�Ƴ�ָ��Message��Folder
void Message::remove_from_Folders()
{
	for (auto i : folders)
	{
		i->remMsg(this);
	}
}

//�������ƺ���
Message::Message(const Message &m) :contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &m)
{
	//ͨ����ɾ��ָ���ٲ��������������Ը�ֵ���
	remove_from_Folders();
	contents = m.contents;
	folders = m.folders;
	add_to_Folders(m);
	return *this;
}

void Folder::addMsg(Message *m)
{
	messages.insert(m);
}

void Folder::remMsg(Message *m)
{
	messages.erase(m);
}

Folder::~Folder()
{
	for (auto i : messages)
	{
		i->remove(*this);
	}
}


int main()
{
	Folder f1("f1");
	Message m1("m1");
	m1.save(f1);
	system("pause");
	return 0;
}