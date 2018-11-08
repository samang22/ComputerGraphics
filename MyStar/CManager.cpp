#include "pch.h"
#include "CManager.h"
#include <gl/freeglut.h>
#include <stdlib.h>
#include <time.h>

#define RECT_INIT_X 0
#define RECT_INIT_Y -400
#define RECT_LENGTH 50
#define RECT_GENERATE_COOLTIME 500

#define TRI_INIT_X -450
#define TRI_INIT_Y 250
#define TRI_LENGTH 50
#define TRI_GENERATE_COOLTIME 100

#define TRI_ABOVE 0
#define TRI_FALLING_LEFT_ROTATE 1
#define TRI_FALLING_RIGHT_ROTATE 2
#define TRI_FALLING_LEFT_STOP 3
#define TRI_FALLING_RIGHT_STOP 4
#define TRI_HOLDED 5
#define TRI_STOP 6

#define STAR_STOP 0
#define STAR_MOVE 1


float GetRadian(int _Num)
{
	return (float)(_Num * (3.1415926545 / 180));
}

CManager::CManager() : RectGenerateCount(1000), TriGenerateCount(30), MouseIsStart(false), StartPoint({ 0, 0 }), EndPoint({0, 0})
{
	memset(FallenTriStack, 0, sizeof(int) * 14);
	CurrentPoint = { 0, 0 };
	StartPoint = { 0, 0 };
	EndPoint = { 0, 0 };
}

CManager::~CManager()
{
}
void CManager::Init()
{

}

void CManager::Draw()
{

	//glColor3f(0.5, 0.5, 0.5);
	//glPushMatrix();
	//glRotatef(270, 0.0, 0.0, 1.0);
	//glBegin(GL_TRIANGLES);
	//glVertex3f(0 - 25, 0 + 25, 0.0);
	//glVertex3f(0 - 25, 0 - 25, 0.0);
	//glVertex3f(0 + 25, 0 - 25, 0.0);
	//glEnd();
	//glPopMatrix();

	DrawStar();
	DrawGrid();
	DrawRect();
	DrawTri();
	DrawDrag();
	DrawSplittedTri();
}
void CManager::Update()
{
	RectGenerateCount++;
	TriGenerateCount++;
	if (RectGenerateCount >= RECT_GENERATE_COOLTIME)
	{
		RectGenerateCount = 0;
		GenerateRectangle();
	}
	if (TriGenerateCount >= TRI_GENERATE_COOLTIME)
	{
		TriGenerateCount = 0;
		GenerateAboveTriangle();
	}
	UpdateRect();
	UpdateAboveTri();
	UpdateSplittedTri();
	UpdateStar();
}
void CManager::GetMouseEvent(int button, int state, float x, float y)
{
	if (state == GLUT_DOWN)
	{
		if (IsFallingTri())
		{
			CheckTriClicked(x - 400, 300 - y);
		}
		else if (false == IsHoldedTri())
		{
			DragStart();
			SetStartPoint(x - 400, 300 - y);
			SetEndPoint(x - 400, 300 - y);
		}
	}
	if (state == GLUT_UP)
	{
		if (IsHoldedTri())
		{
			SetHoldedToFalling();
			return;
		}
		DragDone();
	}
}
void CManager::GetMouseMotion(float x, float y)
{
	if (300 - y > 225)
	{
		int a = 0;
	}
	if (IsHoldedTri())
	{
		SetCurrentPoint(x - 400, 300 - y);
	}
	SetEndPoint(x - 400, 300 - y);
}

void CManager::UpdateRect()
{
	std::list<Rect>::iterator iter;
	for (iter = RectList.begin(); iter != RectList.end(); iter++)
	{
		iter->Y++;
		//iter->Up++;
		if (iter->Y > 200)
		{
			iter->R -= (float)0.0125;
			iter->G -= (float)0.0125;
			iter->B -= (float)0.0125;
		}
	}
}
void CManager::UpdateAboveTri()
{
	std::list<Tri>::iterator iter;
	for (iter = AboveTriList.begin(); iter != AboveTriList.end(); iter++)
	{
		iter->X++;
		
	}
	if (IsHoldedTri())
	{
		std::list<Tri>::iterator iter;
		for (iter = AboveTriList.begin(); iter != AboveTriList.end(); iter++)
		{
			if (CheckAboveHoldedCollision(iter->X, iter->Y))
			{
				GenerateStar(iter->X, iter->Y);
				AboveTriList.erase(iter);
				DeleteHoldedTri();
				break;
			}
		}
	}

}
void CManager::UpdateSplittedTri()
{
	std::list<Tri>::iterator iter;
	for (iter = SplittedTriList.begin(); iter != SplittedTriList.end(); iter++)
	{
		if (iter->State == TRI_STOP)
		{
			continue;
		}

		if (TRI_HOLDED == iter->State)
		{
			iter->X = CurrentPoint.X;
			iter->Y = CurrentPoint.Y;
			continue;
		}


		// X축 이동
		switch (iter->FallPos)
		{
			// 왼쪽
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			if (-400 + (RECT_LENGTH) / 2 + (RECT_LENGTH)* iter->FallPos < iter->X)
			{
				iter->X -= 3;
			}
			break;
			// 오른쪽
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
			if (50 + (RECT_LENGTH) / 2 + (RECT_LENGTH) * (iter->FallPos - 7) > iter->X)
			{
				iter->X += 3;
			}
			break;
		default:
			break;
		}




		// Y축 이동
		iter->Y--;
		// 스택에 얼마나 쌓여있는지 확인
		switch (FallenTriStack[iter->FallPos])
		{
		case 0:
		case 1:
			if (iter->Y <= -300 + TRI_LENGTH / 2)
			{
				if (iter->State == TRI_FALLING_LEFT_STOP)
					iter->State = TRI_STOP;
				else if (TRI_FALLING_RIGHT_STOP)
					iter->State = TRI_STOP;
				FallenTriStack[iter->FallPos] += 1;
			}
			break;
		case 2:
		case 3:
			if (iter->Y <= -250 + TRI_LENGTH / 2)
			{
				if (iter->State == TRI_FALLING_LEFT_STOP)
					iter->State = TRI_STOP;
				else if (TRI_FALLING_RIGHT_STOP)
					iter->State = TRI_STOP;
				FallenTriStack[iter->FallPos] += 1;
			}
			break;
		case 4:
		case 5:
			if (iter->Y <= -200 + TRI_LENGTH / 2)
			{
				if (iter->State == TRI_FALLING_LEFT_STOP)
					iter->State = TRI_STOP;
				else if (TRI_FALLING_RIGHT_STOP)
					iter->State = TRI_STOP;
				FallenTriStack[iter->FallPos] += 1;
			}
			break;
		default:
			break;
		}


		// 회전
		if (TRI_FALLING_LEFT_STOP == iter->State || TRI_FALLING_RIGHT_STOP == iter->State)
		{
			continue;
		}
		// 일정 이상은 그냥 회전
		if (iter->Y > -80)
		{
			iter->Angle = (iter->Angle + 3) % 360;
		}
		// 일정이하가 되면 체크
		else if (iter->Y <= -80)
		{
			//		Angle이 0이 되야하는 경우				 
			if (FallenTriStack[iter->FallPos] % 2 == 0)
			{
				// Angle이 0이 되서 그만돌기
				if (iter->Angle == 0)
				{
					if (iter->State == TRI_FALLING_LEFT_ROTATE)
					{
						iter->State = TRI_FALLING_LEFT_STOP;
					}
					else if (iter->State == TRI_FALLING_RIGHT_ROTATE)
					{
						iter->State = TRI_FALLING_RIGHT_STOP;
					}
				}
				// Angle이 0이 아니면 맞추기
				else if (iter->Angle != 0 && iter->State != TRI_STOP)
					iter->Angle = (iter->Angle + 3) % 360;
			}
			//		Angle이 180이 되야하는 경우			
			else if (FallenTriStack[iter->FallPos] % 2 == 1)
			{
				// Angle이 180이 되서 그만돌기
				if (iter->Angle == 180)
				{
					if (iter->State == TRI_FALLING_LEFT_ROTATE)
					{
						iter->State = TRI_FALLING_LEFT_STOP;
					}
					else if (iter->State == TRI_FALLING_RIGHT_ROTATE)
					{
						iter->State = TRI_FALLING_RIGHT_STOP;
					}
				}
				// Angle이 180이 아니면 계속 돌기
				else if (iter->Angle != 180 && iter->State != TRI_STOP)
					iter->Angle = (iter->Angle + 3) % 360;
			}
		}
	}

}
void CManager::UpdateStar()
{
	//static int CoolTime = 0;
	//int Alpha = 0, Beta = 0;
	//CoolTime = (CoolTime + 1) % 10;
	//std::list<Star>::iterator iter;
	//for (iter = StarList.begin(); iter != StarList.end(); iter++)
	//{
	//	iter->Angle = (iter->Angle + 1) % 360;
	//	if (STAR_STOP == iter->State)
	//	{
	//		continue;
	//	}
	//	//Alpha = tan(atan2(iter->Y - iter->GoalY, iter->X - iter->GoalX));
	//	Alpha = (float)((iter->GoalY - iter->Y) / (iter->GoalX - iter->X));
	//	Beta = iter->Y - tan(atan2(iter->Y - iter->GoalY, iter->X - iter->GoalX)) * iter->X;

	//	if (CoolTime >= 9)
	//	{
	//		if (iter->X > iter->GoalX)
	//		{
	//			iter->X -= 1;
	//		}
	//		else
	//		{
	//			iter->X += 1;
	//		}
	//		iter->Y = Alpha * iter->X + Beta;
	//	}
	//	if (iter->GoalX == iter->X)
	//	{
	//		iter->State = STAR_STOP;
	//	}
	//}
	//static int CoolTime = 0;
	//CoolTime = (CoolTime + 1) % 10;

	//if (CoolTime < 9)
	//{
	//	return;
	//}
	int DestX = 0, DestY = 0;
	int Distance = 0;

	std::list<Star>::iterator iter;
	for (iter = StarList.begin(); iter != StarList.end(); iter++)
	{
		iter->Angle = (iter->Angle + 1) % 360;
		iter->R += (iter->R + 0.0001);
		if (iter->R >= 1)
		{
			iter->R = 0;
		}
		iter->G += (iter->G + 0.0001);
		if (iter->G >= 1)
		{
			iter->G = 0;
		}
		iter->B += (iter->B + 0.0001);
		if (iter->B >= 1)
		{
			iter->B = 0;
		}

		if (STAR_STOP == iter->State)
		{
			continue;
		}
		DestX = iter->GoalX;
		DestY = iter->GoalY;
		Distance = sqrt(DestX * DestX + DestY * DestY);

		if (Distance > 0)
		{
			iter->X += (float)(DestX / Distance);
			iter->Y += (float)(DestY / Distance);
		}

		if (DestX < 0 && iter->X < iter->GoalX)
			iter->X = iter->GoalX;
		if (DestX > 0 && iter->X > iter->GoalX)
			iter->X = iter->GoalX;
		if (DestY < 0 && iter->Y < iter->GoalY)
			iter->Y = iter->GoalY;
		if (DestY > 0 && iter->X > iter->GoalX)
			iter->Y = iter->GoalY;


		if (iter->GoalX == iter->X)
		{
			iter->State = STAR_STOP;
		}
	}

}


void CManager::DeleteRect()
{
	std::list<Rect>::iterator iter;
	for (iter = RectList.begin(); iter != RectList.end(); iter++)
	{
		if (iter->R < 0)
		{
			RectList.erase(iter);
			break;
		}
	}
}
void CManager::DeleteTri()
{
	std::list<Tri>::iterator iter;
	for (iter = AboveTriList.begin(); iter != AboveTriList.end(); iter++)
	{
		if (iter->X > 300)
		{
			AboveTriList.erase(iter);
			break;
		}
	}
}
void CManager::DeleteHoldedTri()
{
	std::list<Tri>::iterator iter;
	for (iter = SplittedTriList.begin(); iter != SplittedTriList.end(); iter++)
	{
		if (iter->State == TRI_HOLDED)
		{
			SplittedTriList.erase(iter);
			break;
		}
	}
}

void CManager::GetCommand(char _key)
{
	switch (_key)
	{
	case 'q':
	case 'Q':
		break;
	case 'w':
	case 'W':
		break;
	case 'e':
	case 'E':
		break;
	case 'r':
	case 'R':
		break;
	case 't':
	case 'T':
		break;
	case 's':
	case 'S':
		break;
	case 'd':
	case 'D':
		break;
	case 'f':
	case 'F':
		break;
	case 'g':
	case 'G':
		break;
	default:
		break;
	}
}
void CManager::DrawGrid()
{
	glColor3f(1.0, 1.0, 1.0);
	// 가로
	for (int i = 0; i < 3; i++)
	{
		glBegin(GL_LINES);
		//glVertex3f(-400.0, TempY, 0.0);
		//glVertex3f(400.0, TempY, 0.0);
		glVertex3f(-400.0, (float)((i + 1) * 50 - 300), 0.0);
		glVertex3f(400.0, (float)((i + 1) * 50 - 300), 0.0);
		glEnd();
	}
	// 세로
	for (int i = 0; i < 20; i++)
	{
		glBegin(GL_LINES);
		//glVertex3f((i + 1) * 50 , 0.0, 0.0);
		//glVertex3f((i + 1) * 50 , 150.0, 0.0);
		glVertex3f((i + 1) * 50 - 400, -300.0, 0.0);
		glVertex3f((i + 1) * 50 - 400, -150.0, 0.0);
		glEnd();
	}
	// 상단
	glBegin(GL_LINES);
	glVertex3f(-400.0 , 200.0, 0.0);
	glVertex3f(400.0, 200.0, 0.0);
	glEnd();
}
void CManager::DrawRect()
{
	std::list<Rect>::iterator iter;
	for (iter = RectList.begin(); iter != RectList.end(); iter++)
	{
		glColor3f(iter->R, iter->G, iter->B);
		glPushMatrix();
			if (iter->Rotate)
			{
				glPushMatrix();
					glTranslatef(0, iter->Y, 0);
					glRotatef(45, 0.0, 0.0, 1.0);
					glTranslatef(0, -iter->Y, 0);
					//glTranslatef(0, iter->Up, 0);
					glRectf(iter->X - iter->Length / 2, iter->Y + iter->Length / 2, iter->X + iter->Length / 2, iter->Y - iter->Length / 2);
				glPopMatrix();
			}
			else
			{
				//glTranslatef(0, iter->Up, 0);
				glRectf(iter->X - iter->Length / 2, iter->Y + iter->Length / 2, iter->X + iter->Length / 2, iter->Y - iter->Length / 2);
				glPopMatrix();

			}
		glPopMatrix();
	}
}
void CManager::DrawTri()
{
	std::list<Tri>::iterator iter;
	for (iter = AboveTriList.begin(); iter != AboveTriList.end(); iter++)
	{
		glColor3f(iter->R, iter->G, iter->B);
		glPushMatrix();
			glTranslatef(iter->X, iter->Y, 0);
			glRotatef(iter->Angle, 0.0, 0.0, 1.0);
			glTranslatef(-iter->X, -iter->Y, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(iter->X - iter->Length / 2, iter->Y + iter->Length / 2, 0.0);
			glVertex3f(iter->X - iter->Length / 2, iter->Y - iter->Length / 2, 0.0);
			glVertex3f(iter->X + iter->Length / 2, iter->Y - iter->Length / 2, 0.0);
			glEnd();
		glPopMatrix();
	}
}
void CManager::DrawDrag()
{
	if (false == GetIsStart())
	{
		return;
	}
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(StartPoint.X, StartPoint.Y, 0.0);
	glVertex3f(EndPoint.X, EndPoint.Y, 0.0);
	glEnd();
}
void CManager::DrawSplittedTri()
{
	std::list<Tri>::iterator iter;
	for (iter = SplittedTriList.begin(); iter != SplittedTriList.end(); iter++)
	{
		glColor3f(iter->R, iter->G, iter->B);
		glPushMatrix();
			glTranslatef(iter->X, iter->Y, 0);
			glRotatef(iter->Angle, 0.0, 0.0, 1.0);
			glTranslatef(-iter->X, -iter->Y, 0);
			glBegin(GL_TRIANGLES);
			glVertex3f(iter->X - iter->Length / 2, iter->Y + iter->Length / 2, 0.0);
			glVertex3f(iter->X - iter->Length / 2, iter->Y - iter->Length / 2, 0.0);
			glVertex3f(iter->X + iter->Length / 2, iter->Y - iter->Length / 2, 0.0);
			glEnd();
		glPopMatrix();
	}
}
void CManager::DrawStar()
{
	std::list<Star>::iterator iter;
	for (iter = StarList.begin(); iter != StarList.end(); iter++)
	{
		glColor3f(iter->R, iter->G, iter->B);
		glPushMatrix();
		glTranslatef(iter->X, iter->Y, 0);
		glRotatef(iter->Angle, 0.0, 0.0, 1.0);
		glTranslatef(-iter->X, -iter->Y, 0);
		glBegin(GL_TRIANGLES);
		glVertex3f(iter->X					 , iter->Y + iter->Length / 2, 0.0);
		glVertex3f(iter->X - iter->Length / 2, iter->Y - iter->Length / 2, 0.0);
		glVertex3f(iter->X + iter->Length / 2, iter->Y - iter->Length / 2, 0.0);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(iter->X - iter->Length / 2, iter->Y - (iter->Length / 3) + iter->Length / 2, 0.0);
		glVertex3f(iter->X					 , iter->Y - (iter->Length / 3) - iter->Length / 2, 0.0);
		glVertex3f(iter->X + iter->Length / 2, iter->Y - (iter->Length / 3) + iter->Length / 2, 0.0);
		glEnd();
		glPopMatrix();
	}

}


void CManager::GenerateRectangle()
{
	srand(time(0));
	Rect TempRect = { 
		RECT_INIT_X,
		RECT_INIT_Y,
		RECT_LENGTH,
		(bool)(rand() % 2),
		//true,
		//false,
		1.0,
		1.0,
		1.0,
		//0
	};
	RectList.push_back({TempRect});
}
void CManager::GenerateAboveTriangle()
{
	srand(time(0));
	Tri TempTri = {
		TRI_INIT_X,
		TRI_INIT_Y,
		TRI_LENGTH,
		(rand() % 180) + (rand() % 180),
		//true,
		1.0,
		1.0,
		1.0,
		TRI_STOP,
		-1
		//0
	};
	AboveTriList.push_back({ TempTri });
}
void CManager::GenerateStar(float _X, float _Y)
{
	srand(time(0));
	Star TempStar = {
		_X,
		_Y,
		rand() % 400 - 200 + rand() % 400 - 200,
		rand() % 100 - 50 + rand() % 100 - 50,
		TRI_LENGTH * 2,
		0,
		STAR_MOVE,
		(float)((rand() % 10 + 1) * 0.1),
		(float)((rand() % 10 + 1) * 0.1),
		(float)((rand() % 10 + 1) * 0.1)
	};

	StarList.push_back(TempStar);
}


void CManager::SetStartPoint(float _X, float _Y)
{
	StartPoint = { _X, _Y };
}
void CManager::SetEndPoint(float _X, float _Y)
{
	EndPoint = { _X, _Y };
}
void CManager::SetCurrentPoint(float _X, float _Y)
{
	CurrentPoint = { _X, _Y };
}

bool CManager::GetIsStart()
{
	return MouseIsStart;
}
void CManager::DragStart()
{
	//StartPoint = { 0, 0 };
	//EndPoint = { 0, 0 };
	MouseIsStart = true;
}

void CManager::DragDone()
{
	MouseIsStart = false;
	std::list<Rect>::iterator iter;
	for (iter = RectList.begin(); iter != RectList.end(); iter++)
	{
		if (CheckDragRectCollision(*iter) && iter->Y > -100 && false == IsFallingTri())
		{
			SplitRect(iter->Rotate, iter->X, iter->Y);
			RectList.erase(iter);
			break;
		}
	}
}

bool CManager::CheckDragRectCollision(Rect _Rect)
{
	// 정방향
	// 좌하우상
	if (_Rect.X + (_Rect.Length / 2) * sqrt(2) >= EndPoint.X
		&& _Rect.X - (_Rect.Length / 2) * sqrt(2) <= StartPoint.X
		&& _Rect.Y + (_Rect.Length / 2) * sqrt(2) <= StartPoint.Y
		&& _Rect.Y - (_Rect.Length / 2) * sqrt(2) >= EndPoint.Y
		&& false == _Rect.Rotate
		)
	{
		printf("true\n");
		return true;
	}	
	// 좌상우하
	else if (_Rect.X + (_Rect.Length / 2) * sqrt(2) <= EndPoint.X
		&& _Rect.X - (_Rect.Length / 2) * sqrt(2) >= StartPoint.X
		&& _Rect.Y + (_Rect.Length / 2) * sqrt(2) <= StartPoint.Y
		&& _Rect.Y - (_Rect.Length / 2) * sqrt(2) >= EndPoint.Y
		&& false == _Rect.Rotate)
	{
		printf("true\n");
		return true;
	}

	// 우상좌하
	else if (_Rect.X + (_Rect.Length / 2) * sqrt(2) <= StartPoint.X
		&& _Rect.X - (_Rect.Length / 2) * sqrt(2) >= EndPoint.X
		&& _Rect.Y + (_Rect.Length / 2) * sqrt(2) <= StartPoint.Y
		&& _Rect.Y - (_Rect.Length / 2) * sqrt(2) >= EndPoint.Y
		&& false == _Rect.Rotate
		)
	{
		printf("true\n");
		return true;
	}
	// 우하좌상
	else if (_Rect.X + (_Rect.Length / 2) * sqrt(2) <= StartPoint.X
		&& _Rect.X - (_Rect.Length / 2) * sqrt(2) >= EndPoint.X
		&& _Rect.Y + (_Rect.Length / 2) * sqrt(2) <= EndPoint.Y
		&& _Rect.Y - (_Rect.Length / 2) * sqrt(2) >= StartPoint.Y

		&& false == _Rect.Rotate)
	{
		printf("true\n");
		return true;
	}
	
	// 역방향

	// 상하
	if (_Rect.X + 15 >= StartPoint.X
		&& _Rect.X - 15 <= StartPoint.X
		&& _Rect.X + 15 >= EndPoint.X
		&& _Rect.X - 15 <= EndPoint.X
		&& _Rect.Y + (RECT_LENGTH / 2) * sqrt(2) <= StartPoint.Y
		&& _Rect.Y - (RECT_LENGTH / 2) * sqrt(2) >= EndPoint.Y
		&& true == _Rect.Rotate
		)
	{
		printf("true\n");
		return true;
	}
	// 좌우
	if (_Rect.Y + 15 >= StartPoint.Y
		&& _Rect.Y - 15 <= StartPoint.Y
		&& _Rect.Y + 15 >= EndPoint.Y
		&& _Rect.Y - 15 <= EndPoint.Y
		&& _Rect.X - (RECT_LENGTH / 2) * sqrt(2) <= StartPoint.Y
		&& _Rect.X + (RECT_LENGTH / 2) * sqrt(2) >= EndPoint.Y
		&& true == _Rect.Rotate
		)
	{
		printf("true\n");
		return true;
	}

	return false;
}

void CManager::SplitRect(bool _Rotate, float _X, float _Y)
{
	srand(time(0));
	Tri TempLeft, TempRight;
	// 회전
	if (_Rotate)
	{
		TempLeft = {
			_X,
			_Y,
			TRI_LENGTH,
			45,
			1.0,
			1.0,
			1.0,
			TRI_FALLING_LEFT_ROTATE,
			(rand() % 7)
		};
		TempRight = {
			_X,
			_Y,
			TRI_LENGTH,
			45 + 180,
			1.0,
			1.0,
			1.0,
			TRI_FALLING_RIGHT_ROTATE,
			7 + (rand() % 7)
		};
	}
	// 정방향
	else
	{
		TempLeft = {
			_X,
			_Y,
			TRI_LENGTH,
			0,
			1.0,
			1.0,
			1.0,
			TRI_FALLING_LEFT_ROTATE,
			//(rand() % 7)
			0
		};
		TempRight = {
			_X,
			_Y,
			TRI_LENGTH,
			180,
			1.0,
			1.0,
			1.0,
			TRI_FALLING_RIGHT_ROTATE,
			7 + (rand() % 7)
		};
	}
	SplittedTriList.push_back({ TempLeft });
	SplittedTriList.push_back({ TempRight });
}


bool CManager::IsFallingTri()
{
	std::list<Tri>::iterator iter;
	for (iter = SplittedTriList.begin(); iter != SplittedTriList.end(); iter++)
	{
		if (iter->State != TRI_STOP)
		{
			return true;
		}
	}
	return false;
}
bool CManager::IsHoldedTri()
{
	std::list<Tri>::iterator iter;
	for (iter = SplittedTriList.begin(); iter != SplittedTriList.end(); iter++)
	{
		if (TRI_HOLDED == iter->State)
		{
			return true;
		}
	}
	return false;
}
bool CManager::CheckTriClicked(float _X, float _Y)
{
	std::list<Tri>::iterator iter;
	for (iter = SplittedTriList.begin(); iter != SplittedTriList.end(); iter++)
	{
		if (iter->X + TRI_LENGTH / 2 >= _X
			&& iter->X - TRI_LENGTH / 2 <= _X
			&& iter->Y - TRI_LENGTH / 2 <= _Y
			&& iter->Y + TRI_LENGTH / 2 >= _Y
			)
		{
			iter->State = TRI_HOLDED;
			return true;
		}
	}
}

void CManager::SetHoldedToFalling()
{
	srand(time(0));
	std::list<Tri>::iterator iter;
	for (iter = SplittedTriList.begin(); iter != SplittedTriList.end(); iter++)
	{
		if (TRI_HOLDED == iter->State)
		{
			if (rand() % 2)
			{
				iter->State = TRI_FALLING_LEFT_ROTATE;
			}
			else
			{
				iter->State = TRI_FALLING_LEFT_ROTATE;
			}
		}
	}
}

bool CManager::CheckAboveHoldedCollision(float _X, float _Y)
{
	if (_X + TRI_LENGTH / 2 >= CurrentPoint.X
		&& _X - TRI_LENGTH / 2 <= CurrentPoint.X
		&& _Y - TRI_LENGTH / 2 <= CurrentPoint.Y
		&& _Y + TRI_LENGTH / 2 >= CurrentPoint.Y
		)
	{
		return true;
	}
	return false;
}
