#pragma once
#define CIRCLE_RADIUS 200
#define CIRCLE_ORBIT_RADIUS 100

class CManager
{
private:
	const float BodySize;
	float BodyX;
	float BodyY;
	float BodyZ;

	const float SmallBodySize;
	float SmallBodyX;
	float SmallBodyY;
	float SmallBodyZ;

	const float ArmSize;
	float ArmX;
	float ArmY;
	float ArmZ;

	float WholeMoveX;
	float WholeYRotateAngle;
	float SmallBodyYRotateAngle;
	float SmallBodyXRotateAngle;
	float ArmXRotateAngle;
	float ArmZRotateAngle;

	bool IsStart;
	bool IsPlus;

public:
	void Init();
	void Draw();
	void Update();
	void GetCommand(char _key);
public:
	void DrawBody();
	void DrawSmallBody();
	void DrawArm();
	void DrawFloor();
	void MoveXPlus();
	void MoveXMinus();

	void WholeRotateY();
	void WholeRotateReverseY();

	void SmallBodyRotateY();
	void SmallBodyRotateX();
	void SmallBodyRotateReverseY();
	void SmallBodyRotateReverseX();
	void ArmRotateX();
	void ArmRotateZ();
	void ArmRotateReverseX();
	void ArmRotateReverseZ();


public:
	CManager();
	~CManager();
};

