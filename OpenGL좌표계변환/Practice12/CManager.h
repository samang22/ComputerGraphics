#pragma once

#include <list>


#define CIRCLE '0'
#define SIN '1'
#define TORNADO '2'
#define ZIGZAG '3'
#define FREE '4'

#define ROTATE_SMALLZ 'z'
#define ROTATE_LARGEZ 'Z'

#define ROTATE_SMALLY 'y'
#define ROTATE_LARGEY 'Y'


#define RECTANGLE true
#define TRIANGLE false

#define CIRCLE_RADIUS 200


struct MousePoint
{
	int X;
	int Y;
};

class CManager
{
private:
	// 사인, 지그재그에 사용
	float Point[800][2];
	// 원
	float CirclePoint[72][2];
	// 회오리
	float TornadoPoint[72 * 3][2];

private:
	int Tornado_Radius;

private:
	float LUX;
	float LUY;
	float RDX;
	float RDY;
	float CenterX;
	float CenterY;
	float FigureWidth;
	int FigureIndex;

	bool Expansion;

	int Angle;
private:
	int Mode_Course;
	bool Figure;
	bool Z_Rotate_Switch;
	// 몇번 돌았는지 확인
	int ZRotateCount;
	float ZRotate_Radius;

	bool Y_Rotate_Switch;
	int YRotateCount;
private:
	// 4번
	//float MousePoint[5][2];
	//int MousePointIndex;

	// 최대 5개
	std::list<MousePoint> MousePointList;
	std::list<MousePoint> FreeVertexList;
	std::list<MousePoint>::iterator UpdateIter;

	bool MousePointStart;
	bool FreeVertexDone;

public:
	void Update();
	void DrawCourse();
	void DrawFigure();
	void DrawLine();
	void Motion();
	void InitCoordinate();
	void YRotate();

public:
	void SetCommand(char _Key);
	void SetMousePoint(int _MouseX, int _MouseY);
	void SetMousePointDone();
public:
	CManager();
	~CManager();
};

