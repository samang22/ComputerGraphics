#include "CManager.h"
#include <gl/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INIT_Y_ANGLE 45

#define XPYP 0
#define XPYM 1
#define XMYP 2
#define XMYM 3


float GetRadian(float _Num)
{
	return (float)(_Num * (3.1415926545 / 180));
}

CManager::CManager() : IsFlat(false), IsDepthEnable(true), IsCulling(false),
YRotateAngle(INIT_Y_ANGLE),ZRotateAngle(0), XTranslate(0), YTranslate(0)
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
		glRotatef(ZRotateAngle, 0.0, 0.0, 1.0);


		DrawBox();
		DrawBalls();
		glPushMatrix();
	
			glPushMatrix();
				// 각도에 따라 움직이기
				if (XTranslate < 100 - 10.0)
				{
					glTranslatef(XTranslate + 10.0, 0.0, 0.0);
				}
				else
				{
					glTranslatef(100- 10.0, 0.0, 0.0);
				}

				//glTranslatef(0.0, YTranslate/* - 7.0*/, 0.0);
				if (YTranslate < 10.0 * 2)
				{
					glTranslatef(0.0, 0, 0.0);
				}
				else
				{
					glTranslatef(0.0, YTranslate - 10.0 * 2, 0.0);
					//glTranslatef(0.0, YTranslate/* - 10.0 * 2*/, 0.0);
				}

				// 바닥에 붙이기
				glTranslatef(0.0, -(100.0 - 10.0), 70.0);
				glColor3f(0.0, 0.0, 0.0);
				glutWireCube(10.0 * 2);
				DrawFallingBoxes(10.0);
			glPopMatrix();
	
			glPushMatrix();
				// 각도에 따라 움직이기
				if (XTranslate < 100 - 7.0)
				{
					glTranslatef(XTranslate + 7.0, 0.0, 0.0);
				}
				else
				{
					glTranslatef(100 - 7.0, 0.0, 0.0);
				}



				if (YTranslate < 7.0 * 2)
				{
					glTranslatef(0.0, 0.0, 0.0);
				}
				else
				{
					glTranslatef(0.0, YTranslate - 7.0 * 2, 0.0);
					//glTranslatef(0.0, YTranslate/* - 7.0*/, 0.0);
				}
				// 바닥에 붙이기
				glTranslatef(0.0, -(100.0 - 7.0), -50.0);
				glColor3f(0.0, 0.0, 0.0);
				glutWireCube(7.0 * 2);
				DrawFallingBoxes(7.0);
			glPopMatrix();
	
			glPushMatrix();
				// 각도에 따라 움직이기
				if (XTranslate < 100 - 8.0)
				{
					glTranslatef(XTranslate + 8.0, 0.0, 0.0);
				}
				else
				{
					glTranslatef(100 - .0, 0.0, 0.0);
				}


				if (YTranslate < 8.0 * 2)
				{
					glTranslatef(0.0, 0.0, 0.0);
				}
				else
				{
					//glTranslatef(0.0, YTranslate/* - 8.0*/, 0.0);
					glTranslatef(0.0, YTranslate - 8.0 * 2, 0.0);
				}

				// 바닥에 붙이기
				glTranslatef(0.0, -(100.0 - 8.0), 0.0);
				glColor3f(0.0, 0.0, 0.0);
				glutWireCube(8.0 * 2);
				DrawFallingBoxes(8.0);
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 3000.0, 0.0);
	glVertex3f(0.0, -3000.0, 0.0);
	glEnd();
}

void CManager::Update()
{
	if (0 < ZRotateAngle && 90 > ZRotateAngle)
	{
		if (XTranslate > -100)
		{
			XTranslate -= 2;
		}
	}
	else if (90 < ZRotateAngle && 180 > ZRotateAngle)
	{
		if (YTranslate < 200)
		{
			YTranslate += 2;
		}
	}
	else if (180 < ZRotateAngle && 270 > ZRotateAngle)
	{
		if (XTranslate < 100)
		{
			XTranslate += 2;
		}
	}
	else if (270 < ZRotateAngle && 360 > ZRotateAngle)
	{
		if (YTranslate > 0)
		{
			YTranslate -= 2;
		}
	}
	UpdateBalls();
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
	case 'z':
	case 'Z':
		ZRotateAngle = (ZRotateAngle + 5) % 360;
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
	case 'b':
	case 'B':
		GenerateBalls();
		break;
	default:
		break;
	}

	SetMode();
}

void CManager::DrawBox()
{
	glPushMatrix();

	 //아래
		glColor3f(0.5f, 0.5f, 0.5f);		// 중간회색
		glBegin(GL_QUADS);
		glVertex3f(100.0, -100.0, 100.0);
		glVertex3f(100.0, -100.0, -100.0);
		glVertex3f(-100.0, -100.0, -100.0);
		glVertex3f(-100.0, -100.0, 100.0);
		glEnd();
	
		// 오른쪽
		glColor3f(0.1f, 0.1f, 0.1f);		// 어두운회색
		glBegin(GL_QUADS);
		glVertex3f(100.0, 100.0, 100.0);
		glVertex3f(100.0, 100.0, -100.0);
		glVertex3f(100.0, -100.0, -100.0);
		glVertex3f(100.0, -100.0, 100.0);
		glEnd();
	
		// 뒤
		glColor3f(0.6f, 0.6f, 0.6f);		// 어두운회색
		glBegin(GL_QUADS);
		glVertex3f(100.0, 100.0, -100.0);
		glVertex3f(100.0, -100.0, -100.0);
		glVertex3f(-100.0, -100.0, -100.0);
		glVertex3f(-100.0, 100.0, -100.0);
		glEnd();
	
		// 위
		glColor3f(0.5f, 0.5f, 0.5f);		// 어두운회색
		glBegin(GL_QUADS);
		glVertex3f(100.0, 100.0, 100.0);
		glVertex3f(100.0, 100.0, -100.0);
		glVertex3f(-100.0, 100.0, -100.0);
		glVertex3f(-100.0, 100.0, 100.0);
		glEnd();
	
		// 왼쪽
		glColor3f(0.3f, 0.3f, 0.3f);		// 어두운회색
		glBegin(GL_QUADS);
		glVertex3f(-100.0, 100.0, 100.0);
		glVertex3f(-100.0, 100.0, -100.0);
		glVertex3f(-100.0, -100.0, -100.0);
		glVertex3f(-100.0, -100.0, 100.0);
		glEnd();



	glPopMatrix();

}
void CManager::DrawFallingBoxes(float _Radius)
{
	//아래
	glColor3f(1.0f, 0.0f, 0.0f);		// 중간회색
	glBegin(GL_QUADS);
	glVertex3f(_Radius, -_Radius, _Radius);
	glVertex3f(_Radius, -_Radius, -_Radius);
	glVertex3f(-_Radius, -_Radius, -_Radius);
	glVertex3f(-_Radius, -_Radius, _Radius);
	glEnd();

	// 오른쪽
	glBegin(GL_QUADS);
	glVertex3f(_Radius, _Radius, _Radius);
	glVertex3f(_Radius, _Radius, -_Radius);
	glVertex3f(_Radius, -_Radius, -_Radius);
	glVertex3f(_Radius, -_Radius, _Radius);
	glEnd();

	// 뒤
	glBegin(GL_QUADS);
	glVertex3f(_Radius, _Radius, -_Radius);
	glVertex3f(_Radius, -_Radius, -_Radius);
	glVertex3f(-_Radius, -_Radius, -_Radius);
	glVertex3f(-_Radius, _Radius, -_Radius);
	glEnd();

	// 뒤
	glBegin(GL_QUADS);
	glVertex3f(_Radius, _Radius, _Radius);
	glVertex3f(_Radius, -_Radius, _Radius);
	glVertex3f(-_Radius, -_Radius, _Radius);
	glVertex3f(-_Radius, _Radius, _Radius);
	glEnd();


	// 위
	glBegin(GL_QUADS);
	glVertex3f(_Radius, _Radius,_Radius);
	glVertex3f(_Radius, _Radius, -_Radius);
	glVertex3f(-_Radius, _Radius, -_Radius);
	glVertex3f(-_Radius, _Radius, _Radius);
	glEnd();

	// 왼쪽
	glBegin(GL_QUADS);
	glVertex3f(-_Radius, _Radius, _Radius);
	glVertex3f(-_Radius, _Radius, -_Radius);
	glVertex3f(-_Radius, -_Radius, -_Radius);
	glVertex3f(-_Radius, -_Radius, _Radius);
	glEnd();

}
void CManager::DrawBalls()
{
	glColor3f(0.0, 0.0, 1.0);
	std::list<Ball>::iterator iter;
	for (iter = BallList.begin(); iter != BallList.end(); iter++)
	{
		glPushMatrix();
			glTranslatef(iter->X, iter->Y, iter->Z);
			glutSolidSphere(10.0, 10.0, 10.0);
		glPopMatrix();
	}
}

void CManager::UpdateBalls()
{
	std::list<Ball>::iterator iter;
	for (iter = BallList.begin(); iter != BallList.end(); iter++)
	{
		switch (iter->Move)
		{
		case XPYP:
			iter->X++;
			iter->Y++;
			break;
		case XPYM:
			iter->X++;
			iter->Y--;
			break;
		case XMYP:
			iter->X--;
			iter->Y++;
			break;
		case XMYM:
			iter->X--;
			iter->Y--;
			break;
		default:
			break;
		}
		

		if (iter->X >= 100 - 10)
		{
			if (iter->Move == XPYP)
			{
				iter->Move = XMYP;
			}
			else if (iter->Move == XPYM)
			{
				iter->Move = XMYM;
			}
		}
		else if (iter->X <= -100 + 10)
		{
			if (iter->Move == XMYP)
			{
				iter->Move = XPYP;
			}
			else if (iter->Move == XMYM)
			{
				iter->Move = XPYM;
			}
		}

		if (iter->Y >= 100 - 10)
		{
			if (iter->Move == XPYP)
			{
				iter->Move = XPYM;
			}
			else if (iter->Move == XMYP)
			{
				iter->Move = XMYM;
			}
		}
		else if (iter->Y <= -100 + 10)
		{
			if (iter->Move == XPYM)
			{
				iter->Move = XPYP;
			}
			else if (iter->Move == XMYM)
			{
				iter->Move = XMYP;
			}
		}


	}
}


void CManager::GenerateBalls()
{
	if (BallList.size() < 5)
	{
		srand((size_t)time(0));
		BallList.push_back({(float)(rand() % 200 - 100), (float)(rand() % 200 - 100) , (float)(rand() % 200 - 100), rand() % 4 });
	}
}
