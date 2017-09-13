#include <iostream>  
#include <string>  
using namespace std;

class Sales_data
{
	// ������Ԫ����  
	friend ostream &print(ostream&, const Sales_data&);
	friend istream &read(istream&, Sales_data&);

public:

	// ���캯��  
	Sales_data()
		:bookNo(""), units_sold(0), revenue(0.0)
	{

	}

	// ��ȡ����ǰ������  
	Sales_data(istream &is)
	{
		read(is, *this);
	}

	// ����isbn���  
	string isbn() const
	{
		return bookNo;
	}

	// ���ص�ǰ���������  
	Sales_data& combine(const Sales_data& rhs)
	{
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
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
istream& read(istream &is, Sales_data &item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}


// ��Ԫ����������һ��ostream����cout�� һ��Sales_data���� ����һ��ostream���������cout, ������ʽ���  
ostream& print(ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();

	return os;
}


int main()
{
	Sales_data total;
	if (read(cin, total))  // ��ȡ�������ݣ� ����total�У� ������cin   
	{
		Sales_data trans;
		while (read(cin, trans))  // ��ȡ�������ݣ� ����trans�У� ������cin   
		{
			if (total.isbn() == trans.isbn()) // �жϵ�ǰisbn��ǰһ��isbn�Ƿ����  
			{
				total.combine(trans);  // �ӵ���ǰ����total��  
			}
			else
			{
				print(cout, total) << endl; // �����ǰ����  
				total = trans;  // ���µ�ǰ����  
			}
		}

		print(cout, total) << endl; // �����ǰ����(���Ķ���)  
	}
	else
	{
		cerr << "No data?!" << endl; // �ʼ�Ͷ�ȡʧ��  
	}

	return 0;
}