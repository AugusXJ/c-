#include "main.h"

vector<vector<int>> createMatrix(const vector<CNode> &nodeVec, const vector<CLink> &linkVec);       //�����������
void PrintDistance(const vector<vector<int>> &distance);                                            //����������
void BrushMinDistance(vector<CNode> &nodeVec, const vector<CLink> &linkVec);                        //ˢ��ÿ���㵽C15����̾���
void PrintRoute(const vector<CNode> &nodeVec);                                                      //���ÿ���㵽C15��̾��뾭���ĵ�

extern map<string, int> dict;
extern map<int, string> revDict;
