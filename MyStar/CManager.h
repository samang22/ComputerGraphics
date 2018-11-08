#pragma once
#include <list>

struct Rect
{
	float X;
	float Y;
	float Length;
	bool Rotate;
	float R;
	float G;
	float B;

	//float Up;
};

struct Tri
{
	float X;
	float Y;
	float Length;
	int Angle;
	float R;
	float G;
	float B;

	int State;

	// -1이면 없음
	// 0~13
	int FallPos;
};

struct Star
{
	float X;
	float Y;
	float GoalX;
	float GoalY;
	float Length;
	int Angle;
	float State;
	float R;
	float G;
	float B;
};

struct Point
{
	float X;
	float Y;
};

class CManager
{
private:
	std::list<Rect> RectList;
	std::list<Tri> AboveTriList;
	std::list<Tri> SplittedTriList;
	std::list<Star> StarList;
private:
	Point StartPoint;
	Point EndPoint;
	Point CurrentPoint;

private:
	bool MouseIsStart;
	int RectGenerateCount;
	int TriGenerateCount;

	int FallenTriStack[14];
public:
	void Init();
	void Draw();
	void Update();
	void GetCommand(char _key);
	void GetMouseEvent(int button, int state, float x, float y);
	void GetMouseMotion(float x, float y);

public:
	void UpdateRect();
	void UpdateAboveTri();
	void UpdateSplittedTri();
	void UpdateStar();

	void DeleteRect();
	void DeleteTri();
	void DeleteHoldedTri();

	void DrawGrid();
	void DrawRect();
	void DrawTri();
	void DrawDrag();
	void DrawSplittedTri();
	void DrawStar();

	void GenerateRectangle();
	void GenerateAboveTriangle();
	void GenerateStar(float _X, float _Y);


	void SetStartPoint(float _X, float _Y);
	void SetEndPoint(float _X, float _Y);
	void SetCurrentPoint(float _X, float _Y);

	bool GetIsStart();
	void DragStart();
	void DragDone();

	bool CheckDragRectCollision(Rect _Rect);
	void SplitRect(bool _Rotate, float _X, float _Y);
	
	bool IsFallingTri();
	bool IsHoldedTri();
	bool CheckTriClicked(float _X, float _Y);

	void SetHoldedToFalling();

	bool CheckAboveHoldedCollision(float _X, float _Y);
public:
	CManager();
	~CManager();
};

