#pragma once
#define CIRCLE_RADIUS 200
#define CIRCLE_ORBIT_RADIUS 100

#include <list>

struct Ball
{
	float X;
	float Y;
	float Z;

	int Move;
};


class CManager
{
private:
	bool IsFlat;
	bool IsDepthEnable;
	bool IsCulling;

private:
	int YRotateAngle;
	int ZRotateAngle;

	float XTranslate;
	float YTranslate;


	std::list<Ball> BallList;

public:
	void Init();
	void SetMode();
	void Draw();
	void Update();
	void GetCommand(char _key);

public:
	void DrawBox();
	void DrawFallingBoxes(float _Radius);
	void DrawBalls();

	void UpdateBalls();

	void GenerateBalls();
public:
	CManager();
	~CManager();
};

