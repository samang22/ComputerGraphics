#define _CRT_SECURE_NO_WARNINGS

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



int WindowX = 800;
int WindowY = 800;
int TimerSpeed = 100;
int RotateY = 10;
time_t timer;
struct tm *t;

bool Rotate_Direct = TRUE;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void DrawEightFigure(int i);

void main(int argc, char *argv[]) {

	srand((unsigned)time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(/*GLUT_SINGLE*/GLUT_DOUBLE | GLUT_RGB);		// 출력모드를 GLUT_SINGLE 대신 GLUT_DOUBLE 
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WindowX, WindowY);
	glutCreateWindow("Example15");
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

	glRotatef(20, 1.0f, 0.0f, 0.0f);
	glRotatef(-RotateY, 0.0f, 1.0f, 0.0f);

	glPushMatrix();

	glTranslatef(-1.12f, 0.0f, 0.0f);

	for (int i = 0; i < 6; i++) {

		timer = time(NULL); // 현재 시각을 초 단위로 얻기
		t = localtime(&timer);  // 초 단위의 시간을 분리하여 구조체에 담는다.

		if (i == 2 || i == 4) {
			glTranslatef(0.08, 0.0f, 0.0f);
		}
		glTranslatef(0.3, 0.0f, 0.0f);
		DrawEightFigure(i);
	}

	glPopMatrix();

	// glFlush(); // 화면에 출력하기
	glutSwapBuffers();	// 그리기 함수에서 glFlush 대신 사용
						//  >> glFlush 효과가 있으므로 glFlush를 사용할 필요가 없다.

}

GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);

	//glMatrixMode(GL_PROJECTION); 
	//glLoadIdentity();

	//
	//1. 클리핑 공간 설정: 원근 투영인 경우
	//gluPerspective(60.0f, w / h, 1.0, 1000.0);
	//glTranslatef(0.0f, 0.0f, -2.0f);


	 /*2. 클리핑 공간 설정: 직각 투영인 경우*/
	glOrtho(0, 800, 0, 800, -1.0, 200.0);


}

void Mouse(int button, int state, int x, int y) {



}

void Motion(int x, int y) {

}

void Keyboard(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'y':
		RotateY += 5;
		break;
	}
}

void TimerFunction(int value) {


	glutPostRedisplay();
	glutTimerFunc(TimerSpeed, TimerFunction, 1);
}

//void RectInit(RectInform *Rect) {
//
////}

void DrawEightFigure(int i) {

	glPushMatrix();

	glTranslatef(0.0f, 0.25f, 0.0f);

	if ((t->tm_hour / 10 == 2 && i == 0) ||
		((t->tm_hour % 10 == 2 || t->tm_hour % 10 == 3 || t->tm_hour % 10 == 5 || t->tm_hour % 10 == 6 || t->tm_hour % 10 == 7 || t->tm_hour % 10 == 8 || t->tm_hour % 10 == 9 || t->tm_hour % 10 == 0) && (i == 1)) ||
		((t->tm_min / 10 == 2 || t->tm_min / 10 == 3 || t->tm_min / 10 == 5 || t->tm_min / 10 == 6 || t->tm_min / 10 == 0) && i == 2) ||
		((t->tm_min % 10 == 2 || t->tm_min % 10 == 3 || t->tm_min % 10 == 5 || t->tm_min % 10 == 6 || t->tm_min % 10 == 7 || t->tm_min % 10 == 8 || t->tm_min % 10 == 9 || t->tm_min % 10 == 0) && (i == 3)) ||
		((t->tm_sec / 10 == 2 || t->tm_sec / 10 == 3 || t->tm_sec / 10 == 5 || t->tm_sec / 10 == 6 || t->tm_sec / 10 == 0) && i == 4) ||
		((t->tm_sec % 10 == 2 || t->tm_sec % 10 == 3 || t->tm_sec % 10 == 5 || t->tm_sec % 10 == 6 || t->tm_sec % 10 == 7 || t->tm_sec % 10 == 8 || t->tm_sec % 10 == 9 || t->tm_sec % 10 == 0) && (i == 5))) {
		glColor3f(0.0f, 1.0f, 0.8f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutSolidCube(0.4);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(0.41);
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutWireCube(0.4);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.125f, 0.125f, 0.0f);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);


	if (((t->tm_hour % 10 == 4 || t->tm_hour % 10 == 5 || t->tm_hour % 10 == 6 || t->tm_hour % 10 == 8 || t->tm_hour % 10 == 9 || t->tm_hour % 10 == 0) && (i == 1)) ||
		((t->tm_min / 10 == 4 || t->tm_min / 10 == 5 || t->tm_min / 10 == 6 || t->tm_min / 10 == 0) && i == 2) ||
		((t->tm_min % 10 == 4 || t->tm_min % 10 == 5 || t->tm_min % 10 == 6 || t->tm_min % 10 == 8 || t->tm_min % 10 == 9 || t->tm_min % 10 == 0) && (i == 3)) ||
		((t->tm_sec / 10 == 4 || t->tm_sec / 10 == 5 || t->tm_sec / 10 == 6 || t->tm_sec / 10 == 0) && i == 4) ||
		((t->tm_sec % 10 == 4 || t->tm_sec % 10 == 5 || t->tm_sec % 10 == 6 || t->tm_sec % 10 == 8 || t->tm_sec % 10 == 9 || t->tm_sec % 10 == 0) && (i == 5))) {

		glColor3f(0.0f, 1.0f, 0.8f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutSolidCube(0.4);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(0.41);

	}
	else {

		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutWireCube(0.4);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.125f, 0.125f, 0.0f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);

	if (((t->tm_hour / 10 == 1 || t->tm_hour / 10 == 2) && i == 0) ||
		((t->tm_hour % 10 == 1 || t->tm_hour % 10 == 2 || t->tm_hour % 10 == 3 || t->tm_hour % 10 == 4 || t->tm_hour % 10 == 7 || t->tm_hour % 10 == 8 || t->tm_hour % 10 == 9 || t->tm_hour % 10 == 0) && (i == 1)) ||
		((t->tm_min / 10 == 1 || t->tm_min / 10 == 2 || t->tm_min / 10 == 3 || t->tm_min / 10 == 4 || t->tm_min / 10 == 0) && i == 2) ||
		((t->tm_min % 10 == 1 || t->tm_min % 10 == 2 || t->tm_min % 10 == 3 || t->tm_min % 10 == 4 || t->tm_min % 10 == 7 || t->tm_min % 10 == 8 || t->tm_min % 10 == 9 || t->tm_min % 10 == 0) && (i == 3)) ||
		((t->tm_sec / 10 == 1 || t->tm_sec / 10 == 2 || t->tm_sec / 10 == 3 || t->tm_sec / 10 == 4 || t->tm_sec / 10 == 0) && i == 4) ||
		((t->tm_sec % 10 == 1 || t->tm_sec % 10 == 2 || t->tm_sec % 10 == 3 || t->tm_sec % 10 == 4 || t->tm_sec % 10 == 7 || t->tm_sec % 10 == 8 || t->tm_sec % 10 == 9 || t->tm_sec % 10 == 0) && (i == 5))) {

		glColor3f(0.0f, 1.0f, 0.8f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutSolidCube(0.4);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(0.41);
	}
	else {

		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutWireCube(0.4f);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);

	if ((t->tm_hour / 10 == 2 && i == 0) ||
		((t->tm_hour % 10 == 2 || t->tm_hour % 10 == 3 || t->tm_hour % 10 == 4 || t->tm_hour % 10 == 5 || t->tm_hour % 10 == 6 || t->tm_hour % 10 == 8 || t->tm_hour % 10 == 9) && (i == 1)) ||
		((t->tm_min / 10 == 2 || t->tm_min / 10 == 3 || t->tm_min / 10 == 4 || t->tm_min / 10 == 5 || t->tm_min / 10 == 6) && i == 2) ||
		((t->tm_min % 10 == 2 || t->tm_min % 10 == 3 || t->tm_min % 10 == 4 || t->tm_min % 10 == 5 || t->tm_min % 10 == 6 || t->tm_min % 10 == 8 || t->tm_min % 10 == 9) && (i == 3)) ||
		((t->tm_sec / 10 == 2 || t->tm_sec / 10 == 3 || t->tm_sec / 10 == 4 || t->tm_sec / 10 == 5 || t->tm_sec / 10 == 6) && i == 4) ||
		((t->tm_sec % 10 == 2 || t->tm_sec % 10 == 3 || t->tm_sec % 10 == 4 || t->tm_sec % 10 == 5 || t->tm_sec % 10 == 6 || t->tm_sec % 10 == 8 || t->tm_sec % 10 == 9) && (i == 5))) {

		glColor3f(0.0f, 1.0f, 0.8f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutSolidCube(0.4);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(0.41);
	}
	else {

		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutWireCube(0.4f);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.125f, -0.125f, 0.0f);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);

	if ((t->tm_hour / 10 == 2 && i == 0) ||
		((t->tm_hour % 10 == 2 || t->tm_hour % 10 == 6 || t->tm_hour % 10 == 8 || t->tm_hour % 10 == 0) && (i == 1)) ||
		((t->tm_min / 10 == 2 || t->tm_min / 10 == 6 || t->tm_min / 10 == 0) && i == 2) ||
		((t->tm_min % 10 == 2 || t->tm_min % 10 == 6 || t->tm_min % 10 == 8 || t->tm_min % 10 == 0) && (i == 3)) ||
		((t->tm_sec / 10 == 2 || t->tm_sec / 10 == 6 || t->tm_sec / 10 == 0) && i == 4) ||
		((t->tm_sec % 10 == 2 || t->tm_sec % 10 == 6 || t->tm_sec % 10 == 8 || t->tm_sec % 10 == 0) && (i == 5))) {

		glColor3f(0.0f, 1.0f, 0.8f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutSolidCube(0.4);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(0.41);
	}
	else {

		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutWireCube(0.4f);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.125f, -0.125f, 0.0f);
	glRotatef(90, 0.0f, 0.0f, 1.0f);

	if ((t->tm_hour / 10 == 1 && i == 0) ||
		((t->tm_hour % 10 == 1 || t->tm_hour % 10 == 3 || t->tm_hour % 10 == 4 || t->tm_hour % 10 == 5 || t->tm_hour % 10 == 6 || t->tm_hour % 10 == 7 || t->tm_hour % 10 == 8 || t->tm_hour % 10 == 9 || t->tm_hour % 10 == 0) && (i == 1)) ||
		((t->tm_min / 10 == 1 || t->tm_min / 10 == 3 || t->tm_min / 10 == 4 || t->tm_min / 10 == 5 || t->tm_min / 10 == 6 || t->tm_min / 10 == 0) && i == 2) ||
		((t->tm_min % 10 == 1 || t->tm_min % 10 == 3 || t->tm_min % 10 == 4 || t->tm_min % 10 == 5 || t->tm_min % 10 == 6 || t->tm_min % 10 == 7 || t->tm_min % 10 == 8 || t->tm_min % 10 == 9 || t->tm_min % 10 == 0) && (i == 3)) ||
		((t->tm_sec / 10 == 1 || t->tm_sec / 10 == 3 || t->tm_sec / 10 == 4 || t->tm_sec / 10 == 5 || t->tm_sec / 10 == 6 || t->tm_sec / 10 == 0) && i == 4) ||
		((t->tm_sec % 10 == 1 || t->tm_sec % 10 == 3 || t->tm_sec % 10 == 4 || t->tm_sec % 10 == 5 || t->tm_sec % 10 == 6 || t->tm_sec % 10 == 7 || t->tm_sec % 10 == 8 || t->tm_sec % 10 == 9 || t->tm_sec % 10 == 0) && (i == 5))) {

		glColor3f(0.0f, 1.0f, 0.8f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutSolidCube(0.4);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(0.41);
	}
	else {

		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutWireCube(0.4f);
	}

	glPopMatrix();

	glPushMatrix();

	glTranslatef(0.0f, -0.25f, 0.0f);

	if ((t->tm_hour / 10 == 2 && i == 0) ||
		((t->tm_hour % 10 == 2 || t->tm_hour % 10 == 3 || t->tm_hour % 10 == 5 || t->tm_hour % 10 == 6 || t->tm_hour % 10 == 8 || t->tm_hour % 10 == 9 || t->tm_hour % 10 == 0) && (i == 1)) ||
		((t->tm_min / 10 == 2 || t->tm_min / 10 == 3 || t->tm_min / 10 == 5 || t->tm_min / 10 == 6 || t->tm_min / 10 == 0) && i == 2) ||
		((t->tm_min % 10 == 2 || t->tm_min % 10 == 3 || t->tm_min % 10 == 5 || t->tm_min % 10 == 6 || t->tm_min % 10 == 8 || t->tm_min % 10 == 9 || t->tm_min % 10 == 0) && (i == 3)) ||
		((t->tm_sec / 10 == 2 || t->tm_sec / 10 == 3 || t->tm_sec / 10 == 5 || t->tm_sec / 10 == 6 || t->tm_sec / 10 == 0) && i == 4) ||
		((t->tm_sec % 10 == 2 || t->tm_sec % 10 == 3 || t->tm_sec % 10 == 5 || t->tm_sec % 10 == 6 || t->tm_sec % 10 == 8 || t->tm_sec % 10 == 9 || t->tm_sec % 10 == 0) && (i == 5))) {

		glColor3f(0.0f, 1.0f, 0.8f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutSolidCube(0.4);
		glColor3f(0.0f, 0.0f, 0.0f);
		glutWireCube(0.41);
	}
	else {

		glColor3f(1.0f, 1.0f, 1.0f);
		glScalef(0.5f, 0.1f, 0.5f);   //직육면체의 x,y,z 크기 설정
		glutWireCube(0.4f);
	};

	glPopMatrix();
}