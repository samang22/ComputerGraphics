#include "pch.h"
#include "CManager.h"
#include <string.h>
#include <math.h>
#include <gl/freeglut.h>
float GetRadian(int _Num)
{
	return _Num * (3.1415926545 / 180);
}
CManager::CManager() : Mode_Course('0'), Figure(TRIANGLE), Z_Rotate_Switch(false), Tornado_Radius(50),
	LUX(0), LUY(0), RDX(0), RDY(0), FigureIndex(0), 
	CenterX(0), CenterY(0), FigureWidth(30), Expansion(true), ZRotate_Radius(0),
	Y_Rotate_Switch(false)
	,MousePointStart(false), FreeVertexDone(false)//, MousePointIndex(0)
{
	memset(Point, 0, sizeof(float) * WINDOW_WIDTH * 2);
	memset(CirclePoint, 0, sizeof(float) * 72 * 2);
	//memset(MousePoint, 0, sizeof(float) * 10 * 2);
}

CManager::~CManager()
{
}

void CManager::Update()
{
	Motion();


	// ���� ������Ʈ
	switch (Mode_Course)
	{
	case ZIGZAG:
	case SIN:
		CenterX = Point[FigureIndex % WINDOW_WIDTH][0];
		CenterY = Point[FigureIndex % WINDOW_WIDTH][1];

		break;
	case CIRCLE:
		CenterX = CirclePoint[FigureIndex % 72][0];
		CenterY = CirclePoint[FigureIndex % 72][1];
		ZRotate_Radius = sqrt(CenterX * CenterX + CenterY * CenterY);
		break;
	case TORNADO:
		CenterX = TornadoPoint[FigureIndex % (72 * 3)][0];
		CenterY = TornadoPoint[FigureIndex % (72 * 3)][1];
		break;
	case FREE:
		if (false == MousePointStart || false == FreeVertexDone)
		{
			break;
		}

		CenterX = UpdateIter->X;
		CenterY = UpdateIter->Y;

		UpdateIter++;
		if (FreeVertexList.end() == UpdateIter)
		{
			UpdateIter = FreeVertexList.begin();
		}
		break;
	default:
		break;
	}
	FigureIndex += 3;
	



	
	Angle = 0;
	int Zigzag_Height = 0;
	bool Zigzag_Switch = true;
	int Tornado_Radius = 50;

	int XPos = -400;
	int YPos = 0;

	std::list<MousePoint>::iterator MousePointerIter;
	float Alpha = 0, Beta = 0;
	float TestX = 0, TestY = 0;
	int LargeY = 0, SmallY = 0, LargeX = 0, SmallX = 0;


	// ��� ������Ʈ
	switch (Mode_Course)
	{
	case CIRCLE:
		XPos = 0;
		for (size_t i = 0; i <= 360 / 5; i++)
		{
			//if (0 <= Angle && 90 > Angle)
			//{
			//	CirclePoint[i][0] = XPos + sin(GetRadian(Angle)) * CIRCLE_RADIUS;
			//	CirclePoint[i][1] = YPos - cos(GetRadian(Angle)) * CIRCLE_RADIUS;
			//}
			//// �����ϴ�
			//else if (90 <= Angle && 180 > Angle)
			//{
			//	CirclePoint[i][0] = XPos + cos(GetRadian(Angle)) * CIRCLE_RADIUS;
			//	CirclePoint[i][1] = YPos + sin(GetRadian(Angle)) * CIRCLE_RADIUS;
			//	//CirclePoint[i][0] = 0;
			//	//CirclePoint[i][1] = 0;
			//}
			//else if (180 <= Angle && 270 > Angle)
			//{
			//	CirclePoint[i][0] = XPos - sin(GetRadian(Angle)) * CIRCLE_RADIUS;
			//	CirclePoint[i][1] = YPos + cos(GetRadian(Angle)) * CIRCLE_RADIUS;
			//}
			//// �������?
			//else if (270 <= Angle && 360 > Angle)
			//{
			//	CirclePoint[i][0] = XPos - cos(GetRadian(Angle)) * CIRCLE_RADIUS;
			//	CirclePoint[i][1] = YPos - sin(GetRadian(Angle)) * CIRCLE_RADIUS;
			//	//CirclePoint[i][0] = 0;
			//	//CirclePoint[i][1] = 0;
			//}
			CirclePoint[i][0] = sin(GetRadian(Angle)) * CIRCLE_RADIUS;
			CirclePoint[i][1] = cos(GetRadian(Angle)) * CIRCLE_RADIUS;


			Angle = (Angle + 5) % 360;
		}
		break;
	case SIN:
		for (size_t i = 0; i < WINDOW_WIDTH; i++)
		{
			Point[i][0] = XPos;
			// 9 / 10 �� ���Ѱ� -360 ~ 360 ������ �ٲ��ַ���
			Point[i][1] = sin(GetRadian(XPos * 9 / 10)) * 100;
			XPos += 1;
		}
		break;

	case ZIGZAG:
		XPos = -400;
		for (int i = 0; i < 800; i++)
		{
			// -400 ����
			Point[i][0] = i - WINDOW_WIDTH / 2;
			Point[i][1] = Zigzag_Height;
			if (true == Zigzag_Switch)
			{
				if (100 <= Zigzag_Height)
				{
					Zigzag_Switch = false;
				}
				Zigzag_Height++;
			}
			else
			{
				if (-100 >= Zigzag_Height)
				{
					Zigzag_Switch = true;
				}
				Zigzag_Height--;
			}
		}
		break;
	case TORNADO:
		XPos = 0;
		for (size_t i = 0; i < 360 / 5 * 3; i++)
		{
			TornadoPoint[i][0] = sin(GetRadian(Angle)) * Tornado_Radius;
			TornadoPoint[i][1] = cos(GetRadian(Angle)) * Tornado_Radius;

			Angle = (Angle + 5) % 360;
			Tornado_Radius += 1;
		}
		break;

	case FREE:

		if (false == MousePointStart)
		{
			break;
		}

		// ���� �ִ� 5���� ������ �� �� ������ ������ ���ϰ� �� ������ ������ FreeVertexList�� ��������
		// Ȥ�ø𸣴� X, Y ��ǥ �ʱ�ȭ
		XPos = 0, YPos = 0;

		for (MousePointerIter = MousePointList.begin(); MousePointerIter != MousePointList.end(); MousePointerIter++)
		{
			// ������ ���� ���� �����Ƿ� ������ �� �������� ���
			if (++MousePointerIter != MousePointList.end())
			{
				// ++ �������� --���ֱ�
				--MousePointerIter;
				// while�� ������ �� �� �ʱ�ȭ
				XPos = MousePointerIter->X;
				YPos = MousePointerIter->Y;
				// ����
				LargeY = (++MousePointerIter)->Y;
				SmallY = (--MousePointerIter)->Y;
				LargeX = (++MousePointerIter)->X;
				SmallX = (--MousePointerIter)->X;
				//Alpha = (++MousePointerIter)->Y - (--MousePointerIter)->Y / ((++MousePointerIter)->X - (--MousePointerIter)->X);
				Alpha = (float)(LargeY - SmallY) / (float)(LargeX - SmallX);
				// Y����
				Beta = YPos - Alpha * XPos;

				// X��ǥ ���� ���� X��ǥ ���� ���� �� ���� �ݺ�
				while (XPos != (++MousePointerIter)->X)
				{
					// ++ �������� --���ֱ�					
					--MousePointerIter;
					// ������ ���� �� ���� ���� X��ǥ�� ���� ������ų���� ���ҽ�ų���� ����
					// �� ���� X��ǥ ���� �� ũ�ų� ���� ���
					if (MousePointerIter->X <= (++MousePointerIter)->X)
					{
						// ++ �������� --���ֱ�
						--MousePointerIter;
						// ���� ���� ��� ������
						if (XPos != (++MousePointerIter)->X)
						{
							TestX = XPos;
							TestY = Alpha * XPos + Beta;
							FreeVertexList.push_back({XPos, (int)(Alpha * XPos + Beta)});
							//FreeVertexList.push_back({ XPos, 600 - Alpha * XPos + Beta });
						}
						// ++ �������� --���ֱ�
						--MousePointerIter;
						XPos++;
					}
					else
					{
						// ++ �������� --���ֱ�
						--MousePointerIter;
						// ���� ���� ��� ������
						if (XPos != (++MousePointerIter)->X)
						{
							TestX = XPos;
							TestY = Alpha * XPos + Beta;
							FreeVertexList.push_back({ XPos, (int)(Alpha * XPos + Beta) });
							//FreeVertexList.push_back({ XPos, 600 - Alpha * XPos + Beta });
						}
						// ++ �������� --���ֱ�
						--MousePointerIter;
						XPos--;
					}
				}
			}
			else
			{
				if (false == FreeVertexDone)
				{
					UpdateIter = FreeVertexList.begin();
					FreeVertexDone = true;
				}
				// ������ ����Ʈ�� �����ϸ� for�� ����
				break;
			}
		}
		break;
	default:
		break;
	}

	//switch (Mode_Course)
	//{
	//case CIRCLE:
	//	for (size_t i = 0; i < 360 / 5; i++)
	//	{
	//		CenterX = CirclePoint[i][0];
	//		CenterY = CirclePoint[i][1];
	//	}
	//	break;
	//case SIN:
	//case ZIGZAG:
	//	for (size_t i = 0; i < WINDOW_WIDTH; i++)
	//	{
	//		CenterX = Point[i][0];
	//		CenterY = Point[i][1];
	//	}
	//	break;
	//case TORNADO:
	//	for (size_t i = 0; i < 360 / 5 * 3; i++)
	//	{
	//		CenterX = TornadoPoint[i][0];
	//		CenterY = TornadoPoint[i][1];
	//	}
	//	break;
	//case FREE:
	//	break;
	//default:
	//	break;
	//}
	Motion();
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
	// ��� �׸���
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); //����
	glPointSize(1.0f);//���� ũ��
	glBegin(GL_LINE_STRIP);

	std::list<MousePoint>::iterator iter;

	switch (Mode_Course)
	{
	case CIRCLE:
		for (size_t i = 0; i < 360 / 5; i++)
		{
			glVertex3f(CirclePoint[i][0], CirclePoint[i][1], 0.0f);
		}
		break;
	case SIN:
	case ZIGZAG:
		for (size_t i = 0; i < WINDOW_WIDTH; i++)
		{
			glVertex3f(Point[i][0], Point[i][1], 0.0f);
		}
		break;
	case TORNADO:
		for (size_t i = 0; i < 360 / 5 * 3; i++)
		{
			glVertex3f(TornadoPoint[i][0], TornadoPoint[i][1], 0.0f);
		}
		break;
	case FREE:
		if (false == MousePointStart)
		{
			break;
		}
		for (iter = MousePointList.begin(); iter != MousePointList.end(); iter++)
		{
			glVertex3f(iter->X, iter->Y, 0.0f);
		}
		break;
	default:
		break;
	}
	glEnd();
}
void CManager::DrawFigure()
{
	// ���� �׸���
	// Z�� �߽����� ȸ���ϰ� ��ΰ� ���� ��
	if (true == Z_Rotate_Switch && CIRCLE == Mode_Course)
	{
		if (Figure == TRIANGLE && CIRCLE == Mode_Course)
		{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //����
			glBegin(GL_TRIANGLES);
			glVertex3f(0, -ZRotate_Radius + FigureWidth, 0.0f);
			glVertex3f(-FigureWidth, -ZRotate_Radius - FigureWidth, 0.0f);
			glVertex3f(FigureWidth, -ZRotate_Radius - FigureWidth, 0.0f);
			glEnd();
		}
		else
		{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //����
			glRectf(- FigureWidth, -ZRotate_Radius + FigureWidth, FigureWidth, -ZRotate_Radius - FigureWidth);
		}

	}
	// ���� ��ΰ� �ƴ� ���
	else if (FREE != Mode_Course)
	{
		if (TRIANGLE == Figure)
		{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //����
			glBegin(GL_TRIANGLES);
			glVertex3f(CenterX, CenterY + FigureWidth, 0.0f);
			glVertex3f(CenterX - FigureWidth, CenterY - FigureWidth, 0.0f);
			glVertex3f(CenterX + FigureWidth, CenterY - FigureWidth, 0.0f);
			glEnd();
		}
		else
		{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //����
			glRectf(CenterX - FigureWidth, CenterY + FigureWidth, CenterX + FigureWidth, CenterY - FigureWidth);
		}
	}
	// ���� ����̰� �غ� �� �Ǿ��� ��
	else if (true == MousePointStart)
	{
		if (TRIANGLE == Figure)
		{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //����
			glBegin(GL_TRIANGLES);
			glVertex3f(CenterX, CenterY + FigureWidth, 0.0f);
			glVertex3f(CenterX - FigureWidth, CenterY - FigureWidth, 0.0f);
			glVertex3f(CenterX + FigureWidth, CenterY - FigureWidth, 0.0f);
			glEnd();
		}
		else
		{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); //����
			glRectf(CenterX - FigureWidth, CenterY + FigureWidth, CenterX + FigureWidth, CenterY - FigureWidth);
		}
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

	if (Z_Rotate_Switch)
	{
		glRotatef(-5, 0.0, 0.0, 1.0);
		ZRotateCount = (ZRotateCount + 1) % (360 / 5);
	}
	if (Y_Rotate_Switch)
	{
		glRotatef(-5, 0.0, 1.0, 0.0);
		YRotateCount = (YRotateCount + 1) % (360 / 5);
	}
}
void CManager::InitCoordinate()
{
	for (int i = 0; i < ZRotateCount; i++)
	{
		glRotatef(5, 0.0, 0.0, 1.0);
	}
	for (int i = 0; i < YRotateCount; i++)
	{
		glRotatef(5, 0.0, 1.0, 0.0);
	}
}
void CManager::YRotate()
{
	if (Y_Rotate_Switch)
	{
		glRotatef(5, 0.0, 1.0, 0.0);
		YRotateCount = (YRotateCount + 1) % (360 / 5);
	}
}

void CManager::SetCommand(char _Key)
{
	switch (_Key)
	{
	case CIRCLE:
		Mode_Course = CIRCLE;
		break;
	case SIN:
		Mode_Course = SIN;
		break;
	case TORNADO:
		Mode_Course = TORNADO;
		break;
	case ZIGZAG:
		Mode_Course = ZIGZAG;
		break;
	case FREE:
		Mode_Course = FREE;
		break;

	case ROTATE_SMALLZ:
	case ROTATE_LARGEZ:
		if (true == Z_Rotate_Switch)
		{
			Z_Rotate_Switch = false;
		}
		else
		{
			Z_Rotate_Switch = true;
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
	case 't':
	case 'T':
		Figure = TRIANGLE;
		break;
	case 'r':
	case 'R':
		Figure = RECTANGLE;
		break;
	default:
		break;
	}
}
void CManager::SetMousePoint(int _MouseX, int _MouseY)
{
	if (MousePointList.size() < 5)
	{
		MousePointList.push_back({ _MouseX - 400, (600 - _MouseY) - 300});
	}
}

void CManager::SetMousePointDone()
{
	if (FREE == Mode_Course)
	{
		MousePointStart = true;
	}
}
