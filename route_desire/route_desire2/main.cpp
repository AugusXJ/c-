#include "main.h"
#include "distance.h"
#include "greedy.h"

//ȫ�ֱ���
const size_t g_allDist = 2000;
//--------
using namespace std;

void InputData(vector<CNode> &nodeVec, vector<CLink> &linkVec)
{
    ifstream infile("�����������.txt");
    string str;float in;
    while(infile >> str >> in)
        nodeVec.push_back(CNode(str,in));
    infile.close();
    infile.open("����֮�����·���.txt");
    string node1, node2;
    size_t distance;
    bool ifAvailabel;
    float builtCost;
    while(infile >> node1 >> node2 >> distance >> ifAvailabel >> builtCost)
        linkVec.push_back(CLink(node1, node2, distance, ifAvailabel, builtCost));

}
void PrintCost(const vector<CNode> &nodeVec)
{
    size_t sum = 0;
    for(auto it = nodeVec.begin(); it!= nodeVec.end(); it++)
    {
        cout << it->m_label << " ������������Ϊ�� " << it->m_logistCost <<endl;
        sum += it->m_logistCost;
    }
    cout << "����������Ϊ�� " << sum << endl;
}


void PrintPath(vector<CNode> &nodeVec)
{
    ofstream outfile("·��.csv");
    outfile<<"���б��"<<","<<"��ǧ��"<<","<<"·��"<<endl;
    for(auto i= nodeVec.begin(); i!= nodeVec.end(); i++)
    {
        if(i->m_ifTransfer == true)
            i->m_logistCost = i->m_cargonDistance * 5 * i->m_cargoNum * 1000 * 10/10000000;
        else
            i->m_logistCost = i->m_cargonDistance * 10* i->m_cargoNum * 1000 * 10/10000000;
//        cout<<i->m_cargonDistance<<"     "<<i->m_cargoNum<<endl;
        outfile<<i->m_label<<","<<i->m_logistCost<< ",";
        //���·��
        for(auto s: i->m_cargonRoute)
            outfile<<s<<",";
        outfile<<endl;
    }

}
int main()
{
    vector<CNode> nodeVec;                  //��Žڵ㼯��
    vector<CLink> linkVec;                  //������Ӽ���
    InputData(nodeVec, linkVec);
    cout<< "�ڵ�����Ϊ�� "<< nodeVec.size() << "   ��������Ϊ�� " << linkVec.size() << endl;


    ChooseCargonRoute(nodeVec, linkVec);
//    PrintPath(nodeVec);
    deque<size_t> greedyResult = Greedy(nodeVec,linkVec);

    ofstream outfile("����.csv");
    outfile<<"����1"<<","<<"����2"<<endl;
    for(auto i: greedyResult)
    {
        outfile<< linkVec[i].m_node1 << "," << linkVec[i].m_node2 << endl;
    }

    double cost = GetCost(nodeVec, linkVec, greedyResult);
    outfile<<"\n\n\n";
    outfile<<"���б��"<<","<<"��ǧ��"<<endl;
    for(auto i: nodeVec)
        outfile<<i.m_label<<","<<i.m_logistCost/10000000<<endl;
    cout<< cost/10000000 << endl;




    system("pause");
    return 0;
}
