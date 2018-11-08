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

CManager::CManager() : Radius(30), SphereX(0), SphereY(0), SphereZ(0),
SphereRotateAngleX(0), SphereRotateAngleY(0), SphereRotateAngleZ(0),
TempX(0), TempY(0), TempZ(0)
{
}

CManager::~CManager()
{
}

void CManager::Draw()
{
	DrawFloor();
	DrawSphere();
}
void CManager::DrawSphere()
{
	glColor3f(1.0, 0.0, 0.0);

	glPushMatrix();
	// 회전
	//glRotatef(SphereRotateAngleX, 1.0, 0.0, 0.0);
	//glRotatef(SphereRotateAngleY, 0.0, 1.0, 0.0);
	// 원점으로 이동
	//glTranslatef(-TempX, -TempY, -TempZ);
	glTranslatef(SphereX, SphereY, SphereZ);
	glRotatef(SphereRotateAngleX, 1.0, 0.0, 0.0);
	glRotatef(SphereRotateAngleY, 0.0, 1.0, 0.0);
	glRotatef(SphereRotateAngleZ, 0.0, 0.0, 1.0);

	// 원래 자리로 이동
	//glTranslatef(TempX, TempY, TempZ);

	glutWireSphere(Radius, 10, 10);
	glPopMatrix();
}

void CManager::SphereRotatateXPlus()
{
}
void CManager::SphereRotatateXMinus()
{

}
void CManager::SphereRotatateYPlus()
{

}
void CManager::SphereRotatateYMinus()
{

}
void CManager::SphereRotatateZPlus()
{

}
void CManager::SphereRotatateZMinus()
{

}
void CManager::GetCommand(char _key)
{
	switch (_key)
	{
	case 'w':
	case 'W':
		if (SphereZ > -200)
		{
			SphereZ -= SPHERE_MOVE_LENGTH;
		}
		SphereRotateAngleX += SPHERE_ROTATE_ANGLE;
		break;
	case 'a':
	case 'A':
		if (SphereX > -200)
		{
			SphereX -= SPHERE_MOVE_LENGTH;
		}
		SphereRotateAngleZ -= SPHERE_ROTATE_ANGLE;
		break;
	case 's':
	case 'S':
		if (SphereZ < 200)
		{
			SphereZ += SPHERE_MOVE_LENGTH;
		}
		SphereRotateAngleX -= SPHERE_ROTATE_ANGLE;
		break;
	case 'd':
	case 'D':
		if (SphereX < 200)
		{
			SphereX += SPHERE_MOVE_LENGTH;
		}
		SphereRotateAngleZ += SPHERE_ROTATE_ANGLE;

		break;
	case 'y':
	case 'Y':
		SphereRotateAngleY += 5;

		break;
	case 'i':
	case 'I':
		SphereX = 0;
		SphereY = 0;
		SphereZ = 0;

		SphereRotateAngleX = 0;
		SphereRotateAngleY = 0;
		SphereRotateAngleZ = 0;
		break;
	default:
		break;
	}
}
void CManager::DrawFloor()
{
	glColor3f(1.0, 1.0, 0.0);

	glPushMatrix();
	glScalef(1.0, 0.01, 1.3);
	glutSolidCube(400);
	glPopMatrix();
}
