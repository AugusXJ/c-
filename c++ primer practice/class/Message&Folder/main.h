#include <memory>
#include <string>
#include <set>
#include <stdlib.h>


using namespace std;

class Message
{
	friend class Folder;
public:
	//folders����ʽ��ʼ��Ϊ�ռ���
	Message(const string &str = "") :contents(str) {}
	//�������Ƴ�Ա����������ָ��Message��ָ��
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	//�Ӹ���Folder���������/ɾ����Message
	void save(Folder &);
	void remove(Folder &);

private:
	string contents;                //ʵ����Ϣ�ı�
	set<Folder*> folders;           //������Message��Folder
									//�������캯����������ֵ������������������õĹ��ߺ���
									//����Message��ӵ�ָ�������Folder��
	void add_to_Folders(const Message&);
	//��folders�е�ÿ��Folder��ɾ����Message
	void remove_from_Folders();
};

class Folder
{
	friend class Message;
public:
	Folder(const string str = "") :name(str) {}
	Folder(const Folder &) = delete;
	~Folder();
	Folder operator=(const Folder&) = delete;
	void addMsg(Message*);          //��messages�����
	void remMsg(Message*);          //��messages��ɾ��
private:
	string name;
	set<Message*> messages;
};