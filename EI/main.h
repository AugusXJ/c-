#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include<vector>
using namespace std;
                                                           //Scale-Free Networks�ĺ궨��
#define SIZE  15                                           //�ڵ���
#define K 4                                                     //ƽ����,����Ϊż��
#define INI_NODES  3                                           //��ʼ�ڵ���,kΪ4��Ϊ2��



typedef struct Agent
{
    int degree; //����Ķ�
    int *neighbours;//������ھ�
}Agent;

extern Agent *Player;


#endif // MAIN_H_INCLUDED
