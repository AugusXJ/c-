#pragma once
#include <vector>
#include <iostream>
#include "Node.h"

using namespace std;
typedef vector<vector<double>> matrix;
class Node;
class Tool
{
	friend class ECgame;
	friend class NE;
public:
	static double getMaxEigen(const vector<Node*> nodes);	//��ڵ㼯���������ֵ
	static double getMaxEigen2(const vector<Node*> nodes);	//�ڶ��ַ���
	static void outdegree(ostream &out, vector<Node*> &nodes);
private:
	static void mult(const matrix &A, vector<double> &X, vector<double> &Y, size_t N);
	static void to1(vector<double> &X, vector<double> &Y, double &maxl, size_t N);
};
