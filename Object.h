#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "SubdivideLevel.h"
#include "IndexArray.h"
#include "Vertex.h"
#include "Edge.h"
#include "Face.h"

#include <iostream>
#include <string>

#include "Log_VertexPositionChange.h"
#include "Log_VertexNormalChange.h"
#include "Log_VertexAdjacentPush.h"
#include "Log_VertexAdjacentChange.h"
#include "Log_VertexAdjacentPop.h"
#include "Log_VertexAdjacentSwap.h"
#include "Log_VertexAdjacentRemove.h"
#include "Log_VertexAdjacentInsert.h"

#include "Log_EdgeStartChange.h"
#include "Log_EdgeEndChange.h"
#include "Log_EdgeLeftChange.h"
#include "Log_EdgeRightChange.h"

#include "Log_FaceEdgePush.h"
#include "Log_FaceEdgeChange.h"
#include "Log_FaceEdgePop.h"
#include "Log_FaceEdgeSwap.h"
#include "Log_FaceEdgeRemove.h"
#include "Log_FaceEdgeInsert.h"

#include "Log_ObjectPositionChange.h"
#include "Log_ObjectRotationChange.h"
#include "Log_ObjectScaleChange.h"
#include "Log_ObjectColorChange.h"
#include "Log_ObjectVertexAdd.h"
#include "Log_ObjectVertexRemove.h"
#include "Log_ObjectEdgeAdd.h"
#include "Log_ObjectEdgeRemove.h"
#include "Log_ObjectFaceAdd.h"
#include "Log_ObjectFaceRemove.h"
#include "HistoryManager.h"

//��ʷ��¼������
extern HistoryManager *historyManager;

//��Ⱦ����
DECLARE_ENUM(RenderType)
	//���߿�ƽ����Ⱦ
	Wireframe=234,
	//���߿��ƽ����Ⱦ
	WireframeFaced,
	//�߿���Ⱦ
	Wire,
	//���߿�ƽ����Ⱦ
	Smooth,
	//���߿��ƽ����Ⱦ
	Faced
END_ENUM()

//����Գ���
DECLARE_ENUM(MirrorMode)
	MirrorXY=345,
	MirrorYZ,
	MirrorXZ,
	Nothing
END_ENUM()

//�����������,���ڴ洢���ļ�
struct ObjectInfo
{
	size_t index;
	float centerX;
	float centerY;
	float centerZ;
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	float rotationZ;
	float scaleX;
	float scaleY;
	float scaleZ;
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_emission[4];
	GLfloat mat_shininess[4];
	size_t vertexCount;
	size_t edgeCount;
	size_t faceCount;
};

//�����������
class Object : public ElementBase
{
public:
	//���������
	std::string name;
	//���������λ��
	Vector center;
	//����λ��ƫ����
	Vector position;
	//�������תƫ����
	Vector rotation;
	//��������ų߶�
	Vector scale;
	//�Ƿ���Ҫ��Ⱦ��������
	bool isMirror;
	//��������ĶԳ���
	MirrorMode theMirrorMode;
	//�����������ԭ�������ĵ�λ��
	Vector mirrorPosition;
	//�Ƿ�������
	bool isHide;
	//����
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_emission[4];
	GLfloat mat_shininess[4];
	//��Ⱦģʽ
	RenderType renderMode;

private:
	//�����б�
	IndexArray<Vertex> vertexArray;
	//���б�
	IndexArray<Edge> edgeArray;
	//���б�
	IndexArray<Face> faceArray;
	//�ֲ�ϸ���滺����
	std::vector<Face*> PSFaceCache;
	std::vector<SubdivideFace*> PSSubFaceCache[5];

private:
	//ϸ�ֲ��,������5��
	SubdivideLevel *subdivideLevel[5];
	//��ǰ��ϸ�ֲ����Ŀ
	int subdivideLevelSize;
	//��ǰ��ϸ�ֱ��
	int subdivideId;

public:
	Object(char *theName);
	//�����µĶ���,������ӵĵ���
	size_t addVertex(float p1,float p2,float p3);
	size_t addVertex(float p1,float p2,float p3,float n1,float n2,float n3);
	size_t addVertex(Vector &pos);
	size_t addVertex(size_t ei,Vertex *theV);
	size_t addVertex(Vector &pos,Vector &nor);

	//�����µı�,������ӵĵ���
	size_t addEdge(int start,int end);
	//ֱ����ָ����λ������µı�
	size_t addEdge(size_t ei,Edge *theE);

	//�õ�ָ��λ�õĶ���
	Vertex * vertex(size_t index);
	//�õ�ָ��λ�õı�
	Edge * edge(size_t index);
	//�õ�ָ��λ�õ���
	Face * face(size_t index);

	//���һ����,������ӵ���ı��
	size_t addFace(size_t theEdgeArray[],size_t size);
	//ֱ�����һ����
	size_t addFace(size_t ei,Face *theF);

	//���ļ������obj��ʽ,���ڲ���
	void testOut(char *fileName);
	//��ָ����ϸ�ֲ�������obj��ʽ,���ڲ���
	void SubTestOut(char *fileName,int level);
	//��������ϸ�ֲ�����
	void SubTestOut(char *fileName);
	//����ǰ����ϸ��
	void subdivide();
	//��վֲ�ϸ���滺����
	void clearPSCache();
	//ͨ���ֲ�ϸ���漯�������ֲ�ϸ�ֻ�����
	void buildPSCache(std::vector<Face*> &faceToBeSub);
	//���ٽ����ֲ�ϸ�ֻ���,��ȷ�Ի���Ҫ̽��
	void buildPSCacheFast(std::vector<Face*> &faceToBeSub);
	//�ֲ�ϸ��
	void partialSubdivision();
	//����ϸ�ֵĲ��
	void unSubdivide();

	//ͨ�������ż����ɾֲ�ϸ���滺��
	void buildPSCacheFromVID(std::vector<size_t> &vertexToBeSub);
	//ͨ���߱�ż����ɾֲ�ϸ���滺��
	void buildPSCacheFromEID(std::vector<size_t> &edgeToBeSub);
	//ͨ�����ż����ɾֲ�ϸ���滺��
	void buildPSCacheFromFID(std::vector<size_t> &faceToBeSub);

	//��ʾ��������
	//type Ϊ����������
	//theMirrorPosition �Ҿ����������������ԭ�������ĵ�λ��
	void mirror(MirrorMode type,Vector &theMirrorPosition);
	//ȡ����������
	void unMirror();
	//����ϸ��
	void updateSubdivision();

	//�õ���ǰ���������,���ڴ洢
	struct ObjectInfo getObjectInfo();
	//ֱ����Ӷ���,���ڴ��ļ��ж�ȡ
	void directPushVertex(Vertex *theVertex);
	//ֱ����ӱ�
	void directPushEdge(Edge *theEdge);
	//ֱ�������
	void directPushFace(Face *theFace);
	
	//�����߿��ƽ������
	void drawWireframeFaced();
	//Ϊѡȡ��������
	void selectionRenderObject();
	//��Ⱦ�߿�ƽ������
	void drawWireframe();
	//��Ⱦ�߿�
	void drawWire(GLuint r=0,GLuint g=0,GLuint b=0);
	//��Ⱦƽ������
	void drawSmooth();
	//��������ķ���,���ڲ���
	void drawNormal();
	//���Ʒ�ƽ��������
	void drawFaced();
	void drawWireEdgeSelected();
	void drawWireFaceSelected();
	void drawWireObjectSelected();
	void drawWireVertexSelected();
	//���Ʒ�ƽ����ѡ��ģʽ
	void drawFacedEdgeSelected();
	//���Ʒ�ƽ����ѡ��ģʽ
	void drawFacedFaceSelected();
	//���Ʒ�ƽ������ѡ��ģʽ
	void drawFacedVertexSelected();
	//���Ʒ�ƽ������ѡ��ģʽ
	void drawFacedObjectSelected();
	//����ƽ������ѡ��ģʽ
	void drawSmoothObjectSelected();
	//�����߿�����ѡ��ģʽ
//	void drawWireObjectSelected();
	//��������ѡ��ģʽ
	void drawObjectSelected();
	//��������ľ���
	void drawMirror();
	//��������
	void draw();
	//�����ж���ķ��ߵ�λ��
	void normalizeVertexNormal();
	//���¶���ķ���
	void updateVNormal(SubdivideVertex *theVertex,size_t level);
	//���¶���ķ���
	void updateVNormal(Vertex *theVertex);
	//������ķ���
	void updateFNormal(Face *theFace);
	//������ķ���
	void updateFNormal(SubdivideFace *theFace,size_t level);
	//�������еķ���
	void updateAllNormal();
	//���������ϸ����ķ���
	void updateAllSubNormal();
	//�õ��ߵ���Ŀ
	size_t edgeCount();
	//�õ��������Ŀ
	size_t vertexCount();
	//�õ������Ŀ
	size_t faceCount();
	//���¶���λ�õ�һ������ֵ
	void vertexPositionChangeA(size_t vertexID,float nx,float ny,float nz);
	//���¶���λ�õ�һ�����ֵ
	void vertexPositionChangeR(size_t vertexID,float nx,float ny,float nz);
	//���¶��㷨��
	void vertexNormalChange(size_t vertexID,float nx,float ny,float nz);
	//ɾ����
	void objectFaceRemove(size_t faceID);
	//ɾ����
	void objectEdgeRemove(size_t edgeID);
	//ɾ������
	void objectVertexRemove(size_t vertexID);
	//�ı�ߵ�����
	void edgeRightChange(size_t edgeID,size_t nr);
	//�ı�ߵ�����
	void edgeLeftChange(size_t edgeID,size_t nl);
	//�ı�ߵ���ʼ��
	void edgeStartChange(size_t edgeID,size_t ns);
	//�ı�ߵ���ֹ��
	void edgeEndChange(size_t edgeID,size_t ne);
	//ɾ�����һ���ڽӱ�
	void vertexAdjacentRemove(size_t vertexID,size_t adjID);
	//������һ���ڽӱ�
	void vertexAdjacentInsert(size_t vertexID,size_t adjID,size_t ne);
	//ĩβ����һ����ı�
	void faceEdgePush(size_t faceID,int nEdge);
	//�������һ����
	void faceEdgePop(size_t faceID);
	//�ı����һ����
	void faceEdgeChange(size_t faceID,size_t edgeID,int nEdge);
	//����һ����ı�
	void faceEdgeInsert(size_t faceID,size_t edgeID,int nEdge);
	//����һ��������ڽӱ�
	void vertexAdjacentPush(size_t vertexID,size_t ne);
	//�ı�һ��������ڽӱ�
	void vertexAdjacentChange(size_t vertexID,size_t edgeID,size_t ne);
	//����һ��������ڽӱ�
	void vertexAdjacentPop(size_t vertexID);
	//����һ��������ڽӱ�
	void vertexAdjacentSwap(size_t vertexID,size_t i1,size_t i2);
	//����һ������ڽӱ�
	void faceEdgeSwap(size_t faceID,size_t i1,size_t i2);
	//ɾ��һ������ڽӱ�
	void faceEdgeRemove(size_t faceID,size_t edgeID);
	//�������xml
	void testXMLOut(char *fileName);
	//���¶�����Ƶ�
	void redefineControlPoint();

private:
	Vector EAdjacentVertex(Vertex *theVertex);
	Vector EAdjacentVertex(SubdivideVertex *theVertex,int level);
	Vector EAdjacentVertex(SubdivideVertex *theVertex);
	void subdivideFace(Face *theFace);
	void subdivideFace(SubdivideFace *theFace);
	void expandSubFace(std::vector<SubdivideFace*> &originalList,size_t level);
	void expandSubFace(std::vector<Face*> &originalList);
	void partialSubdivideFace(SubdivideFace *theFace,int level);
	void partialSubdivideFace(Face *theFace,int level);

public:
	~Object(void);
};
