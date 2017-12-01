#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "ECgame.h"

class Node
{
	friend std::vector<Node*> inputData(const std::string&);
	friend bool operator==(const Node &n1, const Node &n2);
	friend void toMatrix(std::vector<std::vector<double>> &matrix, const std::vector<Node*> &nodes);
	friend class NE;
	friend class ECgame;
public:
	Node(int f):fixflag(f),strategies(1),ifGetSubsidy(false){flag = fixflag;}
	Node() = default;
	~Node() = default;
	size_t degree() { return neighbours.size(); }
	std::vector<Node*> nei() { return neighbours; }
	int getFlag() { return flag; }
	bool ifNei(Node *A);			//if this node is a nighbour of Node A
	int strategies;
	bool ifGetSubsidy;
private:
	std::vector<Node*> neighbours;
	int flag;
	const int fixflag;
};

std::vector<Node*> inputData(const std::string&);		//���ɽڵ�ָ�뼯
void deleteNode(std::vector<Node*> nodes);				//ɾ���ڵ�ָ�뼯
void toMatrix(std::vector<std::vector<double>> &matrix, const std::vector<Node*> &nodes);





