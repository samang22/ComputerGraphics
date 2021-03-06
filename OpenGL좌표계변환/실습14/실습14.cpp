#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define CUBE 1
#define SPHERE 2
#define TORUS 3
#define TEAPOT 4
#define CONE 5

struct FigureInform {
	bool DrawFigure;
	int HowFigure;
	int Direct_To_Rotate;		// 1 : x축으로 회전, 2 : y축으로 회전, 3 : z축으로 회전
	double Rotate;				// 도형의 회전 각도 ( 타이머에 의해 증가 )
	int slide;					// z축 주위 분할
	int stack;					// z축 방향 분할
	double Red;					// RGB의 R
	double Blue;				// RGB의 B
	double Green;				// RGB의 G
	double x, y;				// 도형의 생성 좌표 ( 마우스 좌표를 가지고 옴 )
	double r;					// 도형의 크기 ( 반지름 )
	double height;				// 도형의 높이

	FigureInform() {
		DrawFigure = FALSE;
		Rotate = 0;
		slide = 20;
		stack = 20;
	}
};

int WindowX = 800;
int WindowY = 800;
int TimerSpeed = 100;
bool TurnDirect = TRUE;
FigureInform Figure[20];

bool Rotate_Direct = TRUE;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

void main(int argc, char *argv[]) {

	srand((unsigned)time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(/*GLUT_SINGLE*/GLUT_DOUBLE | GLUT_RGB);		// 출력모드를 GLUT_SINGLE 대신 GLUT_DOUBLE 
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WindowX, WindowY);
	glutCreateWindow("Example14");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	glutTimerFunc(TimerSpeed, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);						// 키보드 입력 콜백 함수 
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutMainLoop();
}

GLvoid drawScene(GLvoid) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT);			// 설정된 색으로 전체를 칠하기 


	glMatrixMode(GL_MODELVIEW);		// 현재의 행렬모드 설정 
									// 
									//  GL_MODELVIEW = 모델링 및 뷰잉 변환 모드 (물체 이동 시) 
									//           >> 디폴트 모드로 GL_MODELVIEW 로 설정되어 있다. 
									//  GL_PROJECTION = 투영 변환 모드 (클리핑 공간 정의) 
									//  GL_TEXTURE = 텍스처 매핑 모드 (텍스처 매핑 정의) 

	glLoadIdentity();   // 현재의 변환 행렬을 단위행렬로 설정, 모델관측행렬 초기화

	for (int i = 0; i < 20; i++) {
		if (Figure[i].DrawFigure == TRUE) {

			glPushMatrix();

			glTranslatef(Figure[i].x, Figure[i].y, 0);

			if (Figure[i].Direct_To_Rotate == 1)
				glRotatef(Figure[i].Rotate, 1.0f, 0.0f, 0.0f);
			else if (Figure[i].Direct_To_Rotate == 2)
				glRotatef(Figure[i].Rotate, 0.0f, 1.0f, 0.0f);
			else if (Figure[i].Direct_To_Rotate == 3)
				glRotatef(Figure[i].Rotate, 0.0f, 0.0f, 1.0f);

			glColor3f(Figure[i].Red / 254, Figure[i].Green / 254, Figure[i].Blue / 254);


			switch (Figure[i].HowFigure)
			{
			case CUBE:		// 정육면체
				glutWireCube(Figure[i].r);
				break;

			case SPHERE:	// 구
				glutWireSphere(Figure[i].r, Figure[i].slide, Figure[i].stack);
				break;

			case TORUS:		// 도넛
				glutWireTorus(Figure[i].r, Figure[i].r + 0.1, Figure[i].slide, Figure[i].stack);
				break;

			case TEAPOT:	// 주전자
				glutWireTeapot(Figure[i].r);
				break;

			case CONE:		// 원뿔
				glutWireCone(Figure[i].r, Figure[i].height, Figure[i].slide, Figure[i].stack);
				break;
			}

			glPopMatrix();

		}
	}

	// glFlush(); // 화면에 출력하기
	glutSwapBuffers();	// 그리기 함수에서 glFlush 대신 사용
						//  >> glFlush 효과가 있으므로 glFlush를 사용할 필요가 없다.

}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 0, 800, -1.0, 1.0);

}

void Mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 20; i++) {
			if (Figure[i].DrawFigure == FALSE) {
				Figure[i].DrawFigure = TRUE;
				Figure[i].Direct_To_Rotate = rand() % 3 + 1;
				Figure[i].HowFigure = rand() % 5 + 1;
				Figure[i].x = double(x) / (WindowX / 2) - 1;
				Figure[i].y = (WindowY - double(y)) / (WindowY / 2) - 1;
				Figure[i].Red = rand() % 154 + 100;
				Figure[i].Green = rand() % 154 + 100;
				Figure[i].Blue = rand() % 154 + 100;
				Figure[i].r = 0.6;
				Figure[i].height = 0.7;

				break;
			}
		}
	}

}

void Motion(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {

	switch (key)
	{
	case 't':
		TurnDirect = 1 - TurnDirect;
	}
}

void TimerFunction(int value) {

	for (int i = 0; i < 20; i++) {
		if (Figure[i].DrawFigure == TRUE) {

			if (TurnDirect == TRUE)
				Figure[i].Rotate += 5;
			else
				Figure[i].Rotate -= 5;

			Figure[i].r -= 0.005;
			Figure[i].height -= 0.005;
			if (Figure[i].r < 0) {
				Figure[i].DrawFigure = FALSE;
				Figure[i].r = 0.7;
				Figure[i].Rotate = 0;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(TimerSpeed, TimerFunction, 1);
}