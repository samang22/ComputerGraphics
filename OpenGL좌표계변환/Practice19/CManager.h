#pragma once
#define CIRCLE_RADIUS 200
#define CIRCLE_ORBIT_RADIUS 100

class CManager
{
private:
	const float Radius;

	float SphereX;
	float SphereY;
	float SphereZ;

	// 원점으로 돌아가기 위한 변수
	float TempX;
	float TempY;
	float TempZ;

	float SphereRotateAngleX;
	float SphereRotateAngleY;
	float SphereRotateAngleZ;

public:
	void Draw();
	//void Update();
	void GetCommand(char _key);
public:
	void DrawSphere();
	void SphereRotatateXPlus();
	void SphereRotatateXMinus();
	void SphereRotatateYPlus();
	void SphereRotatateYMinus();
	void SphereRotatateZPlus();
	void SphereRotatateZMinus();
	void DrawFloor();
public:
	CManager();
	~CManager();
};

