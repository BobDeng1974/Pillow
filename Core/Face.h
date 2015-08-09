#pragma once
#include <vector>
#include "Edge.h"
#include "SubdivideFace.h"

//��������ԣ����ڴ洢���ļ�
struct FaceInfo
{
	size_t index;
	size_t edgeCount;
	float nx;
	float ny;
	float nz;
};

//����
class Face : public ElementBase
{
	//����Object�����ֱ�Ӳ���
	friend class Object;
public:
	//��������ı��б�����ϵ˳ʱ��˳�����С�����ߵĳ�������˳ʱ��˳��һ����Ϊ��������Ϊ��
	//Ҳ���Ǳ��������������Ǹ������ұߵ���������
	std::vector<int> edge;
	//��������ķ��߷���
	Vector normal;

private:
	//����һ��ϸ���д�����е���
	size_t center;
	//���������һ��ϸ�������ɵ���������
	std::vector<int> subdivideFace;

public:
	Face(void);
	//�õ�ָ���ı��б��е�Ԫ��
	const int& operator [](size_t i);
	//�����������������ԣ����ڴ洢���ļ�
	struct FaceInfo getFaceInfo();

public:
	~Face(void);
};