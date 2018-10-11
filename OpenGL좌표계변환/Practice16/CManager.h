#pragma once
#define SPHERE 0
#define CUBE 1
#define CONE 2
#define TEAPOT 3

// WholeCoordinateRotateKind
#define DEFAULT -1
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

// FigureRotateKind
#define SOLID_FIGURE_Y_AXIS 0
#define WIRE_FIGURE_Y_AXIS 1
#define BOTH_FIGURE_Y_AXIS 2

class CManager
{
private:
	int WholeCoordinateRotateKind;
	int FigureRotateKind;
	int FigureKind;

private:
	int SolidFigureRotateAngle;
	int WireFigureRotateAngle;
	int WholeCoordinateXAxisRotateAngle;
	int WholeCoordinateYAxisRotateAngle;
	int WholeCoordinateZAxisRotateAngle;

public:
	void Draw();
	void Update();
	void GetCommand(char _Command);

public:
	void DrawCoordinate();
	void DrawFloor();
	void DrawSolidFigure();
	void DrawWireFigure();
	void RotateWholeCoordinate();
	void RotateSolidFigure();
	void RotateWireFigure();

public:
	CManager();
	~CManager();
};

