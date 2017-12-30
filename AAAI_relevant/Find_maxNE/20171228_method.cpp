#include "Node.h"
#include "ECgame.h"
#include "tool.h"
#include "20171228_method.h"
#include <map>

using namespace std;

//������
Node* max_degree(vector<Node*> nodes)
{
    Node* maxDegree_Node = nullptr;
    int maxD = 0;
    for(auto i:nodes)
    {
        if(i->degree() > maxD)
        {
            maxDegree_Node = i;
            maxD = maxDegree_Node->degree();
        }

    }
    return maxDegree_Node;
}

////�����������ٵĽڵ㼯�ϣ��ȴ���2��
//vector<Node*> get_min_link_node(vector<Node*> nodes,  map<Node*, int> link_num,  map<Node*, bool> ifchoosed)
//{
//    vector<Node*> min_link_node;
//    int min_link = ECgame::size;
//    vector<Node*> candidate;
//    for(auto i:nodes)
//    {
//        if(i->degree() > 1 && ifchoosed[i] == false)
//            candidate.push_back(i);
//    }
//    for(auto i:candidate)
//    {
//        if(link_num[i] !=0 && link_num[i] < min_link)
//            min_link = link_num[i];
//    }
//    if(min_link == ECgame::size)
//        min_link = 0;
//    for(auto i:candidate)
//        if(link_num[i] == min_link)
//            min_link_node.push_back(i);
//    return min_link_node;
//}

//����������duoduodduodudodudoudo�Ľڵ㼯�ϣ��ȴ���2��
vector<Node*> get_min_link_node(vector<Node*> nodes,  map<Node*, int> link_num,  map<Node*, bool> ifchoosed)
{
    vector<Node*> min_link_node;
    int min_link = 0;
    vector<Node*> candidate;
    for(auto i:nodes)
    {
        if(i->degree() > 1 && ifchoosed[i] == false)
            candidate.push_back(i);
    }
    for(auto i:candidate)
    {
        if( link_num[i] > min_link)
            min_link = link_num[i];
    }
    if(min_link == ECgame::size)
        min_link = 0;
    for(auto i:candidate)
        if(link_num[i] == min_link)
            min_link_node.push_back(i);
    return min_link_node;
}

//�ҽ��ֽڵ�
vector<Node*> get_vacc_nodes(vector<Node*> nodes,  map<Node*, int> link_num,  map<Node*, bool> ifchoosed)
{
    vector<Node*> min_link_node;
    int min_link = 0;
    vector<Node*> candidate;
    for(auto i:nodes)
    {
        if( ifchoosed[i] == false)
            candidate.push_back(i);
    }
    return candidate;
}


//�жϽڵ��Ƿ�Ϊ��Ӱ��ڵ�
bool ifInfluenced(Node* n)
{
    if(n->strategies == 1)
        return true;
    for(auto i:n->nei())
    {
        if(i->strategies == 1)
            return true;
    }
    return false;
}

//Ѱ�ҽڵ�n��δӰ���ھ���
int UnInfluNei(Node* n)
{
    int num = 0;
    for(auto i:n->nei())
    {
        if(ifInfluenced(i) == false)
            num++;
    }
    return num;
}

//��ȡ����δӰ���ھ����ڵ�
vector<Node*> get_max_UnInfluNei_nodes( vector<Node*> min_link_node)
{
    map<Node*, int> UninfluNei_num;
    vector<Node*> max_UnInfluNei_nodes;
    for(auto i:min_link_node)
        UninfluNei_num[i] = UnInfluNei(i);
    int maxNum = -100;
    for(auto i:min_link_node)
    {
        if(UninfluNei_num[i] > maxNum)
            maxNum = UninfluNei_num[i];
    }
    for(auto i:min_link_node)
    {
        if(UninfluNei_num[i] == maxNum)
            max_UnInfluNei_nodes.push_back(i);
    }
    return max_UnInfluNei_nodes;
}

//�õ��ڵ�n�ķ���
int score(Node* n)
{
    int s = 0;
    for(auto i:n->nei())
    {
        if(ifInfluenced(i) == false)
            s += UnInfluNei(i);
    }
    return s;
}

Node* get_max_score(vector<Node*> max_UnInfluNei_nodes)
{
    int max_score = -100;
    Node* max_score_node = nullptr;
    for(auto i:max_UnInfluNei_nodes)
    {
        int s = score(i);
        if(s > max_score)
        {
            max_score_node = i;
            max_score = s;
        }
    }
    return max_score_node;
}
/*
������
1.	���и��崦�ڽ���״̬��
2.	�����ж϶����Ľڵ��Ƿ���Բ����֣���Ϊ��һ���㣬�϶����ԣ����γɳ�ʼ��C��
3.	�ж������еĽڵ����C����������ѡ����С�������Ľڵ㣨����Ҫ���ڵ�2����
    3.1	����С��������ͬ����ѡȡ��Χδ��Ӱ�쵽�Ľ��ֽڵ�������ġ�
    3.2	��δ��Ӱ�쵽�Ľ��ֽڵ�Ҳ��ͬ������������ڵ�ķ�����С��
*/
int cluster_improved(vector<Node*> nodes, double T)
{
    int size = ECgame::size;
    map<Node*, bool> ifchoosed;
    map<Node*, int> link_num;
    //ȫ���������
    for(auto i:nodes)
    {
        i->strategies = 0;
        link_num[i] = 0;
        ifchoosed[i] = false;
    }
    //Ѱ�Ҷ����ĵ�
    Node* first_node = max_degree(nodes);
    first_node->strategies = 1;
    for(auto i:first_node->nei())
        link_num[i] ++;
    ifchoosed[first_node] = true;
    cout<<"first:   "<<first_node->getFlag()<<endl;
    while(true)
    {
        Node* target_node = nullptr;
        //�����������ٵĽڵ�
        vector<Node*> min_link_node = get_vacc_nodes(nodes, link_num, ifchoosed);
        cout<<"size of min_link_node:      "<<min_link_node.size()<<endl;
//        //-----
//        for(auto i:min_link_node)
//            cout<<i->getFlag()<<"  ";
//        cout<<endl;
//        //----
        if(min_link_node.size() == 0)                                       //ֻʣ��Ҷ�ӽڵ���
            break;
        else if(min_link_node.size() == 1)
            target_node = min_link_node[0];
        else
        {
            vector<Node*> max_UnInfluNei_nodes = get_max_UnInfluNei_nodes(min_link_node);
            cout<<"size of max_UnInfluNei_nodes:      "<<max_UnInfluNei_nodes.size()<<endl;
//            //-----
//            for(auto i:max_UnInfluNei_nodes)
//                cout<<i->getFlag()<<"  ";
//            cout<<endl;
//            //----
            if(max_UnInfluNei_nodes.size() == 1)
                target_node = max_UnInfluNei_nodes[0];
            else
                target_node = get_max_score(max_UnInfluNei_nodes);
        }
        //��Ŀ��ڵ���д���
        cout<<"target_Node:   "<<target_node->getFlag();
        ifchoosed[target_node] = true;
        target_node->strategies = 1;
        double l = Tool::getMaxEigen(nodes);
        if(l > T)
        {
            target_node->strategies = 0;
            cout<<"  vacc  ";
        }
        else
        {
            cout<<"  unvacc  ";
            for(auto i:target_node->nei())
                link_num[i] ++;
        }
        cout<<endl;
        cout<<"lambda:   "<<l<<endl;
        cout<<"----------------------------------------------------"<<endl;
    }
    //��Ҷ�ӽڵ���д���
    for(auto i:nodes)
    {
        if(ifchoosed[i] == false)
        {
            if(i->degree() != 1)
                cout<<"error!!!!!!!!"<<endl;
            cout<<"leaf node:  "<<i->getFlag();
            i->strategies = 1;
            double l = Tool::getMaxEigen(nodes);
            if(l > T)
            {
                i->strategies = 0;
                cout<<"  vacc  ";
            }
            else
                cout<<"  unvacc  ";
            cout<<endl;

        }
    }
    int num = count_if(nodes.begin(),nodes.end(),[](Node* n){return n->strategies == 0;});
    return num;
}
