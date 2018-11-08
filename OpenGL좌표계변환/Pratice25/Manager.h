#pragma once
#define CIRCLE_RADIUS 200
#define CIRCLE_ORBIT_RADIUS 100

class CManager
{
private:
	bool IsFlat;
	bool IsDepthEnable;
	bool IsCulling;

private:
	int XRotateAngle;
	int YRotateAngle;

	// true�� ������
	// false�� �ݱ�
	bool UpCoverAnimation;
	int UpCoverAngle;

	// true�� ������
	// false�� �ݱ�
	bool FrontCoverAnimation;
	int FrontCoverAngle;

	float UpCircleTranslate;
	float FrontCircleTranslate;
	float FrontCircleRotate;

	float UpSpringScale;
public:
	void Init();
	void SetMode();
	void Draw();
	void Update();
	void GetCommand(char _key);

public:
	void DrawCube();
	void DrawUpCover();
	void DrawFrontCover();
	void UpdateUpCover();
	void UpdateFrontCover();

	void DrawUpCircle();
	void DrawUpSpring();
	void DrawFrontCircle();


public:
	CManager();
	~CManager();
};

