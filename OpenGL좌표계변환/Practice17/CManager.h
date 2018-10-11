#pragma once
#define CIRCLE_RADIUS 200
#define CIRCLE_ORBIT_RADIUS 100

class CManager
{
private:
	float NormalX;
	float NormalZ;
	float NormalOrbitX;
	float NormalOrbitZ;

	float CCWX;
	float CCWZ;
	float CCWOrbitX;
	float CCWOrbitZ;

	float CWX;
	float CWZ;
	float CWOrbitX;
	float CWOrbitZ;

	int NormalAngle;
	int NormalOrbitAngle;

	int CCWAngle;
	int CCWOrbitAngle;

	int CWAngle;
	int CWOrbitAngle;
public:
	void Draw();
	void Update();
public:
	void DrawCenterSphere();
	void DrawNormalOrbit();
	void DrawNormalSphere();
	void DrawNormalOrbitOrbit();
	void DrawNormalOrbitSphere();

	void DrawCCW45Sphere();
	void DrawCCW45Orbit();
	void DrawCCW45OrbitOrbit();
	void DrawCCW45OrbitSphere();

	void DrawCW45Sphere();
	void DrawCW45Orbit();
	void DrawCW45OrbitOrbit();
	void DrawCW45OrbitSphere();
public:
	CManager();
	~CManager();
};

