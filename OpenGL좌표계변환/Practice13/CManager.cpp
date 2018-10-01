#include "pch.h"
#include "CManager.h"
#include <string.h>
#include <math.h>
#include <gl/freeglut.h>

float GetRadian(int _Num)
{
	return _Num * (3.1415926545 / 180);
}

CManager::CManager() : LUX(0), LUY(0), RDX(0), RDY(0),
	XYCenterX(0), XYCenterY(0), YZCenterZ(0), YZCenterY(0),
	FigureWidth(30), CourseWidth(200), Expansion(true),
	Y_Rotate_Switch(false), Start(false), xyMode(0), yzMode(0),
	CourseExpansion(false), CourseExpansionUpDown(true), CourseExpansionCount(0)
{
	xyAlpha1 = 0, xyAlpha2 = 0;
	xyBeta1 = 0, xyBeta2 = 0;
	yzAlpha1 = 0, yzAlpha2 = 0;
	yzBeta1 = 0, yzBeta2 = 0;
}

CManager::~CManager()
{
}
void CManager::Init()
{
	XYCenterX = - CourseWidth;
	XYCenterY = - CourseWidth;
	YZCenterZ = - CourseWidth;
	YZCenterY = - CourseWidth;

	xyAlpha1 = 2;
	xyAlpha2 = -2;

	xyBeta1 = CourseWidth;
	xyBeta2 = CourseWidth;

	yzAlpha1 = 2;
	yzAlpha2 = -2;

	yzBeta1 = CourseWidth;
	yzBeta2 = CourseWidth;
}

void CManager::Update()
{
	if (false == Start)
	{
		Init();
		Start = true;
	}

	Motion();


	// Figure 갱신
	switch (xyMode)
	{
	case 0:
		XYCenterX++;
		XYCenterY = xyAlpha1 * XYCenterX + xyBeta1;
		if (0 == XYCenterX)
		{
			xyMode = 1;
		}
		break;
	case 1:
		XYCenterX++;
		XYCenterY = xyAlpha2 * XYCenterX + xyBeta2;
		if (CourseWidth == XYCenterX)
		{
			xyMode = 2;
		}
		break;
	case 2:
		XYCenterX--;
		XYCenterY = -CourseWidth;
		if (0 == -CourseWidth)
		{
			xyMode = 0;
		}
		break;
	default:
		break;
	}
	switch (yzMode)
	{
	case 0:
		YZCenterZ++;
		YZCenterY = yzAlpha1 * YZCenterZ + yzBeta1;
		if (0 == YZCenterZ)
		{
			yzMode = 1;
		}
		break;
	case 1:
		YZCenterZ++;
		YZCenterY = yzAlpha2 * YZCenterZ + yzBeta2;
		if (CourseWidth == YZCenterZ)
		{
			yzMode = 2;
		}
		break;
	case 2:
		YZCenterZ--;
		YZCenterY = - CourseWidth;
		if (-CourseWidth == YZCenterZ)
		{
			yzMode = 0;
		}
		break;
	default:
		break;
	}
}

void CManager::DrawLine()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(-400.0, 0.0, 0.0);
	glVertex3f(400.0, 0.0, 0.0);
	glVertex3f(0.0, -300.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);
	glEnd();
}


void CManager::DrawCourse()
{
	// 경로 그리기

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //점색
	glPointSize(1.0f);//점의 크기
	
	// xy 평면
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0 + CourseWidth, 0.0f);
	glVertex3f(0.0 - CourseWidth, 0 - CourseWidth, 0.0f);
	glVertex3f(0.0 + CourseWidth, 0 - CourseWidth, 0.0f);
	glEnd();
	// yz 평면
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0 + CourseWidth, 0.0f);
	glVertex3f(0.0, 0 - CourseWidth, 0.0 - CourseWidth);
	glVertex3f(0.0, 0 - CourseWidth, 0.0 + CourseWidth);
	glEnd();
}

void CManager::DrawFigure()
{
	if (true == Y_Rotate_Switch)
	{
		glPushMatrix();
		glRotatef(-20, 0.0, 1.0, 0.0);
	}
	// 도형 그리기
	// xy 평면
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //점색
	glBegin(GL_TRIANGLES);
	glVertex3f(XYCenterX, XYCenterY + FigureWidth, 0.0f);
	glVertex3f(XYCenterX - FigureWidth, XYCenterY - FigureWidth, 0.0f);
	glVertex3f(XYCenterX + FigureWidth, XYCenterY - FigureWidth, 0.0f);
	glEnd();

	// yz 평면
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //점색
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, YZCenterY + FigureWidth, YZCenterZ);
	glVertex3f(0.0, YZCenterY - FigureWidth, YZCenterZ - FigureWidth);
	glVertex3f(0.0, YZCenterY - FigureWidth, YZCenterZ + FigureWidth);
	glEnd();

	if (true == Y_Rotate_Switch)
	{
		glPopMatrix();
	}
}
void CManager::Motion()
{
	if (true == Expansion)
	{
		FigureWidth++;
		if (FigureWidth >= 50)
		{
			Expansion = false;
		}
	}
	else
	{
		FigureWidth--;
		if (FigureWidth <= 10)
		{
			Expansion = true;
		}
	}
	YRotate();

	if (true == CourseExpansion)
	{
		if (true == CourseExpansionUpDown)
		{
			CourseExpansionCount++;
			glScalef(1.01f, 1.01f, 1.01f);
			if (10 <= CourseExpansionCount)
			{
				CourseExpansionUpDown = false;
			}
		}
		else
		{
			CourseExpansionCount--;
			glScalef(0.99f, 0.99f, 0.99f);
			if (0 >= CourseExpansionCount)
			{
				CourseExpansionUpDown = true;
			}
		}
	}
}

void CManager::InitCoordinate()
{
	for (int i = 0; i < YRotateCount; i++)
	{
		glRotatef(5, 0.0, 1.0, 0.0);
	}
}
void CManager::YRotate()
{
	if (Y_Rotate_Switch)
	{
		glRotatef(-5, 0.0, 1.0, 0.0);
		YRotateCount = (YRotateCount + 1) % (360 / 5);
	}
}

void CManager::SetCommand(char _Key)
{
	switch (_Key)
	{
	case EXPANSION_SMALLS:
	case EXPANSION_LARGES:
		if (true == CourseExpansion)
		{
			CourseExpansion = false;
		}
		else
		{
			CourseExpansion = true;
		}
		break;
	case ROTATE_SMALLY:
	case ROTATE_LARGEY:
		if (true == Y_Rotate_Switch)
		{
			Y_Rotate_Switch = false;
		}
		else
		{
			Y_Rotate_Switch = true;
		}
		break;

	default:
		break;
	}
}