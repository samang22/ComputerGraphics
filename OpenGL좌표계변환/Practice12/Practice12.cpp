#include "pch.h"
#include "CManager.h"
#include <gl/freeglut.h>
//#include <stdio.h>

void DrawScene(void);
void reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

CManager Manager = CManager();

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);				// 윈도우의 위치지정
	glutInitWindowSize(800, 600);					// 윈도우 크기 지정
	glutCreateWindow("Practice12");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);
	//glutIdleFunc(drawScene);
	glutMainLoop();
	return 0;
}

void DrawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Manager.DrawFigure();
	glPushMatrix();
	Manager.InitCoordinate();
	Manager.DrawLine();
	glPopMatrix();
	Manager.DrawCourse();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}
void TimerFunction(int value)
{
	Manager.Update();
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && (state == GLUT_UP))
	{
		Manager.SetMousePoint(x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && (state == GLUT_UP))
	{
		Manager.SetMousePointDone();
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	Manager.SetCommand(key);
}