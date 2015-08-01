#pragma once
#include "SubdivideEdge.h"

//����ߵ����ԣ����ڴ洢���ļ�
struct EdgeInfo
{
	size_t index;
	size_t start;
	size_t end;
	size_t left;
	size_t right;
};

//����
class Edge : public SubdivideEdge
{
public:
	//�ߵĿ�¡�߱�ţ�������������ߵĿ�¡
	int clone;

public:
	Edge(void);
	//theStart�ߵ���ʼ�� theEnd�ߵ��յ�
	//�ߵķ����Ǵӱߵ���ʼ��ָ���յ�
	Edge(int theStart,int theEnd);
	//�õ��ߵ��������ԣ����ڴ洢���ļ�
	struct EdgeInfo getEdgeInfo();

public:
	~Edge(void);
};