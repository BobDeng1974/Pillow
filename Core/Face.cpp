#include "Face.h"

//��ʼ���޷���
Face::Face(void):ElementBase(),center(0),normal(0)
{
	//�ٶ����ͨ������ĿС��5
	edge.reserve(5);
}

//����ָ���ı��б�Ԫ��
const int& Face::operator [](size_t i)
{
	return edge[i];
}

//�õ������Ϣ,���ڴ洢���ļ�
struct FaceInfo Face::getFaceInfo()
{
	struct FaceInfo result;
	result.index=index;
	result.edgeCount=edge.size();
	result.nx=normal.x;
	result.ny=normal.y;
	result.nz=normal.z;
	return result;
}

Face::~Face(void)
{
}