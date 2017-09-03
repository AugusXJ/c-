#include "main.h"
#include "distance.h"

using namespace std;


double GetCost(vector<CNode> &nodeVec, vector<CLink> temp_linkVec, deque<size_t> greedyResult)
{
    if(greedyResult.size() == 0)
        cerr << "Greedy ����" <<endl;

    size_t currentDist = 0;
    vector<double> logistCost(nodeVec.size(), 0);          //����ÿ�����еĽ��
    for(auto i = nodeVec.begin(); i!= nodeVec.end() ; i++)
        i->m_logistCost = 0;

    ChooseCargonRoute(nodeVec, temp_linkVec);                //��ʼʱ�����·��
    size_t change = temp_linkVec[greedyResult[0]].m_distance;       //���иı�ʱ���ֵ
    while(currentDist < g_allDist)
    {
        if(currentDist == change)
        {
            size_t target = greedyResult[0];
            greedyResult.pop_front();
            temp_linkVec[target].m_ifAvailable = true;
            ChooseCargonRoute(nodeVec, temp_linkVec);
            if(greedyResult.size())
                change += temp_linkVec[greedyResult[0]].m_distance;
            else
                change = 1000000;
        }
        int index = 0;
        for(auto i = nodeVec.begin(); i!= nodeVec.end(); i++)
        {
            if(i->m_ifTransfer ==  true)
                logistCost[index] += (i->m_cargoNum / (g_allDist/10)) * i->m_cargonDistance * 5 * 1000;
            else
                logistCost[index] += (i->m_cargoNum / (g_allDist/10)) * i->m_cargonDistance * 10 * 1000;
            i->m_logistCost = logistCost[index];
            index++;
        }
        currentDist += 1;
    }
    return accumulate(logistCost.begin(), logistCost.end(), 0.0);
}


/*
̰���㷨�����޽���˳��
*/
deque<size_t> Greedy(vector<CNode> nodeVec, vector<CLink> linkVec)
{
    deque<size_t> greedyResult;

    //������Ҫ�޽�������·
    size_t sum = count_if(linkVec.begin(), linkVec.end(),
                          [](const CLink &n) -> bool{return  n.m_ifAvailable == false;});

    for(size_t i=0; i<sum; i++)
    {
        //����һ��linkVec
        vector<CLink> temp_linkVec(linkVec);
        size_t temp_link;                             //��¼Ҫѡ�������
        vector<pair<size_t, double>> cost;           //��¼ÿ�������cost
        for(size_t j=0; j<linkVec.size(); j++)
        {
            if(temp_linkVec[j].m_ifAvailable == false &&
                    find(greedyResult.begin(),greedyResult.end(),j) == greedyResult.end())
            {
                greedyResult.push_back(j);
                cost.push_back(make_pair(j, GetCost(nodeVec, temp_linkVec, greedyResult)));
                greedyResult.pop_back();
            }
        }
        //ѡ����С��cost
        sort(cost.begin(), cost.end(),
             [](const pair<size_t, double> &s1, const pair<size_t, double> &s2)
        {
            return s1.second < s2.second;
        });
        temp_link = cost[0].first;      //�ҵ���С������
        greedyResult.push_back(temp_link);
    }
    return greedyResult;
}
