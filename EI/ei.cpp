
/*
----------------------------------------------------------------���˵��-------------------------------------------------------
*/


#include"main.h"
#include"DangerScore.h"
#include<vector>
#include<iostream>
#include<cmath>
#include<fstream>
#include"RNG.h"
#include<ctime>


using namespace std;

#define EMPTY (-SIZE-1)
#define MAX 10000000
#define Sq_c 0.002


int *ptr;//���Ŵ�ʱ�ã���ֵΪ����ָ�����ĳһ��ֵ����������һ����ָ����ڵ㣬�����ֵ�ĸ�ֵ��ʾ���ŴصĴ�С
int *state;//��ʾÿһ�������״̬,0ΪS��1ΪV
int ClusterNumber;//��¼�Ŵص�����
double LargeCluster;//��¼����ŴصĴ�С
double AverCluster;//��¼�Ŵص�ƽ����С

int changeSize;

void initialCluster()
{
    ptr=new int[SIZE];
    state=new int[SIZE];
    for(int i=0;i<SIZE;i++)
    {
        ptr[i]=EMPTY;
        state[i]=1;
    }
}

void deleteCluster()
{
    delete []ptr;
    delete []state;
    delete []score;
}

int findRoot(int i)
{
    if(ptr[i]<0&&ptr[i]!=EMPTY)   return i;       //���i��ֵС��0����ôi���Ǹôصĸ��ڵ�
    else
        findRoot(ptr[i]);       //���i��ֵ����0��ptr[i]���Ǹ��ڵ�
}

/*
�ı����i״̬֮��Դص�Ӱ��
˼�룺����i��V���S�����ɸ���i���Լ�Ϊroot�ȴ���һ���أ�Ȼ�������ھӵĴؽ��кϲ����ϲ���size�����Ǹ��ء�
*/
void changeState(int i)
{
    int r1,r2;
    int s1,s2;
    if(state[i]==1)         //�������i��V���壬�򴴽���
    {
        r1=i;               //�ص�root��i��r1��ʾi�����صĸ��ڵ���
        ptr[i]=-1;
        state[i]=0;         //�ı�״̬
        for(int j=0;j<Player[i].degree;j++)
        {
            int playerj=Player[i].neighbours[j];
            if(ptr[playerj]!=EMPTY)
            {
                r2=findRoot(playerj);
                if(r2!=r1)                  //��������ز�һ��������кϲ�
                {
                    if(ptr[r1]>ptr[r2])     //���r1��r2С����ϲ���r2�����Ĵ���ȥ
                    {
                        ptr[r2]+=ptr[r1];
                        ptr[r1]=r2;
                        r1 = r2;
                    }
                    else                    //���r1��r2��r2�ϲ���r1��ȥ
                    {
                        ptr[r1]+=ptr[r2];
                        ptr[r2]=r1;
                    }
                }
            }
        }

    }
}
//
///*
//������еĴ�����
//*/
//int clusterNumber()
//{
//    ClusterNumber=0;
//    for(int i=0;i<SIZE;i++)
//    {
//        if(ptr[i]<0&&ptr[i]!=EMPTY)
//        {
//            ClusterNumber++;
//        }
//    }
//    return ClusterNumber;
//}

/*
�ҳ������е����صĸ��ڵ�
*/
int maxCluster()
{
    int *flag=new int[SIZE];
    for(int i=0;i<SIZE;i++)
    {
        flag[i]=0;
    }
    int max=-1;
    int k=-1;      //���ظ��ڵ������
    for(int i=0;i<SIZE;i++)
    {
        if(ptr[i]<0&&ptr[i]!=EMPTY)         //�ҵ����ڵ�i
        {
            int r=findRoot(i);              //i�Ѿ��Ǹ��ڵ��ˣ�����r=i
            if(flag[r]==0)
            {
                flag[r]=1;

                if(abs(ptr[r])>max)
                {
                    max=abs(ptr[r]);
                    k=r;
                }
            }
        }
    }
    if(k==-1)  cout<<"�����ص�ʱ�������в����ڴأ���һ�γ���������"<<endl;
    delete []flag;
    return k;
}

/*
�ҳ��ڵ�i�����дصĸ��ڵ�
*/
vector<int> N_i(int playeri)
{

    //�ҳ��ھӴ������и��ڵ�
    vector<int> N(0);
    int *temp=new int[SIZE];
    for(int i=0;i<SIZE;i++)
    {
        temp[i]=0;
    }
    for(int j=0;j<Player[playeri].degree;j++)
    {
        int playerj=Player[playeri].neighbours[j];
        if(state[playerj]==0)
        {
            int r2=findRoot(playerj);
			if (temp[r2] == 0)
			{
				N.push_back(r2);
				temp[r2] = 1;
			}
        }

    }
    delete []temp;
    return N;
}

/*
�ҳ��ڵ�i�ھ��еĵڶ���صĸ��ڵ�
*/
int C_2(int playeri)
{
    vector<int> N=N_i(playeri);
    if(N.size()<2)
        cout<<"C2 ��ڵ�i���ھӴ�����"<<endl;

    //�ҵ����غ͵ڶ���Ĵ�
    for(int i=0;i<2;i++)
    {
        int k=i;
        for(int j=i+1;j<N.size();j++)
        {

            if(ptr[N[j]]<ptr[N[i]])         //�ߴ�Խ��ptrԽС
                k=j;
        }
        int temp=N[i];
        N[i]=N[k];
        N[k]=temp;
    }
    return N[1];

}

/*
�������playeri��\sigma 1 (����û�г�ʼ��ÿ�������danger score)
*/
double sigma1(int playeri, bool ifHaveVinfo)
{

    //��һ�����ǽڵ����ͨ��Ϣ
    int k1=score[playeri];      //����i��dangerscore

    //�ڶ������ǽڵ�Դص�Ӱ��
    double k2=0;
    vector<int> N=N_i(playeri);
    for(int i=0;i<N.size();i++)
    {
        k2+=(sqrt(abs(ptr[N[i]]))-1);
    }


    int k3=0;


    return k1+k2+k3;
}


/*
�������i��\sigma 2
*/
double sigma2(int playeri, bool ifHaveVinfo,int maxC)
{
    //�ҳ��ھӴ������и��ڵ�
    vector<int> N=N_i(playeri);

    //���i�ھӴ��в��������ص����
    int flag=0;
    for(int i=0;i<N.size();i++)
    {
        if(N[i]==maxC)
        {
            flag=1;
        }
    }
    if(flag==0)
        return MAX;

    //���������giant component
    return N.size();
}

///*
//ͨ��EI���в���������
//*/
//void SubsidyByEi(bool ifHaveVinfo)
//{
//    for(int i=0;i<SIZE;i++)
//    {
//        Player[i].label=false;
//    }
//
//    ofstream outfile;
//
//    outfile.open("EI�����Ķ���.csv");
//
//
//    //��ʼ��ʱ���и���״̬ΪV�������ڴ�
//    initialCluster();
//
//    int changeSize=0;       //�ı������
//
//    DangerScore();          //����ÿ������sigma1��ǰ�벿��
//
//
//    vector<double> s(SIZE,0);
//    //��ʼ����
//    while(changeSize<SIZE-subsidyNum)
//    {
//        double q=((SIZE-changeSize)*1.0)/SIZE;
//        //��ʼ��
//        for(int i=0;i<SIZE;i++)
//            s[i]=0;
//        //����ÿ�������ֵ
//        for(int i=0;i<SIZE;i++)
//        {
//            if(state[i]==1)
//            {
//                if(q>q_c)
//                {
//                    double score=sigma1(i,ifHaveVinfo);
//                    s[i]=score;
//                }
//                else
//                    s[i]=sigma2(i,ifHaveVinfo);
//            }
//            else
//                s[i]=MAX;
//        }
//
//
//        //�ҳ����и����е���Сֵ
//        double min=MAX;
//        int k;              //��Сֵ������
//        for(int i=0;i<SIZE;i++)
//        {
//            if(state[i]==1&&s[i]<min)
//            {
//                min=s[i];
//                k=i;
//            }
//        }
//
//        //��ʹ��\sigmal2ʱ���������ͬ����С��������ô����Щ��С������һ������
//        if(q<=q_c)
//        {
//            vector<int> N(0);               //N�д�ŷ���Ϊ��Сֵ����Щ������
//            for(int i=0;i<SIZE;i++)
//            {
//                if(s[i]==min)
//                {
//                    N.push_back(i);
//                }
//            }
//            if(N.size()==0)
//                cout<<"chucuo"<<endl;
//            else if(N.size()>1)              //�����С�ھӴظ����� �ڵ㲻Ψһ����������ǵڶ���صĴ�С��ѡȡС��
//            {
//                //���ȼ��N�еĸ�����ھӴش�С�Ƿ�Ϊ1����Ϊ1��Ϊ����Ǹ��أ�������Щ�������ѡһ��
//                vector<int> tempN=N_i(N[0]);
//                if(tempN.size()==1)
//                    k=N[randi(N.size())];
//                else
//                {
//                    //����������ÿ���ڵ���ھӴض�������2��
//                    int minC2=MAX;
//                    for(int i=0;i<N.size();i++)
//                    {
//
//
//                        int r=C_2(N[i]);
//                        if(abs(ptr[r])<minC2)
//                            k=N[i];
//                    }
//                }
//
//
//            }
//        }
//
//
//        ofstream outfilea;
//        outfilea.open("test.txt",ios::app);
//        outfilea<<"�ı�֮�󣬸ı������Ϊ: "<<changeSize+1<<endl;
//        outfilea.close();
//        //�ı�k��״̬
//        changeState(k);
//        changeSize++;
//    }
//
//    //��ʣ�µ���Щ������н���
//    for(int i=0;i<SIZE;i++)
//    {
//        if(state[i]==1)
//        {
//            Player[i].label=true;
//            outfile<<i<<","<<Player[i].degree<<endl;
//        }
//
//    }
//
//    outfile.close();
//}

double S_q(int maxC)
{
    return (abs(ptr[maxC])*1.0)/SIZE;
}

void testEI()
{
    ofstream outfile;
    outfile.open("S(q).txt");
//    ofstream outfiletest;
//    outfiletest.open("test.txt");
    clock_t sta=clock();

    int CandidateNum=20;           //��ѡ�ڵ����
    //��ʼ��ʱ���и���״̬ΪV�������ڴ�
    initialCluster();

    changeSize=0;       //�ı������

    DangerScore();          //����ÿ������sigma1��ǰ�벿��
    clock_t end_dangerScore=clock();
    double dur=(double)(end_dangerScore - sta);
    cout<<"���DangerScore�� "<<dur/CLOCKS_PER_SEC<<endl;

    vector<double> s(CandidateNum,0);           //��ź�ѡ�ڵ��������ķ���
    vector<int> cand(CandidateNum);

    double Sq=0;

    while(changeSize<SIZE)
    {
        double q=((SIZE-changeSize)*1.0)/SIZE;

        //�ҳ�����
        int maxC=maxCluster();
        //ѡ����ѡ�ڵ�
        //�����ж�ʣ�µ�V�ڵ��ǲ��Ǵ��ں�ѡ�ڵ�
        bool label=true;
        int sum=0;
        if(changeSize>=SIZE-CandidateNum)
        {
            label=false;
            sum=SIZE-changeSize;
        }

        //��ʼ��ڵ�
        int num=0;
        vector<bool> flag(SIZE,false);
        if(label==false)            //���ʣ��ڵ����С�ں�ѡ�ڵ��������ʣ��ڵ����
        {
            CandidateNum=sum;
            s.resize(sum,0);
            cand.resize(sum);
            for(int i=0;i<SIZE;i++)         //�ڵ����
            {
                if(state[i]==1)
                {
                    cand[num]=i;
                    num++;
                }
            }
        }
        else
        {
            while(num<CandidateNum)
            {
                int Candidate=randi(SIZE);
                if(flag[Candidate]==false&&state[Candidate]==1)
                {
                    cand[num]=Candidate;
                    flag[Candidate]=true;
                    num++;
                }
            }
        }

        //����ѡ�е���Щ�����ֵ
        for(int i=0;i<CandidateNum;i++)
        {
            if(state[cand[i]]==1)
            {
                if(Sq<Sq_c)
                {
                    double score=sigma1(cand[i],false);
                    s[i]=score;
                }
				else
				{
					s[i]=sigma2(cand[i],false,maxC);         //���������صľ�ΪMAX������Ϊ�ھӴصĸ���
				}

            }
            else
                s[i]=MAX;
        }


        //�ҳ����и����е���Сֵ
        double min=MAX;
        int k;              //��Сֵ������
        for(int i=0;i<CandidateNum;i++)
        {
            if(state[cand[i]]==1&&s[i]<min)
            {
                min=s[i];
                k=cand[i];
            }
        }

        //��ʹ��\sigmal2ʱ���������ͬ����С��������ô����Щ��С������һ������
        if(Sq>=Sq_c)
        {
            vector<int> N(0);               //N�д�ŷ���Ϊ��Сֵ����Щ������
            for(int i=0;i<CandidateNum;i++)
            {
                if(s[i]==min)
                {
                    N.push_back(cand[i]);
                }
            }
            if(N.size()==0)
                cout<<"chucuo"<<endl;
            else if(N.size()>1)              //�����С�ھӴظ����� �ڵ㲻Ψһ����������ǵڶ���صĴ�С��ѡȡС��
            {
                //�����СֵΪMAX����ô�����������1�����и�����ھӴ��ж�����������  2 ���и��嶼�������ھӴ�
                //����������¶��������ѡ��
				if (min == MAX)
				{
					k=N[randi(N.size())];
					cout << "min == MAX" << endl;
				}
				else if (min == 1)     //min==1 ʱ�����ڽڵ�ֻ��һ���ھӴأ����أ�����ʱ|Ni|=1�����ʱ��C2�����ڣ�Ҫ���⴦��
				{
					k=N[randi(N.size())];
					cout << "min == 1" << endl;
				}
                else
                {
                    //����������ÿ���ڵ���ھӴض�������2��
					//��ʱN����ѵĵ�ȡ���ڵڶ����
                    int minC2=MAX;
                    for(int i=0;i<N.size();i++)
                    {
                        int r=C_2(N[i]);
                        if(abs(ptr[r])<minC2)
                            k=N[i];
                    }
                }
            }
        }
        if(changeSize==750)
            cout<<endl;

        //���ҵ�Ҫ�ı�״̬�Ľڵ�k
//        outfiletest<<"�Ѹı�Ľڵ������ "<<changeSize<<endl;
//        outfiletest<<"Ҫ�ı�Ľڵ㣺 "<<k<<endl;
//        outfiletest<<"------------�ı�ǰ-------------"<<endl;
//        outfiletest<<"ptr[k]: "<<ptr[k]<<endl;
//        outfiletest<<"state[k]: "<<state[k]<<endl;

        changeState(k);

//        outfiletest<<"------------�ı��-------------"<<endl;
//        outfiletest<<"ptr[k]: "<<ptr[k]<<endl;
//        outfiletest<<"state[k]: "<<state[k]<<endl;
//        if(ptr[k]>0)
//        {
//            outfiletest<<"�ϲ���������"<<"�ôظ��ڵ�Ϊ"<<findRoot(k)<<"   �Ҹôش�СΪ: "<<ptr[findRoot(k)]<<endl;
//        }
//        outfiletest<<"���صĸ��ڵ㣺 "<<maxCluster()<<"   ���صĴ�С"<<abs(ptr[maxCluster()])<<endl;
//        outfiletest<<endl;
        changeSize++;

        //����Sq
        Sq=S_q(maxC);
        if(changeSize == 1)
            Sq = 0;
        outfile<<q<<" "<<Sq<<endl;

        clock_t end_onetime=clock();
        double dur=(double)(end_onetime-end_dangerScore );
        cout<<"���һ������ɵĸ���Ϊ��"<<changeSize<<"��ʹ�õ�ʱ�䣺 "<<dur/CLOCKS_PER_SEC<<endl;

    }

    clock_t end_EI=clock();
    dur=(double)(end_EI-end_dangerScore );
    cout<<"���EI�� "<<dur/CLOCKS_PER_SEC<<endl;

    deleteCluster();
    outfile.close();
}





