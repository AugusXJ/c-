#include "Node.h"
#include "ECgame.h"
#include "tool.h"
#include "20180102_method.h"
#include <map>

using namespace std;

//�жϽڵ��Ƿ�Ϊ��Ӱ��ڵ�
bool ifInfluenced2(Node* n, map<Node*, bool> &ifchoosed)
{
    if(n->strategies == 1 || ifchoosed[n] == true)
        return true;
    for(auto i:n->nei())
    {
        if(i->strategies == 1)
            return true;
    }
    return false;
}

//Ѱ�ҽڵ�n��δӰ���ھ���
int UnInfluNei2(Node* n, map<Node*, bool> &ifchoosed)
{
    int num = 0;
    for(auto i:n->nei())
    {
        if(ifInfluenced2(i, ifchoosed) == false)
            num++;
    }
    return num;
}

//�ھ���δ���ָ���
int clusterNei(Node *n)
{
    int num = 0;
    for(auto i:n->nei())
    {
        if(i->strategies == 1)
            num++;
    }
    return num;
}

//�õ��ڵ�n�ķ���
int Soc(Node* n, map<Node*, bool> &ifchoosed)
{
    int s = 0;
    for(auto i:n->nei())
    {
        if(ifInfluenced2(i, ifchoosed) == false)
            s += UnInfluNei2(i, ifchoosed);
    }
    return s;
}

double sigmoid(float frac)
{
    return 1/(1+exp(-10*(frac - 0.5)));
}

//ʵ����
Node* get_targetNode(vector<Node*> nodes, map<Node*, bool> &ifchoosed, map<Node*, double> &score)
{
    Node* target_node = nullptr;
    //����ÿ������ķ���
    bool ifAllZero = true;
    for(auto i:nodes)
    {
        if(ifchoosed[i] == false)
        {
            //double f = sigmoid(frac);
            //double f = frac;
            //score[i] = (1-f) * UnInfluNei2(i, ifchoosed) + f * clusterNei(i);
            score[i] = UnInfluNei2(i, ifchoosed) + 0.001*Soc(i, ifchoosed);
            if(score[i] > 0)
                ifAllZero = false;
        }
    }
    if(ifAllZero)
    {
        for(auto i:nodes)
        {
            if(ifchoosed[i] == false)
            {
                score[i] = clusterNei(i);
            }
        }
    }
    double max_score = -1;
    for(auto i:nodes)
    {
        //cout<<i->getFlag()<<"  "<<score[i]<<endl;
        if(ifchoosed[i] == false && score[i] > max_score)
        {
            max_score = score[i];
            target_node = i;
        }
    }
    return target_node;
//    //ѡ����ͬ�����ĸ���
//    vector<Node*> candidate;
//    for(auto i:nodes)
//    {
//        if( ifchoosed[i] == false && score[i] == max_score)
//            candidate.push_back(i);
//    }
//    cout<<candidate.size()<<endl;
//    if(candidate.size() == 1)
//        target_node = candidate[0];
//    else
//    {
//        cout<<"Same Score~~~~~~"<<endl;
//        max_score = -1;
//        for(auto i:candidate)
//        {
//            double s = Soc(i, ifchoosed);
//            if(s > max_score)
//            {
//                max_score = s;
//                target_node = i;
//            }
//        }
//    }
}

int method_20180102(NE &ne, double T)
{
    float frac = T/ne.lambda1;
    vector<Node*> nodes = ne.nodes;
    map<Node*, bool> ifchoosed;
    map<Node*, double> score;
    for(auto i:nodes)
    {
        i->strategies = 0;
        ifchoosed[i] = false;
        score[i] = -0.1;
    }
    for(int t = 0;t < ECgame::size;t++)
    {
        Node* target_node = get_targetNode(nodes, ifchoosed, score);
        cout<<"target_Node:   "<<target_node->getFlag()<<"  score:  "<<score[target_node];
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
        }
        cout<<endl;
        cout<<"lambda:   "<<l<<endl;
        cout<<"----------------------------------------------------"<<endl;
    }
    int num = count_if(nodes.begin(),nodes.end(),[](Node* n){return n->strategies == 0;});
        return num;
}

//---------------------------------------------------------------------------------
Node* UnInf_max_element(vector<Node*> nodes, map<Node*, bool> ifchoosed)
{
    Node* target_Node;
    int Uninf_max = -1;
    for(auto i:nodes)
    {
        if(ifchoosed[i] == false)
        {
            int num = UnInfluNei2(i, ifchoosed);
            if(num > Uninf_max)
            {
                target_Node = i;
                Uninf_max = num;
            }
        }
    }
    return target_Node;
}

bool ifchange_flag(vector<Node*> nodes, map<Node*, bool> ifchoosed)
{
    vector<Node*> unvacc;
    for(auto i:nodes)
    {
        if(i->strategies == 1)
        {
            for(auto j:i->nei())
            {
                if(ifchoosed[j] == false)
                    return false;
            }
        }
    }
    return true;
}
int method_20180103(NE &ne, double T)
{
    float frac = T/ne.lambda1;
    vector<Node*> nodes = ne.nodes;
    map<Node*, bool> ifchoosed;
    map<Node*, double> score;
    bool flag = false;              //��������Ƿ��п�ѡ�ڵ㡣���û��ѡ��Ӱ��ڵ����ĵ�
    for(auto i:nodes)
    {
        i->strategies = 0;
        ifchoosed[i] = false;
        score[i] = -1;
    }
    for(int t = 0;t < ECgame::size;t++)
    {
        Node* target_node = nullptr;
        vector<Node*> candi;
        if(flag == false)
        {
            for(auto i:nodes)
            {
                if(ifchoosed[i] == false)
                {
                    score[i] = UnInfluNei2(i, ifchoosed);
                    candi.push_back(i);
                }
            }
            flag = true;
        }
        else
        {
            //�������������ÿ������ķ���
            bool ifAllZero = true;
            for(auto i:nodes)
            {
                if(ifchoosed[i] == false)
                {
                    int n2 = clusterNei(i), n1 = UnInfluNei2(i, ifchoosed);
                    if(n2 != 0)                     //n1 = 0 ��ʱ��û����
                    {
                        //double f = sigmoid(frac);
                        double f = frac;
                        score[i] = (1-f) * n2 + f * n1;
                        candi.push_back(i);
                    }
                }
            }
        }
        double max_score = -1;
        for(auto i:candi)
        {
            if(ifchoosed[i] == false && score[i] > max_score)
            {
                max_score = score[i];
                target_node = i;
            }
        }
//        if(candi.size() == 0)
//            cout<<"error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
//        double max_score = -1;
//        for(auto i:candi)
//        {
//            //cout<<i->getFlag()<<"  "<<score[i]<<endl;
//            if(ifchoosed[i] == false && score[i] > max_score)
//            {
//                max_score = score[i];
//            }
//        }
//        //ѡ����ͬ�����ĸ���
//        vector<Node*> candidate;
//        for(auto i:candi)
//        {
//            if( ifchoosed[i] == false && score[i] == max_score)
//                candidate.push_back(i);
//        }
//        cout<<candidate.size()<<endl;
//        if(candidate.size() == 1)
//            target_node = candidate[0];
//        else
//        {
//            max_score = -1;
//            for(auto i:candidate)
//            {
//                int s = Soc(i, ifchoosed);
//                if(s > max_score)
//                {
//                    max_score = s;
//                    target_node = i;
//                }
//            }
//        }
        cout<<"target_Node:   "<<target_node->getFlag()<<"  score:  "<<score[target_node];
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
        }
        cout<<endl;
        cout<<"lambda:   "<<l<<endl;
        cout<<"----------------------------------------------------"<<endl;
        if(ifchange_flag(nodes, ifchoosed))
            flag = false;               //��true��Ϊfalse
    }
    int num = count_if(nodes.begin(),nodes.end(),[](Node* n){return n->strategies == 0;});
        return num;
}
