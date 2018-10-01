#pragma once
#define EXPANSION_SMALLS 's'
#define EXPANSION_LARGES 'S'

#define ROTATE_SMALLY 'y'
#define ROTATE_LARGEY 'Y'

class CManager
{
private:
	float LUX;
	float LUY;
	float RDX;
	float RDY;

	float XYCenterX;
	float XYCenterY;
	float YZCenterZ;
	float YZCenterY;

	float FigureWidth;
	const float CourseWidth;
	bool Expansion;

	int Angle;

	bool Start;

private:
	int xyMode;
	int yzMode;

	float xyAlpha1;
	float xyAlpha2;
	float xyBeta1;
	float xyBeta2;
	float yzAlpha1;
	float yzAlpha2;
	float yzBeta1;
	float yzBeta2;




private:

	// 몇번 돌았는지 확인
	bool Y_Rotate_Switch;
	int YRotateCount;

	bool CourseExpansion;
	bool CourseExpansionUpDown;
	int CourseExpansionCount;
private:
	void Init();

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
public:
	CManager();
	~CManager();
};

