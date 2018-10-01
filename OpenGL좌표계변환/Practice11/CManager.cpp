#include "pch.h"
#include "CManager.h"
#include <math.h>
#include <stdio.h>
#include <gl/freeglut.h>
#include <string.h>
// 11
float GetRadian(int _Num)
{
	return _Num * 3.1415926545 / 180;
}


CManager::CManager() : Mode_Draw(0), Mode_Move(0), Move_Switch(false), 
	LUX(-200), LUY(200), RDX(200), RDY(-200)
{
	memset(Point, 0, sizeof(float) * 800 * 2);
}

CManager::~CManager()
{
}

void CManager::Update()
{
	if (PROGRAM_QUIT_SMALL == Mode_Move)
	{
		Delete();
		exit(1);
	}
	else if (0 == Mode_Draw)
	{
		return;
	}
	int XPos = -400, YPos = 0;
	int Angle = 0;
	int Stack = 0;
	switch (Mode_Draw)
	{
	case DRAW_SIN:
		for (size_t i = 0; i < WINDOW_WIDTH; i++)
		{
			Point[i][0] = XPos;
			// 9 / 10 을 곱한건 -360 ~ 360 비율로 바꿔주려고
			Point[i][1] = sin(GetRadian(XPos * 9 / 10)) * 100;
			XPos += 1;
		}
		break;
	case DRAW_SPRING:
		for (size_t i = 0; i < WINDOW_WIDTH; i++)
		{
			if (0 <= Angle && 90 > Angle)
			{
				Point[i][0] = XPos + sin(GetRadian(Angle)) * RADIUS;
				Point[i][1] = YPos - (cos(GetRadian(Angle)) * RADIUS);
			}
			else if (90 <= Angle && 180 > Angle)
			{
				Point[i][0] = XPos + cos(GetRadian(Angle - 90)) * RADIUS;
				Point[i][1] = YPos + (sin(GetRadian(Angle - 90)) * RADIUS);
			}
			else if (180 <= Angle && 270 > Angle)
			{
				Point[i][0] = XPos - sin(GetRadian(Angle - 180)) * RADIUS;
				Point[i][1] = YPos + cos(GetRadian(Angle - 180)) * RADIUS;
			}
			else if (270 <= Angle && 360 > Angle)
			{
				Point[i][0] = XPos - cos(GetRadian(Angle - 270)) * RADIUS;
				Point[i][1] = YPos - (sin(GetRadian(Angle - 270)) * RADIUS);
			}


			XPos+=2;
			Angle = (Angle + 5) % 360;
		}
		break; 
	case DRAW_RIBBON:
		Point[0][0] = LUX;
		Point[0][1] = RDY;
		Point[1][0] = RDX;
		Point[1][1] = LUY;
		Point[2][0] = RDX;
		Point[2][1] = RDY;
		Point[3][0] = LUX;
		Point[3][1] = LUY;
		break;
	case DRAW_RECTANGLE:
		Point[0][0] = LUX;
		Point[0][1] = LUY;
		Point[1][0] = LUX;
		Point[1][1] = RDY;
		Point[2][0] = RDX;
		Point[2][1] = RDY;
		Point[3][0] = RDX;
		Point[3][1] = LUY;
		break;
	default:
		break;
	}
}
void CManager::DrawLine()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glVertex3f(-8000.0, 0.0, 1.0f);
	glVertex3f(8000.0, 0.0, 1.0f);
	glVertex3f(0.0, -300.0, 1.0f);
	glVertex3f(0.0, 300.0, 1.0f);
	glEnd();
}

void CManager::Draw()
{
	if (0 == Mode_Draw)
	{
		return;
	}
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //점색
	glPointSize(1.0f);//점의 크기

	float X = 0, Y = 0;

	switch (Mode_Draw)
	{
	case DRAW_SIN:
	case DRAW_SPRING:
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < WINDOW_WIDTH; ++i)
		{
			//glBegin(GL_POINTS);
			X = Point[i][0];
			Y = Point[i][1];
			printf("%f, %f\n", X, Y);
			//glVertex2f(X, Y);//점의 좌표
			glVertex3f(X, Y, 1.0f);//점의 좌표
		}
		glEnd();
		break;
	case DRAW_RIBBON:
		glBegin(GL_LINE_LOOP);
		for (size_t i = 0; i < 4; i++)
		{
			glVertex3f(Point[i][0], Point[i][1], 1.0f);
		}
		glEnd();
		break;
	case DRAW_RECTANGLE:
		glBegin(GL_LINE_LOOP);
		for (size_t i = 0; i < 4; i++)
		{
			glVertex3f(Point[i][0], Point[i][1], 1.0f);
		}
		glEnd();
		break;
	default:
		break;
	}
}

bool CManager::Move()
{
	switch (Mode_Move)
	{
	case MOVE_X_SMALL:
		glTranslatef(1.0, 0.0, 0.0);
		MoveList.push_front(MOVE_X_SMALL);

		//Mode_Move = 0;
		break;
	case MOVE_Y_SMALL:
		glTranslatef(0.0, 1.0, 0.0);
		MoveList.push_front(MOVE_Y_SMALL);
		//Mode_Move = 0;
		break;
	case EXPANSION_X_SMALL:
		glScalef(1.1, 1.0, 1.0);
		MoveList.push_front(EXPANSION_X_SMALL);
		//Mode_Move = 0;
		break;
	case SHRINK_X_SMALL:
		glScalef(0.9, 1.0, 1.0);
		MoveList.push_front(SHRINK_X_SMALL);
		break;
	case MOVE10_X_SMALL:
		glTranslatef(10.0, 0.0, 0.0);
		MoveList.push_front(MOVE10_X_SMALL);
		//Mode_Move = 0;
		break;
	case MOVE_ANIMATION_SMALL:
		glTranslatef(1.0, 0.0, 0.0);
		MoveList.push_front(MOVE_ANIMATION_SMALL);
		break;
	case REVERSE_MOVE_ANIMATION_SMALL:
		glTranslatef(-1.0, 0.0, 0.0);
		MoveList.push_front(REVERSE_MOVE_ANIMATION_SMALL);
		break;
	case STOP_ANIMATION_SMALL:
		Mode_Move = 0;
		break;

	default:
		break;
	}

	if (PROGRAM_QUIT_SMALL == Mode_Move)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CManager::GetCommand(char _Key)
{
	switch (_Key)
	{
	case DRAW_SIN:
		Mode_Draw = DRAW_SIN;
		break;
	case DRAW_SPRING:
		Mode_Draw = DRAW_SPRING;
		break;
	case DRAW_RIBBON:
		Mode_Draw = DRAW_RIBBON;
		break;
	case DRAW_RECTANGLE:
		Mode_Draw = DRAW_RECTANGLE;
		break;


	case MOVE_X_SMALL:
	case MOVE_X_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = MOVE_X_SMALL;
			Move_Switch = true;
		}
		break;
	case MOVE_Y_SMALL:
	case MOVE_Y_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = MOVE_Y_SMALL;
			Move_Switch = true;
		}
		break;
	case EXPANSION_X_SMALL:
	case EXPANSION_X_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = EXPANSION_X_SMALL;
			Move_Switch = true;
		}		
		break;
	case SHRINK_X_SMALL:
	case SHRINK_X_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = SHRINK_X_SMALL;
			Move_Switch = true;
		}
		break;
	case REVERSE_MOVE_ANIMATION_SMALL:
	case REVERSE_MOVE_ANIMATION_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = REVERSE_MOVE_ANIMATION_SMALL;
			Move_Switch = true;
		}
		break;
	case MOVE10_X_SMALL:
	case MOVE10_X_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = MOVE10_X_SMALL;
			Move_Switch = true;
		}
		break;
	case MOVE_ANIMATION_SMALL:
	case MOVE_ANIMATION_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = MOVE_ANIMATION_SMALL;
			Move_Switch = true;
		}
		break;
	case STOP_ANIMATION_SMALL:
	case STOP_ANIMATION_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = 0;
		}
		else
		{
			Mode_Move = STOP_ANIMATION_SMALL;
			Move_Switch = true;
		}
		break;
	case PROGRAM_QUIT_SMALL:
	case PROGRAM_QUIT_LARGE:
		if (true == Move_Switch)
		{
			Move_Switch = false;
			Mode_Move = PROGRAM_QUIT_SMALL;
		}
		else
		{
			Mode_Move = PROGRAM_QUIT_SMALL;
			Move_Switch = false;
		}
		break;
	default:
		break;
	}
}
void CManager::InitCoordinate()
{
	std::list<char>::iterator iter;
	for (iter = MoveList.begin(); iter != MoveList.end(); iter++)
	{
		switch (*iter)
		{
		case MOVE_X_SMALL:
			glTranslatef(-1.0, 0.0, 0.0);
			break;
		case MOVE_Y_SMALL:
			glTranslatef(0.0, -1.0, 0.0);
			break;
		case EXPANSION_X_SMALL:
			glScalef(0.9, 1.0, 1.0);
			break;
		case MOVE10_X_SMALL:
			glTranslatef(-10.0, 0.0, 0.0);
			break;
		case MOVE_ANIMATION_SMALL:
			glTranslatef(-1.0, 0.0, 0.0);
			break;
		case SHRINK_X_SMALL:
			glScalef(1.1, 1.0, 1.0);
			break;
		case REVERSE_MOVE_ANIMATION_SMALL:
			glTranslatef(1.0, 0.0, 0.0);
			break;
		default:
			break;
		}
	}
}



int CManager::GetModeMove()
{
	return Mode_Move;
}
bool CManager::GetMoveSwitch()
{
	return Move_Switch;
}

void CManager::Delete()
{
	if (MoveList.size() != 0)
	{
		MoveList.clear();
	}
}
