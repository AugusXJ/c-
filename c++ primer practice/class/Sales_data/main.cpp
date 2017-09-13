#include <iostream>  
#include <string>  
#include <stdlib.h>
using namespace std;

class Sales_data
{
	// ������Ԫ����  
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
	friend ostream &operator<<(ostream&, const Sales_data&);
	friend istream &operator>>(istream&, Sales_data&);

public:

	// ���캯��  
	Sales_data():bookNo(""), units_sold(0), revenue(0.0){ }

	// ��ȡ����ǰ������  
	Sales_data(istream &is) { cout<<(is, *this); }

	// ����isbn���  
	string isbn() const { return bookNo; }

	//������ֵ�����
	Sales_data& operator=(const Sales_data &rhs)
	{
		this->bookNo = rhs.bookNo;
		this->revenue = rhs.revenue;
		this->units_sold = rhs.units_sold;
		return *this;
	}
	// ���ص�ǰ���������  
	Sales_data& operator+=(const Sales_data& rhs)
	{
		if (rhs.bookNo == this->bookNo)
		{
			units_sold += rhs.units_sold;
			revenue += rhs.revenue;
			return *this;
		}
	}

	// ����  
	double avg_price() const
	{
		if (units_sold)
		{
			return revenue / units_sold;
		}
		return 0;
	}

private:
	string bookNo; // isbn����  
	unsigned units_sold; // ���˶��ٲ�  
	double revenue; // ������  
};


// ��Ԫ����������һ��istream����cin, һ��Sales_data���� ����һ��istream���������cin�� ������������  
istream& operator>>(istream &is, Sales_data &item)
{
	double price = 0;
	cout << "����ͼ����:	";
	is >> item.bookNo;
	cout << "������������:	";
	is >> item.units_sold;
	cout << "����ͼ�鵥��:	";
	is >> price;
	item.revenue = price * item.units_sold;
	return is;
}


// ��Ԫ����������һ��ostream����cout�� һ��Sales_data���� ����һ��ostream���������cout, ������ʽ���  
ostream& operator<<(ostream &os, const Sales_data &item)
{
	os << "ͼ���ţ�	"<<item.isbn() << "	����������	" << item.units_sold << "	�����棺	 "
		<< item.revenue << "	���ۣ�	" << item.avg_price();
	return os;
}

Sales_data operator+(const Sales_data &a, const Sales_data &b)
{
	Sales_data temp = a;
	temp += b;
	return temp;
}

int main()
{
	Sales_data total;
	if (cin>>(cin, total))  // ��ȡ�������ݣ� ����total�У� ������cin   
	{
		Sales_data trans;
		if(cin >> (cin, trans))
		{
			if (total.isbn() == trans.isbn()) // �жϵ�ǰisbn��ǰһ��isbn�Ƿ����  
			{
				total = total + trans;  // �ӵ���ǰ����total��  
			}
			else
			{
				cout<<(cout, total) << endl; // �����ǰ����  
				total = trans;  // ���µ�ǰ����  
			}
		}

		cout<<(cout, total) << endl; // �����ǰ����(���Ķ���)  
	}
	else
	{
		cerr << "No data?!" << endl; // �ʼ�Ͷ�ȡʧ��  
	}
	system("pause");
	return 0;
}