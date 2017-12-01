
/*
-----------------------------------------------------------���˵��-------------------------------------------------------------
��ʽ��             k_i^eff=k_i-L_i-M_i({k_j^eff})  ���������

����˵����
k_i^eff:            �ڵ�i�ķ���
k_i:                �ڵ�i�Ķ�
L_i:                �ڵ�i�ھ���Ҷ�ӽڵ�ĸ���
M_i({k_j^eff}):     �ڵ�i���ھ���hub�ڵ�ĸ������жϱ�׼����


M�жϱ�׼��         ����һ����ֵcutoff K��һ�������ȡK=6������ڵ�i���ھ�j��������K����λhub�ڵ�

�㷨˼·��          ʽ�ӹ���Ϊ�������֣��ȼ����һ���ֺ͵ڶ����֣�����������һ����ֵ��Ȼ��ͨ�������ķ�������������֡�

                    key:        �趨һ������key��������з�����ֵ���ٸı䣬�����з�����������ҽ��ñ�����0������Ϊ1��ÿ�ε���������0

                    v[SIZE]:    ��ÿһ���ڵ����趨һ������v[SIZE]�������Ҫ��������1��������0��ÿ�ε�����������Ϊ0

                    ����������   keyΪ1







-----------------------------------------------------------���˵��-------------------------------------------------------------

*/


#include"main.h"
#include<fstream>
#include <vector>
#include <iostream>

using namespace std;

#define cutoff 6

int *score;
int *fixScore;                                     //���湫ʽ���������
vector<int> v;                                            //�ж�ÿ������ķ����Ƿ񱻸ı�
int key;                                              //�Ƿ�ﵽ�ȶ�״̬��1��ʾ���ı�



//----------------------------------------------------------����score����----------------------------------------------------------


/*
��ʼ��ÿ������ķ���������ȷ������߹̶�����
*/
void initialScore()
{
    fixScore=new int[SIZE];
    for(int i=0;i<SIZE;i++)                             //��ʼ������
    {
        int l=0;                                        //�ڵ�i�ھ���Ҷ�ӽڵ�ĸ���
        for(int j=0;j<Player[i].degree;j++)             //�����ھӽڵ�ĸ���
        {
            int k=Player[i].neighbours[j];              //�ھӽڵ�
            if(Player[k].degree==1)
                l++;
        }

        fixScore[i]=Player[i].degree-l;                    //ǰ�����ֵĽ��
    }
}

/*
�ı�ڵ�i�ھӵı��vֵ
*/
void changeV(int i)
{
    for(int j=0;j<Player[i].degree;j++)
    {
        int k=Player[i].neighbours[j];
        if(v[k]!=1)
            v[k]=1;
    }
}

/*
���½ڵ�i�ķ���
*/
void renewScore(int i)
{
    int M=0;
    for(int j=0;j<Player[i].degree;j++)                 //�����ھ���M������
    {
        int k=Player[i].neighbours[j];       //��j���ھ�

        //����ھ�k�ķ������ڽ�ֹ��������Ϊhub
        if(score[k]>cutoff)
        {
            M++;
        }
    }
    score[i]=fixScore[i]-M;
}


void DangerScore()
{
    score=new int[SIZE];
    fixScore=new int[SIZE];
	v.resize(SIZE);

    for(int i=0;i<SIZE;i++)
    {
        v[i]=1;
        score[i]=0;
    }
                                        //��ʼ��ÿ�����嶼�Ǵ��ı��
    key=1;

    initialScore();                                     //���㹫ʽ���������ֵ�ֵ

    //score=fixScore;                                     //��ʼ����Ϊ������
    while(key==1)
    {
        for(int i=0;i<SIZE;i++)
        {
            if(v[i]==1)                                 //����ø����Ǵ��ı�ĸ���
            {
                v[i]=0;
                int oldScore=score[i];                  //������������ڸı���ԭ�����ıȽ�
                renewScore(i);                          //�ı�i�ķ���

                if(score[i]!=oldScore)
                {
                    changeV(i);                         //�ı�i�ھӵı��
                }

            }
        }
		key = 0;                                      //key��0����Ϊ�ȶ�״̬
        for(int i=0;i<SIZE;i++)
        {

            //������ڸ�����ı䣬��Ϊ���ȶ�״̬
            if(v[i]==1)
                key=1;
        }
    }
    delete []fixScore;
}


//----------------------------------------------------------����score����----------------------------------------------------------





//------------------------------------------------------------------���򲿷�-----------------------------------------------------------

struct AgentSc
{
    int score;
    int index;
};

void SelectSortSc(AgentSc *sc)
{
    AgentSc temp;
    for(int i=0;i<SIZE;i++)
    {
        int k=i;
        for(int j=i+1;j<SIZE;j++)
        {
            if(sc[j].score>sc[k].score)
            {
                k=j;
            }
        }

        temp=sc[i];
        sc[i]=sc[k];
        sc[k]=temp;
    }
}


