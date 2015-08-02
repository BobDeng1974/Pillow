#pragma once
#include<vector>
#include<deque>

//��¼Ԫ���±�Ŀɱ䳤�б�
template<class ElementType> class IndexArray
{
private:
	//�洢�б���Ԫ�ص��б�
	std::vector<ElementType*> theArray;
	//�����ͷſռ�Ķ���
    std::deque<unsigned int> theSpace;

public:
	//���캯�����������б��з�������ݣ���ΪԪ�ص��±������0��ʾ��û����ӵ����飬�������������0��λ����ռ��
	IndexArray(void)
	{
        theArray.push_back(nullptr);
	};

	//����ʼ�ռ����Ĺ��캯��
    IndexArray(unsigned int space)
	{
		theArray.reserve(space+1);
        theArray.push_back(nullptr);
	};

	//��������б�
	void clear()
	{
		//�����б��ڵ�����Ԫ��
        for(unsigned int i=0;i<theArray.size();++i)
		{
			//��鵱ǰ���ʵ���Ԫ���Ƿ��Ѿ����ͷŹ�
			if(theArray[i])
			{
				//���û�б��ͷŹ������ɾ��
				delete theArray[i];
			}
		}
		
		//����б�
		theArray.clear();
		//������0λ���Ͽ�Ԫ��
        theArray.push_back(nullptr);
		//����Ѿ��ͷ�Ԫ�ر�Ŷ���
		theSpace.clear();
	};

	//Ϊ�б�Ԥ���ռ�
    void reserve(unsigned int space)
	{
		theArray.reserve(space);
	};

	//�����ֵԪ��
	void pushNull()
	{
        theArray.push_back(nullptr);
	};

	//���б��ĩβ����һ���յ�Ԫ�ز��������ͷŶ����м�¼
	//����������ڴ��ļ��ж�ȡ��ʱ����������Ѿ�ɾ����Ԫ�ص�ʱ��
	void pushNullS()
	{
		theSpace.push_back(theArray.size());
        theArray.push_back(nullptr);
	};

	//�Բ���ķ�ʽ���һ��Ԫ��
	//ei�ǲ����λ��
	//����������ڱ�֤���Ƶ�һ���ԣ�������add����
	//��������Ҫɾ��һ���棬֮��undo�ָ������theSpace�����¼���������е�λ�ã������ܿ��ܱ��ָ��������Ŀ���λ����������ݲ�һ��
    unsigned int addI(unsigned int ei,ElementType *theElement)
	{
		//���ָ����λ��û��Ԫ��
        if(theArray[ei]==nullptr)
		{
			//���Ѿ�
            for(unsigned int e=0;e<theSpace.size();++e)
			{
				if(theSpace[e]==ei)
				{
					theSpace[e]=theSpace[0];
					theSpace.pop_front();
					theArray[ei]=theElement;
					return ei;
				}
			}
			//���û����theSpace���ҵ���Ӧ�Ŀ����±�
			return 0;	
		}
		else
		{
			//�����ǰλ�ñ�ռ��
			return 0;
		}
	};	

	//ֱ����ĩβ����Ԫ�أ������Ѿ����±��Ԫ�أ��Ҳ�ϣ�������뵽��ǰ����λ�õ�ʱ��
	void directPush(ElementType *theElement)
	{
		theArray.push_back(theElement);
	};

	//���һ���µ�Ԫ��
    unsigned int add(ElementType *theElement)
	{
		//��鵱ǰ�Ƿ��п���λ��
		if(theSpace.empty())
		{
			//�����ǰû�п���λ
			//�õ���������Ԫ�ص�λ��(ĩβ)
            unsigned int tempIndex=theArray.size();
			//ĩβ����Ԫ��
			theArray.push_back(theElement);
			//����Ԫ�صĽű�
			theElement->index=tempIndex;
			//���ز����λ��
			return tempIndex;
		}
		else
		{
			//�õ������׵�һ������λ��
            unsigned int tempIndex=theSpace[0];
			//���������λ������
			theSpace.pop_front();
			//����Ԫ�ص�����λ��
			theArray[tempIndex]=theElement;
			//����Ԫ�صĽű�
			theElement->index=tempIndex;
			//����Ԫ�صĽű�
			return tempIndex;
		}
	};

	//ɾ��һ��Ԫ��
	//������������ͷ�Ԫ�صĿռ䣬��ΪҪ��֤��ӵ���ʷ��¼��Ԫ�ص���ȷ��
    void remove(unsigned int index)
	{
		//���index����0
		if(index)
		{
			//���Ƚ����λ���ÿ�
            theArray[index]= nullptr;
			//�ڿ��ж�����������λ��
			theSpace.push_back(index);
		}
		return;
	};

	//�õ�ָ��λ�õ�Ԫ��
    ElementType* operator [](unsigned int i)
	{
		return theArray[i];
	};

	//�õ�����Ĵ�С�������С�Ǹ�����ֵ���������������ɾ����Ԫ����Ŀ
    unsigned int size()
	{
		return theArray.size();
	};

	~IndexArray(void)
	{
        unsigned int length=theArray.size();
        for(unsigned int i=1;i<length;i++)
		{
			if(theArray[i])
			{
				delete theArray[i];
			}
		}
		theArray.clear();
	};
};
