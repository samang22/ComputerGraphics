#include "pch.h"
#include "CManager.h"
#include <gl/freeglut.h>
#include <math.h>

float GetRadian(int _Num)
{
	return _Num * (3.1415926545 / 180);
}

CManager::CManager() : NormalAngle(0), CCWAngle(30), CWAngle(60), 
	NormalX(0), NormalZ(0), CCWX(0), CCWZ(0), CWX(0), CWZ(0),
	NormalOrbitX(0), NormalOrbitZ(0), CCWOrbitX(0), CCWOrbitZ(0),
	CWOrbitX(0), CWOrbitZ(0), NormalOrbitAngle(0), CCWOrbitAngle(0),
	CWOrbitAngle(0)
{
}

CManager::~CManager()
{
}
void CManager::Update()
{
	NormalX = sin(GetRadian(NormalAngle)) * CIRCLE_RADIUS;
	NormalZ = cos(GetRadian(NormalAngle)) * CIRCLE_RADIUS;
	NormalOrbitX = sin(GetRadian(NormalOrbitAngle)) * CIRCLE_ORBIT_RADIUS;
	NormalOrbitZ = cos(GetRadian(NormalOrbitAngle)) * CIRCLE_ORBIT_RADIUS;

	CCWX = sin(GetRadian(CCWAngle)) * CIRCLE_RADIUS;
	CCWZ = cos(GetRadian(CCWAngle)) * CIRCLE_RADIUS;
	CCWOrbitX = sin(GetRadian(CCWAngle)) * CIRCLE_ORBIT_RADIUS;
	CCWOrbitZ = cos(GetRadian(CCWAngle)) * CIRCLE_ORBIT_RADIUS;

	CWX = sin(GetRadian(CWAngle)) * CIRCLE_RADIUS;
	CWZ = cos(GetRadian(CWAngle)) * CIRCLE_RADIUS;
	CWOrbitX = sin(GetRadian(CWOrbitAngle)) * CIRCLE_ORBIT_RADIUS;
	CWOrbitZ = cos(GetRadian(CWOrbitAngle)) * CIRCLE_ORBIT_RADIUS;

	NormalAngle = (NormalAngle + 5) % 360;
	NormalOrbitAngle = (NormalOrbitAngle + 5) % 360;
	CCWAngle = (CCWAngle + 5) % 360;
	CCWOrbitAngle = (CCWOrbitAngle + 5) % 360;
	CWAngle = (CWAngle + 5) % 360;
	CWOrbitAngle = (CWOrbitAngle + 5) % 360;
}

void CManager::Draw()
{
	DrawCenterSphere();
	//DrawNormalOrbit();
	//DrawNormalSphere();
	//DrawNormalOrbitOrbit();
	//DrawNormalOrbitSphere();
	DrawCCW45Sphere();
	DrawCCW45Orbit();
	DrawCCW45OrbitOrbit();
	DrawCCW45OrbitSphere();
	DrawCW45Sphere();
	DrawCW45Orbit();
	DrawCW45OrbitOrbit();
	DrawCW45OrbitSphere();
}
void CManager::DrawCenterSphere()
{
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(50, 10, 10);
}
void CManager::DrawNormalOrbit()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0; i <= 360; i+=5)
	{
		glVertex3f(sin(GetRadian(i)) * CIRCLE_RADIUS, 0.0, cos(GetRadian(i)) * CIRCLE_RADIUS);
	}
	glEnd();
}
void CManager::DrawNormalSphere()
{
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(NormalX, 0.0, NormalZ);
	glutSolidSphere(25, 10, 10);
	glPopMatrix();
}
void CManager::DrawNormalOrbitOrbit()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(NormalX, 0.0, NormalZ);
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0; i <= 360; i += 5)
	{
		glVertex3f(sin(GetRadian(i)) * CIRCLE_ORBIT_RADIUS, 0.0, cos(GetRadian(i)) * CIRCLE_ORBIT_RADIUS);
	}
	glEnd();
	glPopMatrix();
}
void CManager::DrawNormalOrbitSphere()
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(NormalOrbitX, 0.0, NormalOrbitZ);
	glutSolidSphere(15, 10, 10);
	glPopMatrix();
}


void CManager::DrawCCW45Orbit()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0; i <= 360; i += 5)
	{
		glVertex3f(sin(GetRadian(i)) * CIRCLE_RADIUS, 0.0, cos(GetRadian(i)) * CIRCLE_RADIUS);
	}
	glEnd();
	glPopMatrix();
}
void CManager::DrawCCW45Sphere()
{
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(CCWX, 0.0, CCWZ);
	glutSolidSphere(25, 10, 10);
	glPopMatrix();
}
void CManager::DrawCCW45OrbitOrbit()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(CCWX, 0.0, CCWZ);
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0; i <= 360; i += 5)
	{
		glVertex3f(sin(GetRadian(i)) * CIRCLE_ORBIT_RADIUS, 0.0, cos(GetRadian(i)) * CIRCLE_ORBIT_RADIUS);
	}
	glEnd();
	glPopMatrix();
}
void CManager::DrawCCW45OrbitSphere()
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(CCWX, 0.0, CCWZ);
	glTranslatef(CCWOrbitX, 0.0, CCWOrbitZ);
	glutSolidSphere(15, 10, 10);
	glPopMatrix();
}

void CManager::DrawCW45Orbit()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0; i <= 360; i += 5)
	{
		glVertex3f(sin(GetRadian(i)) * CIRCLE_RADIUS, 0.0, cos(GetRadian(i)) * CIRCLE_RADIUS);
	}
	glEnd();
	glPopMatrix();
}
void CManager::DrawCW45Sphere()
{
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glTranslatef(CWX, 0.0, CWZ);
	glutSolidSphere(25, 10, 10);
	glPopMatrix();
}
void CManager::DrawCW45OrbitOrbit()
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glTranslatef(CWX, 0.0, CWZ);
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0; i <= 360; i += 5)
	{
		glVertex3f(sin(GetRadian(i)) * CIRCLE_ORBIT_RADIUS, 0.0, cos(GetRadian(i)) * CIRCLE_ORBIT_RADIUS);
	}
	glEnd();
	glPopMatrix();
}
void CManager::DrawCW45OrbitSphere()
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glTranslatef(CWX, 0.0, CWZ);
	glTranslatef(CWOrbitX, 0.0, CWOrbitZ);
	glutSolidSphere(15, 10, 10);
	glPopMatrix();
}


