#include "main.h"

vector<vector<int>> createMatrix(const vector<CNode> &nodeVec, const vector<CLink> &linkVec);       //�����������
void PrintRoute(const vector<CNode> &nodeVec, const string &target);                                           //����������
void BrushMinDistance(vector<CNode> &nodeVec, const vector<CLink> &linkVec);                        //ˢ��ÿ���㵽C15����̾���
void PrintRoute(const vector<CNode> &nodeVec);                                                      //���ÿ���㵽C15��̾��뾭���ĵ�
void ChooseCargonRoute(vector<CNode> &nodeVec, const vector<CLink> &linkVec);

extern map<string, int> dict;
extern map<int, string> revDict;
extern map<string, int> pointCityMap;
extern map<int, string> re_pointCityMap;
