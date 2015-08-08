#pragma once
#include "Global.h"
#include "SplitedView.h"
#include <time.h>

class SingleView:public SplitedView
{
public:
    SingleView(unsigned int splitX,unsigned int splitY,unsigned int width,unsigned int height);
	
	CameraMode::__Enum setView(size_t index)
	{
		index;
		camera[0]->setCamera();
		return camera[0]->type._value;
		//camera[0]->setCameraForSelectionS();
	};

	bool onPanPress(size_t x,size_t y)
	{
		//����Ҫ�ж�һ��������ĸ�������
		camera[selected]->onPanPress(x,y);
		return true;
	};

	bool onPanDrag(size_t x,size_t y)
	{
		//����Ҫ�ж�һ�µ�ǰѡ���pan����
		camera[selected]->pan(x,y);
		return true;
	};

	void onWheel(float step,size_t x,size_t y)
	{
		x;
		y;
		//����Ҫ�ж�һ��������ĸ�������
		camera[selected]->zoom(step);
	};

	bool onRotateDrag(size_t x,size_t y)
	{
		camera[selected]->rotate(x,y);
		return true;
	};

	bool onRotatePress(size_t x,size_t y)
	{
		//����Ҫ�ж����λ��
		camera[selected]->onRotatePress(x,y);
		return true;
	};

	bool onCtrlPress(size_t x,size_t y)
	{
		isCtrlMode=true;
		ctrlSX=x;
		ctrlSY=y;
		return true;
	};

	bool onCtrlRelease()
	{
		if(isCtrlMode)
		{
			isCtrlMode=false;
			ctrlSX=0;
			ctrlSY=0;
			return true;
		}else 
			return false;
	};

	bool onCtrlDrag(size_t x,size_t y)
	{
		if(isCtrlMode)
		{
			camera[selected]->setCamera();
			Vector horizontalDir(camera[selected]->getHorizontalDir());
			theScene->ctrlDrag(horizontalDir,camera[selected]->up,x-ctrlSX,y-ctrlSY,isExtrude);
			isExtrude=false;
			ctrlSX=x;
			ctrlSY=y;
			return true;
		}
		else 
			return false;
	};

	bool onRotateRelease()
	{
			camera[selected]->onRotateRelease();
			return true;
	};
	
	bool onPanRelease()
	{
		camera[selected]->onPanRelease(0,0);
		return true;
	}

	void update(size_t theSplitX,size_t theSplitY,size_t theWidth,size_t theHeight)
	{
		splitX=theSplitX;
		splitY=theSplitY;
		width=theWidth;
		height=theHeight;
		camera[0]->updateSize(0.0f,0.0f,(float)width,(float)height);
	};

	bool onSelectionPress(size_t x,size_t y)
	{
		isSelectionMode=true;
		selectionSX=x;
		selectionSY=y;
		selectionEX=x;
		selectionEY=y;
		return true;
	};

	bool onSelectionDrag(size_t x,size_t y)
	{
		if(isSelectionMode)
		{
			selectionEX=x;
			selectionEY=y;
			return true;
		}
		else
			return false;
	};

	bool onSingleSideSelectionRelease(bool isAppend)
	{
		if(isSelectionMode)
		{
            qDebug() << "single selection mode =";
			size_t x1=(selectionSX>selectionEX)?selectionEX:selectionSX;
			size_t y1=(selectionSY>selectionEY)?selectionEY:selectionSY;
			size_t x2=(selectionSX>selectionEX)?selectionSX:selectionEX;
			size_t y2=(selectionSY>selectionEY)?selectionSY:selectionEY;
			camera[selected]->setCameraForSelectionS();
			theScene->selectSingleSide(x1,y1,x2,y2,height,isAppend);
			isSelectionMode=false;
			selectionSX=0;
			selectionSY=0;
			selectionEX=0;
			selectionEY=0;
			return true;
		}
		else 
			return false;
	};

	bool onDualSideSelectionRelease(bool isAppend)
	{
		if(isSelectionMode)
		{
			size_t x1=(selectionSX>selectionEX)?selectionEX:selectionSX;
			size_t y1=(selectionSY>selectionEY)?selectionEY:selectionSY;
			size_t x2=(selectionSX>selectionEX)?selectionSX:selectionEX;
			size_t y2=(selectionSY>selectionEY)?selectionSY:selectionEY;
			camera[selected]->setCameraForSelectionD(x1,y1,x2,y2,height);
			theScene->selectDualSide(isAppend);
			isSelectionMode=false;
			selectionSX=0;
			selectionSY=0;
			selectionEX=0;
			selectionEY=0;
			return true;
		}
		else 
			return false;
	};

	bool onAxisDrag(size_t x,size_t y)
	{
		//����Ҫ���������ĵ��
		if(isAxisMode)
		{
			camera[0]->setCamera();
			//�������ǿ��ת��
			Vector m((float)((int)x-(int)axisDragSX),(float)((int)y-(int)axisDragSY),0.0f);
			float work=psVECDOT(cursorDir,m);
			theScene->axisDrag(work,cursorMode,cursorDir.x,cursorDir.y);
			axisDragSX=x;
			axisDragSY=y;
			return true;
		}
		else 
			return false;
	};

	bool onAxisRelease()
	{
		if(isAxisMode)
		{
			isAxisMode=false;
			theScene->axisRelease();
			axisDragSX=0;
			axisDragSY=0;
			return true;
		}
		else
			return false;
	}

	bool onAxisPress(size_t x,size_t y)
	{
		camera[selected]->setCameraForSelectionS();
		cursorDir.z=0;
		bool result=theScene->isAxisSelected(camera[selected]->type._value,camera[selected]->getEye(),height,x,y,cursorDir.x,cursorDir.y,cursorMode);
		if(result)
		{
			axisDragSX=x;
			axisDragSY=y;
			cursorDir.normalize();
			isAxisMode=true;
		}
		return result;		
	};


	void onPaint()
	{
		if(isSelectionMode)
		{
			glEnable(GL_ALPHA_TEST);
			glColor4ub(0,0,255,125);
			glBegin(GL_QUADS);
				glVertex2i(selectionSX,selectionSY);
				glVertex2i(selectionEX,selectionSY);
				glVertex2i(selectionEX,selectionEY);
				glVertex2i(selectionSX,selectionEY);
			glEnd();
			glDisable(GL_ALPHA_TEST);
			glColor3ub(255,255,255);
		}
	};

public:
	~SingleView(void);
};
