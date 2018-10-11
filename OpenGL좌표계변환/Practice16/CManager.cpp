#include "pch.h"
#include "CManager.h"
#include <gl/freeglut.h>


CManager::CManager() : WholeCoordinateRotateKind(-1), FigureRotateKind(-1),	FigureKind(CUBE),
	SolidFigureRotateAngle(0), WireFigureRotateAngle(0),
	WholeCoordinateXAxisRotateAngle(0),	WholeCoordinateYAxisRotateAngle(0),	WholeCoordinateZAxisRotateAngle(0)
{
}

CManager::~CManager()
{
}

void CManager::Draw()
{
	DrawCoordinate();
	DrawFloor();
	glPushMatrix(); // RotateWholeCoordinate
	// 얘는 DEAFAULT 값이 들어가 있으면 회전 안한다
	RotateWholeCoordinate();

	if (SOLID_FIGURE_Y_AXIS == FigureRotateKind || BOTH_FIGURE_Y_AXIS == FigureRotateKind)
	{
		glPushMatrix(); // RotateSolidFigure
		RotateSolidFigure();
	}
	DrawSolidFigure();
	if (SOLID_FIGURE_Y_AXIS == FigureRotateKind || BOTH_FIGURE_Y_AXIS == FigureRotateKind)
	{
		glPopMatrix(); // RotateSolidFigure
	}

	if (WIRE_FIGURE_Y_AXIS == FigureRotateKind || BOTH_FIGURE_Y_AXIS == FigureRotateKind)
	{
		glPushMatrix(); // RotateWireFigure
		RotateWireFigure();
	}
	DrawWireFigure();
	if (WIRE_FIGURE_Y_AXIS == FigureRotateKind || BOTH_FIGURE_Y_AXIS == FigureRotateKind)
	{
		glPopMatrix(); // RotateWireFigure
	}
	glPopMatrix(); // RotateWholeCoordinate
}
void CManager::Update()
{
	switch (WholeCoordinateRotateKind)
	{
	case X_AXIS:
		WholeCoordinateXAxisRotateAngle = (WholeCoordinateXAxisRotateAngle + 5) % 360;
		break;
	case Y_AXIS:
		WholeCoordinateYAxisRotateAngle = (WholeCoordinateYAxisRotateAngle + 5) % 360;
		break;
	case Z_AXIS:
		WholeCoordinateZAxisRotateAngle = (WholeCoordinateZAxisRotateAngle + 5) % 360;
		break;
	default:
		break;
	}

	switch (FigureRotateKind)
	{
	case SOLID_FIGURE_Y_AXIS:
		SolidFigureRotateAngle = (SolidFigureRotateAngle + 5) % 360;
		break;
	case WIRE_FIGURE_Y_AXIS:
		WireFigureRotateAngle = (WireFigureRotateAngle + 5) % 360;
		break;
	case BOTH_FIGURE_Y_AXIS:
		SolidFigureRotateAngle = (SolidFigureRotateAngle + 5) % 360;
		WireFigureRotateAngle = (WireFigureRotateAngle + 5) % 360;
		break;
	default:
		break;
	}
}
void CManager::RotateWholeCoordinate()
{
	switch (WholeCoordinateRotateKind)
	{
	case X_AXIS:
		glRotatef((float)WholeCoordinateXAxisRotateAngle, 1.0, 0.0, 0.0);
		break;
	case Y_AXIS:
		glRotatef((float)WholeCoordinateYAxisRotateAngle, 0.0, 1.0, 0.0);
		break;
	case Z_AXIS:
		glRotatef((float)WholeCoordinateZAxisRotateAngle, 0.0, 0.0, 1.0);
		break;
	default:
		break;
	}
}
void CManager::RotateSolidFigure()
{
	glTranslatef(-200.0, -150.0, 0.0);
	glRotatef((float)SolidFigureRotateAngle, 0.0, 1.0, 0.0);
	glTranslatef(200.0, 150.0, 0.0);
}
void CManager::RotateWireFigure()
{
	glTranslatef(200.0, -150.0, 0.0);
	glRotatef((float)WireFigureRotateAngle, 0.0, 1.0, 0.0);
	glTranslatef(-200.0, 150.0, 0.0);
}

void CManager::GetCommand(char _Command)
{
	switch (_Command)
	{
	case 'x':
	case 'X':
		if (X_AXIS == WholeCoordinateRotateKind)
		{
			WholeCoordinateRotateKind = DEFAULT;
		}
		else
		{
			WholeCoordinateRotateKind = X_AXIS;
		}
		break;
	case 'y':
	case 'Y':
		if (Y_AXIS == WholeCoordinateRotateKind)
		{
			WholeCoordinateRotateKind = DEFAULT;
		}
		else
		{
			WholeCoordinateRotateKind = Y_AXIS;
		}
		break;
	case 'z':
	case 'Z':
		if (Z_AXIS == WholeCoordinateRotateKind)
		{
			WholeCoordinateRotateKind = DEFAULT;
		}
		else
		{
			WholeCoordinateRotateKind = Z_AXIS;
		}
		break;
	case 'l':
	case 'L':
		if (SOLID_FIGURE_Y_AXIS == FigureRotateKind)
		{
			FigureRotateKind = DEFAULT;
		}
		else
		{
			FigureRotateKind = SOLID_FIGURE_Y_AXIS;
		}
		break;
	case 'r':
	case 'R':
		if (WIRE_FIGURE_Y_AXIS == FigureRotateKind)
		{
			FigureRotateKind = DEFAULT;
		}
		else
		{
			FigureRotateKind = WIRE_FIGURE_Y_AXIS;
		}
		break;
	case 'o':
	case 'O':
		if (BOTH_FIGURE_Y_AXIS == FigureRotateKind)
		{
			FigureRotateKind = DEFAULT;
		}
		else
		{
			FigureRotateKind = BOTH_FIGURE_Y_AXIS;
		}
		break;
	case 'c':
	case 'C':
		FigureKind = (FigureKind + 1) % 4;
		break;
	default:
		break;
	}
}


void CManager::DrawCoordinate()
{
	// 빨간색 X축
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glEnd();
	// 녹색 Y축
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glEnd();
}
void CManager::DrawFloor()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glRotatef(-80.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -250.0, 0.0);
	glRectf(-200, 200, 200, -200);
	glPopMatrix();
}

void CManager::DrawSolidFigure()
{
	switch (FigureKind)
	{
	case SPHERE:
		glPushMatrix();
		glTranslatef(-200.0, -150.0, 0.0);
		glColor3f(0.0, 1.0, 1.0);
		glutSolidSphere(100, 10, 10);
		glPopMatrix();
		break;
	case CUBE:
		glPushMatrix();
		glTranslatef(-200.0, -150.0, 0.0);
		glColor3f(0.0, 1.0, 1.0);
		glutSolidCube(200);
		glPopMatrix();
		break;
	case CONE:
		glPushMatrix();
		glTranslatef(-200.0, -150.0, 0.0);
		glColor3f(0.0, 1.0, 1.0);
		glutSolidCone(100, 200, 10, 10);
		glPopMatrix();
		break;
	case TEAPOT:
		glPushMatrix();
		glTranslatef(-200.0, -150.0, 0.0);
		glColor3f(0.0, 1.0, 1.0);
		glutSolidTeapot(100);
		glPopMatrix();
		break;
	default:
		break;
	}

}
void CManager::DrawWireFigure()
{
	switch (FigureKind)
	{
	case SPHERE:
		glPushMatrix();
		glTranslatef(200.0, -150.0, 0.0);
		glColor3f(1.0, 1.0, 0.0);
		glutWireSphere(100, 10, 10);
		glPopMatrix();
		break;
	case CUBE:
		glPushMatrix();
		glTranslatef(200.0, -150.0, 0.0);
		glColor3f(1.0, 1.0, 0.0);
		glutWireCube(200);
		glPopMatrix();
		break;
	case CONE:
		glPushMatrix();
		glTranslatef(200.0, -150.0, 0.0);
		glColor3f(1.0, 1.0, 0.0);
		glutWireCone(100, 200, 10, 10);
		glPopMatrix();
		break;
	case TEAPOT:
		glPushMatrix();
		glTranslatef(200.0, -150.0, 0.0);
		glColor3f(1.0, 1.0, 0.0);
		glutWireTeapot(100);
		glPopMatrix();
		break;
	default:
		break;
	}
}