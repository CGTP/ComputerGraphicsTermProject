#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void MouseMotion(int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);

void vLine();

float fMapZ = 0.0;
float vMapX = 0.0;
float fView = 0.0;
int initX, initY;

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�
	glEnable(GL_DEPTH_TEST);

	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);

	glPushMatrix(); //Save
	vLine();
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(0, -210, 100);
	glScaled(4.0, 0.1, 2.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();     // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	switch (value){
	case 1:
		glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
		break;


	}
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == '+'){
		fView += 3.0;
	}
	else if (key == '-'){
		fView -= 3.0;
	}
	else if (key == 'a'){
		
	}
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		fMapZ -= 3.0;
	}
	if (key == GLUT_KEY_RIGHT){
		fMapZ += 3.0;
	}
	if (key == GLUT_KEY_DOWN){
		vMapX += 3.0;
	}
	if (key == GLUT_KEY_UP){
		vMapX -= 3.0;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Left = (%d, %d)\n", x, y);
		initX = x;
		initY = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

void MouseMotion(int x, int y){
	//printf("Motion : %d, %d\n", x, y);
	if (initX >= x){
		gluLookAt(0.02, 0, 0, 0, 0, -1, 0, 1, 0);
	}
	else if (initX <= x){
		gluLookAt(-0.02, 0, 0, 0, 0, -1, 0, 1, 0);
	}
	
	if (initY >= y){
		gluLookAt(0, 0.02, 0, 0, 0, -1, 0, 1, 0);
	}
	else if (initY <= y){
		gluLookAt(0, -0.02, 0, 0, 0, -1, 0, 1, 0);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1500.0);

	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

void vLine(){
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);
	glEnd();
}
