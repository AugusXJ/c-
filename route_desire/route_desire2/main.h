#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <deque>
using namespace std;
class CNode
{
public:
    const std::string m_label;          //�ڵ���
    const float m_cargoNum;             //ÿ�����������ǧ��
    vector<size_t> m_minDistance;               //���·������
    vector<vector<string> > m_route;             //���·�������Ľڵ�
    size_t m_cargonDistance;                //�˻�·������
    vector<string> m_cargonRoute;           //�˻�·��
    double m_logistCost;                //�ó��е�C15�������ɱ�
    bool m_ifTransfer;                  //�Ƿ���ת

    CNode() = default;
    CNode(const std::string &label, float cargoNum)
        :m_label(label), m_cargoNum(cargoNum), m_logistCost(0), m_ifTransfer(false){};

};

class CLink
{
public:
    const string m_node1;               //�ڵ�1
    const string m_node2;               //�ڵ�2
    const size_t m_distance;            //���ӳ���
    bool m_ifAvailable;                 //�Ƿ��Ѿ�����
    float m_builtCost;                    //����ɱ�

    CLink() = default;
    CLink(string node1, string node2, size_t weight, bool ifAvailable, float builtCost)
        :m_node1(node1), m_node2(node2), m_distance(weight), m_ifAvailable(ifAvailable), m_builtCost(builtCost){};
};

extern const size_t g_allDist;          //��·����
#endif // MAIN_H_INCLUDED
