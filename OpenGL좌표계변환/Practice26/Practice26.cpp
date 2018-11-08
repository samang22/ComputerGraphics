#include "CManager.h"
#include <gl/freeglut.h>
#include <stdio.h>

void DrawScene(void);
void reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

CManager Manager = CManager();
bool IsStart = false;

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);				// 윈도우의 위치지정
	glutInitWindowSize(800, 600);					// 윈도우 크기 지정
	glutCreateWindow("Practice26");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	//glutIdleFunc(drawScene);
	glutMainLoop();
}

void DrawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.1, 0.0,	// 카메라의 위치
		0.0, 0.0, -100.0,			// 카메라가 보고있는 방향
		0.0, 1.0, 0.0);			// up-vetor 방향


	if (false == IsStart)
	{
		IsStart = true;
		Manager.Init();
	}
	Manager.Update();
	Manager.Draw();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);


	// 원근투영
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, w / h, 1.0, 2000.0);
	glTranslatef(0.0, 0.0, -400);


	// 직각투영
	// glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}
void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN))
	{

	}
}

void Keyboard(unsigned char key, int x, int y)
{
	Manager.GetCommand(key);
}