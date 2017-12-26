#include <vector>
#include <list>
#include <map>
#include <stdexcept>
#include "20171225_method.h"

using namespace std;

//----------------------------------------------------------------------------------------
/*
�������Ӷ���С�ĵ㿪ʼѰ�ң�Ȼ�������ھ��ж�С��ĳ��ָ��ĵ���н��֣����й�ȱ���
*/
vector<int> minDeg(const NE &ne, vector<int> vec);
vector<int> maxDeg(const NE &ne, vector<int> vec);

int BreadthMethod(NE &ne, int Deg_threshold, double T)
{
    ne.init();
    vector<int> vacc_vec;
    list<int> ready2Vacc;
    list<int> bigDegList;
    vector<int> unvacc;
    vector<bool> flag(ECgame::size, false);
    double lastl = 0.0;
    //�Ҷ���С�ĵ�
    for(int i=0;i<NE::size;i++)
        unvacc.push_back(i);
    int mindegree_index = minDeg(ne, unvacc)[0];
    ready2Vacc.push_back(mindegree_index);flag[mindegree_index] = true;
    cout<<"---------stage 1-----------"<<endl;
    while(!(ready2Vacc.empty() && bigDegList.empty()))
    {
        if(ready2Vacc.empty())
        {
            ready2Vacc = bigDegList;
            bigDegList.clear();
        }
        int index = ready2Vacc.front();
        ready2Vacc.pop_front();
        ne.nodes[index]->strategies = 0;
        vacc_vec.push_back(index);
        double l = Tool::getMaxEigen(ne.nodes);
        if(l==-1)
            l = lastl;
        lastl = l;
        cout<<"<<stage 1>>   add flag:  "<<index<<"    num:  "<<vacc_vec.size()<<"\tmaxeigenV:  "<<l<<endl;
        if(l < T)
            break;

        //�ھӽ�������
        vector<Node*> neighbour = ne.nodes[index]->nei();
        sort(neighbour.begin(),neighbour.end(),[](Node *a, Node *b){return a->degree()<b->degree();});
        for(auto i:neighbour)
        {
            //cout<<i->getFlag()<<"   "<<i->strategies<<endl;
            if(flag[i->getFlag()] == false)
            {
                flag[i->getFlag()] = true;
                if(i->degree() <= Deg_threshold)
                    ready2Vacc.push_back(i->getFlag());
                else
                    bigDegList.push_back(i->getFlag());
            }

        }
    }
    cout<<"---------stage 2-----------"<<endl;
    for(int i=0;i<vacc_vec.size();i++)
    {
        int t = vacc_vec[i];
        for(int j=i+1;j<vacc_vec.size();j++)
        {
            if(ne.nodes[vacc_vec[j]]->degree() < ne.nodes[t]->degree())
                swap(vacc_vec[i], vacc_vec[j]);
        }
    }
    for(auto it = vacc_vec.rbegin();it!=vacc_vec.rend();)
    {
        Node *n = ne.nodes[*it];
        n->strategies = 1;
        cout<<"delete flag:  "<<n->getFlag()<<endl;
        double l = Tool::getMaxEigen(ne.nodes);
        if(l==-1)
            l = lastl;
        lastl = l;
        //��ȥ���ֽڵ�֮������ֵ����T�������½��ָýڵ�
        if(l > T)
        {
            cout<<"add flag:  "<<n->getFlag()<<endl;
            n->strategies = 0;
            it++;
        }
        else
        {
            auto it2 = vacc_vec.erase((++it).base());
            vector<int>::reverse_iterator it3(it2);
            it = it3;
        }
        cout<<"<<stage 2>>   num:  "<<vacc_vec.size()<<"\tmaxeigenV:  "<<l<<endl;
    }
    return vacc_vec.size();
}
/*
���ܺ���
*/
vector<int> maxDeg(const NE &ne, vector<int> vec)
{
    vector<int> maxdegree(2,-100);            //����,��
    for(auto index:vec)
    {
        int degree = ne.nodes[index]->degree();
        if(degree>maxdegree[1])
        {
            maxdegree[0] = index;
            maxdegree[1] = degree;
        }
    }
    return maxdegree;
}
vector<int> minDeg(const NE &ne, vector<int> vec)
{
    vector<int> mindegree(2,100000);            //����,��
    for(auto index:vec)
    {
        int degree = ne.nodes[index]->degree();
        if(degree<mindegree[1])
        {
            mindegree[0] = index;
            mindegree[1] = degree;
        }
    }
    return mindegree;
}
//----------------------------------------------------------------------


//-------------------------
/*
�������������и��嶼Ϊ����״̬���Ӷ����Ľڵ㿪ʼ������ȱ������жϽڵ��Ƿ���Ҫ�ı����
*/
void DFS(vector<Node*> nodes, int n, vector<bool> &flag, double T);
bool ifAllSelected(vector<bool> flag);
int DeepMethod(NE &ne,  double T)
{
    int size = ECgame::size;
    for(auto i:ne.nodes)
        i->strategies = 0;
    vector<int> Allindex;
    for(int i=0;i<size;i++)
        Allindex.push_back(i);
    int maxDegree_index = maxDeg(ne, Allindex)[0];
    vector<bool> flag(size, false);
    while(!ifAllSelected(flag))
        DFS(ne.nodes, maxDegree_index, flag, T);
    int num = count_if(ne.nodes.begin(),ne.nodes.end(),[](Node* n1){return n1->strategies == 0;});
    cout<<"<<stage 2>>   num:  "<<num<<"\tmaxeigenV:  "<<T<<endl;
    return num;
}
void DFS(vector<Node*> nodes, int n, vector<bool> &flag, double T)
{
    if(flag[n] == true)
        return;
    //cout<<"delete_vacc flag:  "<<n<<endl;
    flag[n] = true;
    nodes[n]->strategies = 1;
    double l = Tool::getMaxEigen(nodes);
    if(l>T)
    {
        nodes[n]->strategies = 0;
        //cout<<"vacc flag:  "<<n<<endl;
    }
    vector<Node*> vec = nodes[n]->nei();
    sort(vec.begin(),vec.end(),[](Node* n1, Node* n2){return n1->degree()>n2->degree();});
    for(auto i:vec)
        DFS(nodes, i->getFlag(), flag, T);
}
bool ifAllSelected(vector<bool> flag)
{
    for(auto i:flag)
    {
        if(i==false)
            return false;
    }
    return true;
}
//----------------------------------------------------------------------
/*
�������������и��嶼Ϊ����״̬��Ȼ��ѡ������ĵ㿪ʼ�������������
*/
int BreadthMethod2(NE &ne,  double T)
{
    cout<<"--------------------"<<T<<"------------------------"<<endl;
    ne.init();
    int size = ECgame::size;
    for(auto i:ne.nodes)
        i->strategies = 0;
    vector<int> temp_degree(size, 0);

    for(int times = 0;times<size;times++)
    {
        //��Ŀ��ڵ�
        vector<int>::iterator max_index_iter = max_element(temp_degree.begin(),temp_degree.end());
        vector<int> maxindex_vec;
        for(int i=0;i<temp_degree.size();i++)
        {
            if(temp_degree[i] == *max_index_iter)
                maxindex_vec.push_back(i);
        }
        //�Ҷ����Ľڵ�
        int target_index = maxDeg(ne, maxindex_vec)[0];
        //cout<<"target_index:   "<<target_index<<endl;
        temp_degree[target_index] = -(size+1);           //��Ϊ�����������ٱ�ѡ��
        ne.nodes[target_index]->strategies = 1;
        double l = Tool::getMaxEigen(ne.nodes);
        if(l > T)
            ne.nodes[target_index]->strategies = 0;
        else
        {
            cout<<target_index<<endl;
            for(auto i:ne.nodes[target_index]->nei())
                temp_degree[i->getFlag()] ++;
        }
    }
    int num = count_if(ne.nodes.begin(),ne.nodes.end(),[](Node* n1){return n1->strategies == 0;});
    return num;
}


