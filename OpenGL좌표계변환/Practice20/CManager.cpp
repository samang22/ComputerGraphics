#include "pch.h"
#include "CManager.h"
#include <gl/freeglut.h>
#include <math.h>

#define SPHERE_MOVE_LENGTH 5
#define SPHERE_ROTATE_ANGLE 5

float GetRadian(int _Num)
{
	return (float)(_Num * (3.1415926545 / 180));
}

CManager::CManager() : BodySize(60), BodyX(0), BodyY(0), BodyZ(0),
	SmallBodySize(40), SmallBodyX(0), SmallBodyY(0), SmallBodyZ(0),
	ArmSize(20), ArmX(0), ArmY(0), ArmZ(0), IsPlus(true), IsStart(false),
	WholeMoveX(0), WholeYRotateAngle(0), SmallBodyYRotateAngle(0), SmallBodyXRotateAngle(0),
	ArmXRotateAngle(0),	ArmZRotateAngle(0)
{
}

CManager::~CManager()
{
}
void CManager::Init()
{
	SmallBodyY = BodySize;
	ArmY = BodySize + SmallBodySize - 10;
}

void CManager::Draw()
{
	DrawFloor();
	glPushMatrix();
		glTranslatef(WholeMoveX, 0.0, 0.0);
		glRotatef(WholeYRotateAngle, 0.0, 1.0, 0.0);
		DrawBody();
		glTranslatef(SmallBodyX, SmallBodyY - 20, SmallBodyZ);
		glRotatef(SmallBodyYRotateAngle, 0.0, 1.0, 0.0);
		glRotatef(SmallBodyXRotateAngle, 1.0, 0.0, 0.0);
		glTranslatef(-SmallBodyX, -SmallBodyY + 20, -SmallBodyZ);
		DrawSmallBody();
			glTranslatef(ArmX, ArmY - 15, ArmZ);
			glRotatef(ArmXRotateAngle, 1.0, 0.0, 0.0);
			glRotatef(ArmZRotateAngle, 0.0, 0.0, 1.0);
			glTranslatef(-ArmX, -ArmY + 15, -ArmZ);
			DrawArm();
	glPopMatrix();
}
void CManager::Update()
{
	if (WholeMoveX >= 200)
	{
		IsPlus = false;
	}
	else if (WholeMoveX <= -200)
	{
		IsPlus = true;
	}

	if (IsPlus)
	{
		MoveXPlus();
	}
	else
	{
		MoveXMinus();
	}
}
void CManager::DrawBody()
{
	glPushMatrix();
		glScalef(1.2, 1.0, 1.2);
		glTranslatef(BodyX, BodyY, BodyZ);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidCube(BodySize);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(BodySize);
		glPopMatrix();
}
void CManager::DrawSmallBody()
{
	glPushMatrix();
		glScalef(0.2, 1.0, 0.2);
		glTranslatef(SmallBodyX, SmallBodyY, SmallBodyZ);
		glColor3f(0.0, 1.0, 0.0);
		glutSolidCube(SmallBodySize);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(SmallBodySize);
	glPopMatrix();
}
void CManager::DrawArm()
{
	glPushMatrix();
		glScalef(0.2, 1.0, 0.2);
		glTranslatef(ArmX, ArmY, ArmZ);
		glColor3f(0.0, 1.0, 1.0);
		glutSolidCube(ArmSize);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(ArmSize);
	glPopMatrix();
}
void CManager::DrawFloor()
{
	glPushMatrix();
		glScalef(1.0, 0.01, 1.3);
		glColor3f(1.0, 1.0, 0.0);
		glutSolidCube(400);
	glPopMatrix();
}
void CManager::MoveXPlus()
{
	WholeMoveX+= 3;
}
void CManager::MoveXMinus()
{
	WholeMoveX-= 3;
}
void CManager::WholeRotateY()
{
	WholeYRotateAngle += 5;
}
void CManager::WholeRotateReverseY()
{
	if (WholeYRotateAngle > -90)
	{
		WholeYRotateAngle -= 5;
	}
}

void CManager::SmallBodyRotateY()
{
	if (SmallBodyYRotateAngle < 90)
	{
		SmallBodyYRotateAngle += 5;
	}
}
void CManager::SmallBodyRotateX()
{
	if (SmallBodyXRotateAngle < 90)
	{
		SmallBodyXRotateAngle += 5;
	}
}


void CManager::SmallBodyRotateReverseY()
{
	if (SmallBodyYRotateAngle > -90)
	{
		SmallBodyYRotateAngle -= 5;
	}
}
void CManager::SmallBodyRotateReverseX()
{
	if (SmallBodyXRotateAngle > -90)
	{
		SmallBodyXRotateAngle -= 5;
	}
}

void CManager::ArmRotateX()
{
	if (ArmXRotateAngle < 90)
	{
		ArmXRotateAngle += 5;
	}
}
void CManager::ArmRotateZ()
{
	if (ArmZRotateAngle < 90)
	{
		ArmZRotateAngle += 5;
	}
}
void CManager::ArmRotateReverseX()
{
	if (ArmXRotateAngle > -90)
	{
		ArmXRotateAngle -= 5;
	}

}
void CManager::ArmRotateReverseZ()
{
	if (ArmZRotateAngle > -90)
	{
		ArmZRotateAngle -= 5;
	}
}





void CManager::GetCommand(char _key)
{
	switch (_key)
	{
	case 'q':
	case 'Q':
		WholeRotateY();
		break;
	case 'w':
	case 'W':
		SmallBodyRotateY();
		break;
	case 'e':
	case 'E':
		SmallBodyRotateX();
		break;
	case 'r':
	case 'R':
		ArmRotateX();
		break;
	case 't':
	case 'T':
		ArmRotateZ();
		break;
	//case 'a':
	//case 'A':
	//	WholeRotateReverseY();
	//	break;
	case 's':
	case 'S':
		SmallBodyRotateReverseY();
		break;
	case 'd':
	case 'D':
		SmallBodyRotateReverseX();
		break;
	case 'f':
	case 'F':
		ArmRotateReverseX();
		break;
	case 'g':
	case 'G':
		ArmRotateReverseZ();
		break;
	default:
		break;
	}
}

