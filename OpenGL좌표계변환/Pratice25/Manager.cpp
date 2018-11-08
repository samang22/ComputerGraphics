#include "Manager.h"
#include <gl/freeglut.h>
#include <math.h>
#include <stdio.h>

#define INIT_X_ANGLE 30
#define INIT_Y_ANGLE 45

float GetRadian(float _Num)
{
	return (float)(_Num * (3.1415926545 / 180));
}

CManager::CManager() : IsFlat(false), IsDepthEnable(false), IsCulling(false),
	XRotateAngle(INIT_X_ANGLE), YRotateAngle(INIT_Y_ANGLE),
	UpCoverAnimation(false), UpCoverAngle(0), FrontCoverAnimation(false), FrontCoverAngle(0),
	UpCircleTranslate(0), FrontCircleTranslate(0), FrontCircleRotate(0),
	UpSpringScale(1.0)
{
}

CManager::~CManager()
{
}
void CManager::Init()
{
	SetMode();
}
void CManager::SetMode()
{
	if (IsFlat)	glShadeModel(GL_FLAT);		
	else glShadeModel(GL_SMOOTH);

	if (IsDepthEnable) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	if (IsCulling) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
}

void CManager::Draw()
{
	glPushMatrix();
		//glRotatef(XRotateAngle, 1.0, 0.0, 0.0);
		//glRotatef(YRotateAngle, 0.0, 1.0, 0.0);
		DrawCube();
		DrawUpCircle();
		DrawFrontCircle();
		DrawUpSpring();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 3000.0, 0.0);
	glVertex3f(0.0, -3000.0, 0.0);
	glEnd();
}

void CManager::Update()
{
	//SetMode();
	//YRotateAngle += 4;
	UpdateUpCover();
	UpdateFrontCover();
}
void CManager::GetCommand(char _key)
{
	switch (_key)
	{
	case 'q':
	case 'Q':
		if (IsFlat)
		{
			IsFlat = false;
			printf("IsFlat = false\n");
		}
		else
		{
			IsFlat = true;
			printf("IsFlat = true\n");
		}
		break;
	case 'w':
	case 'W':
		if (IsDepthEnable)
		{
			IsDepthEnable = false;
			printf("IsDepthEnable  = false\n");
		}
		else
		{
			IsDepthEnable = true;
			printf("IsDepthEnable  = true\n");
		}
		break;
	case 'e':
	case 'E':
		if (IsCulling)
		{
			IsCulling = false;
			printf("IsCulling  = false\n");
		}
		else
		{
			IsCulling = true;
			printf("IsCulling  = true\n");
		}
		break;
	case 'u':
	case 'U':
		if (UpCoverAnimation) UpCoverAnimation = false;
		else UpCoverAnimation = true;
		break;
	case 'f':
	case 'F':
		if (FrontCoverAnimation) FrontCoverAnimation = false;
		else FrontCoverAnimation = true;
		break;
	default:
		break;
	}

	SetMode();
}

void CManager::DrawCube()
{
	glPushMatrix();
		
		// 아래
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 1.0f);		// Cyan
		glVertex3f(100.0, -100.0, 100.0);
		glColor3f(1.0f, 0.0, 1.0f);			// Magenta
		glVertex3f(100.0, -100.0, -100.0);
		glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		glVertex3f(-100.0, -100.0, -100.0);
		glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
		glVertex3f(-100.0, -100.0, 100.0);
		glEnd();

		// 앞
		//glBegin(GL_QUADS);
		//glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		//glVertex3f(100.0, 100.0, 100.0);
		//glColor3f(1.0f, 0.0, 1.0f);			// Magenta
		//glVertex3f(100.0, -100.0, 100.0);
		//glColor3f(0.0f, 1.0f, 1.0f);		// Cyan
		//glVertex3f(-100.0, -100.0, 100.0);
		//glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
		//glVertex3f(-100.0, 100.0, 100.0);
		//glEnd();

		// 오른쪽
		//glBegin(GL_QUADS);
		//glColor3f(1.0f, 0.0, 1.0f);			// Magenta
		//glVertex3f(100.0, 100.0, 100.0);
		//glColor3f(0.0f, 1.0f, 1.0f);		// Cyan
		//glVertex3f(100.0, 100.0, -100.0);
		//glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
		//glVertex3f(100.0, -100.0, -100.0);
		//glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		//glVertex3f(100.0, -100.0, 100.0);
		//glEnd();

		// 뒤
		//glBegin(GL_QUADS);
		//glColor3f(0.0f, 1.0f, 1.0f);		// Cyan
		//glVertex3f(100.0, 100.0, -100.0);
		//glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
		//glVertex3f(100.0, -100.0, -100.0);
		//glColor3f(1.0f, 0.0, 1.0f);			// Magenta
		//glVertex3f(-100.0, -100.0, -100.0);
		//glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		//glVertex3f(-100.0, 100.0, -100.0);
		//glEnd();

		DrawFrontCover();
		//DrawUpCover();

	glPopMatrix();
}
void CManager::DrawUpCover()
{
	// 윗면
	glPushMatrix();
		glTranslatef(100.0, 0.0, 0.0);
		glTranslatef(0.0, 100.0, 0.0);
		glRotatef(-UpCoverAngle, 0.0, 0.0, 1.0);
		glTranslatef(-100.0, 0.0, 0.0);
		glTranslatef(0.0, -100.0, 0.0);
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0, 1.0f);			// Magenta
		glVertex3f(100.0, 100.0, 100.0);
		glColor3f(0.0f, 1.0f, 1.0f);		// Cyan
		glVertex3f(100.0, 100.0, -100.0);
		glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		glVertex3f(-100.0, 100.0, -100.0);
		glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
		glVertex3f(-100.0, 100.0, 100.0);
		glEnd();
	glPopMatrix();
}
void CManager::DrawFrontCover()
{
	// 앞면
	glPushMatrix();
		glTranslatef(-100.0, 0.0, 0.0);
		glTranslatef(0.0, -100.0, 0.0);
		glRotatef(FrontCoverAngle, 0.0, 0.0, 1.0);
		glTranslatef(100.0, 0.0, 0.0);
		glTranslatef(0.0, 100.0, 0.0);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);		// Yellow
		glVertex3f(-100.0, 100.0, 100.0);
		glColor3f(0.0f, 0.0f, 1.0f);		// Blue
		glVertex3f(-100.0, 100.0, -100.0);
		glColor3f(1.0f, 0.0, 1.0f);			// Magenta
		glVertex3f(-100.0, -100.0, -100.0);
		glColor3f(0.0f, 1.0f, 1.0f);		// Cyan
		glVertex3f(-100.0, -100.0, 100.0);
		glEnd();
	glPopMatrix();

}
void CManager::UpdateUpCover()
{
	if (UpCoverAnimation)
	{
		if (90 > UpCoverAngle)
		{
			UpCoverAngle+= 3;
			UpCircleTranslate+=5;
			UpSpringScale += 0.4;
		}
	}
	else
	{
		if (0 < UpCoverAngle)
		{
			UpCoverAngle -= 3;
			UpCircleTranslate-=5;
			UpSpringScale -= 0.4;
		}
	}
}
void CManager::UpdateFrontCover()
{
	if (FrontCoverAnimation)
	{
		if (90 > FrontCoverAngle)
		{
			FrontCoverAngle+= 3;
			FrontCircleTranslate += 7;
			FrontCircleRotate += 3;
		}
	}
	else
	{
		if (0 < FrontCoverAngle)
		{
			FrontCoverAngle -= 3;
			FrontCircleTranslate -= 7;
			FrontCircleRotate -= 3;
		}
	}
}

void CManager::DrawUpCircle()
{
	glPushMatrix();
		glTranslatef(0.0, UpCircleTranslate, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glutWireSphere(75, 50, 10);
	glPopMatrix();
}
void CManager::DrawUpSpring()
{
	int SpringAngle = 0;
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f); 
		glPointSize(20.0f);
		glScalef(1.0, -UpSpringScale, 1.0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 1000; i++)
		{
			glVertex3f(
				sin(GetRadian(SpringAngle)) * 75,
				i * 0.01 - 10,
				cos(GetRadian(SpringAngle)) * 75
				);
			SpringAngle = (SpringAngle + 3) % 360;
		}
		glEnd();
	glPopMatrix();
	//CirclePoint[i][0] = sin(GetRadian(Angle)) * CIRCLE_RADIUS;
	//CirclePoint[i][1] = cos(GetRadian(Angle)) * CIRCLE_RADIUS;
}
void CManager::DrawFrontCircle()
{
	glPushMatrix();
		glTranslatef(-FrontCircleTranslate, 0.0, 0.0);
		glRotatef(FrontCircleRotate, 0.0, 0.0, 1.0);
		glColor3f(0.5, 0.5, 0.5);
		glutWireSphere(75, 50, 10);
	glPopMatrix();

}
