#pragma once

//���п��Ա�ѡ���Լ�ϸ�ֺ���ӵ�IndexArray��Ԫ�ػ���
class ElementBase
{
public:
	//��ǵ�ǰԪ���Ƿ�ѡ��
	bool isSelected;
	//��ǵ�ǰԪ���Ƿ���һ����ʱ��������
	bool isIn;
	//��ǵ�ǰ��Ԫ���Ƿ��ھֲ�ϸ���б�����
	bool isSub;
	//��ǵ�ǰԪ����IndexArray�е��±�
	size_t index;

public:
	ElementBase(void);

public:
	virtual ~ElementBase(void);
};