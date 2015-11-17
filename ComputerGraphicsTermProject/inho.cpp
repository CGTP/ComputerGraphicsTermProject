#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

int Time = 1;
char Input;

float camxrotate = 0, camyrotate = -90, Vewx = 0, Vewy = 0, Vewz = -1000, Charx = 0, Charz = 0;
float nx = 0, ny = 0, bx = 0, by = 0;

bool RotateCam = true;

void main()
{
	srand((unsigned)time(NULL));

	//������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //���÷��� ��� ����
	glutInitWindowPosition(500, 0); // ������ ��ġ ����
	glutInitWindowSize(800, 600); //������ ũ�� ����
	glutCreateWindow("CGExample1"); //������ ����(������ �̸�)

	//���� ���� �ʱ�ȭ �Լ�
	glutSetCursor(GLUT_CURSOR_NONE);//���콺Ŀ�� ���ֱ�

	//�ʿ��� �ݹ� �Լ� ����
	glutDisplayFunc(DrawScene); //��� �Լ��� ����
	glutTimerFunc(Time, TimerFunction, 1);//Ÿ�̸� �ݹ� �Լ�
	glutMouseFunc(Mouse);//���콺�Է�
	//glutMotionFunc(Motion);
	glutPassiveMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);//Ű�����Է�
	glutReshapeFunc(Reshape);//�ٽñ׸���

	glutMainLoop();//�̺�Ʈ ���� �����ϱ�

}

//������ ��� �Լ�
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//��������'black'������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�

	glLoadIdentity();
	gluLookAt(Charx, 0.0, Charz, Vewx, Vewy, Vewz, 0.0, 1.0, 0.0);



	//������
	glEnable(GL_DEPTH_TEST);                              // ������ �� ����
	glEnable(GL_CULL_FACE);                               // �ĸ� ����


	glPushMatrix();//�ٴ� �׸���
	glTranslatef(0, -100, 0);
	glScalef(1, 0.01, 1);
	glutWireCube(2000);
	glPopMatrix();//�ٴ� �׸��� ����

	glPushMatrix();//�ٴ� �׸���
	glColor3f(1, 0, 0);
	glTranslatef(0, 0, -1000);
	glutSolidCube(100);
	glPopMatrix();//�ٴ� �׸��� ����

	glPushMatrix();//�ٴ� �׸���
	glColor3f(0, 0, 1);
	glTranslatef(0, 0, 1000);
	glutSolidCube(100);
	glPopMatrix();//�ٴ� �׸��� ����

	glPushMatrix();//�ٴ� �׸���
	glColor3f(0, 1, 0);
	glTranslatef(1000, 0, 0);
	glutSolidCube(100);
	glPopMatrix();//�ٴ� �׸��� ����

	glPushMatrix();//�ٴ� �׸���
	glColor3f(1, 1, 0);
	glTranslatef(-1000, 0, 0);
	glutSolidCube(100);
	glPopMatrix();//�ٴ� �׸��� ����


	glPushMatrix();//�ٴ� �׸���
	glColor3f(1, 0, 1);
	glTranslatef(0, -1000, 0);
	glutSolidCube(100);
	glPopMatrix();//�ٴ� �׸��� ����

	glPushMatrix();//�ٴ� �׸���
	glColor3f(0, 1, 1);
	glTranslatef(0, 1000, 0);
	glutSolidCube(100);
	glPopMatrix();//�ٴ� �׸��� ����


	glutSwapBuffers(); //ȭ�鿡 ����ϱ�
}//end of drawScene

GLvoid Reshape(int w, int h)
{
	//����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);

	//���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Ŭ���� ���� ���� : ��������
	gluPerspective(60.0f, (float)w / (float)h, 0.1, 5000.0);

	//�� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
}

void Mouse(int button, int state, int x, int y)
{
}//end of Mouse

void Motion(int x, int y)
{
	if (RotateCam)
	{
		nx = 400 - x;
		ny = 300 - y;

		camxrotate = camxrotate + (nx / 25);
		camyrotate = camyrotate + (ny / 30);
		Vewy = 2000 * sin(-camyrotate * 3.141592 / 180) * cos(camyrotate * 3.141592 / 180);
		Vewx = 1000 * sin(-camxrotate * 3.141592 / 180) * sin(camyrotate * 3.141592 / 180) + Charx;
		Vewz = 1000 * cos(-camxrotate * 3.141592 / 180) * sin(-camyrotate * 3.141592 / 180) + Charz;
		//printf("Vewx : %f, Vewy : %f, Vewz : %f\n", Vewx, Vewy, Vewz);
		//printf("x : %d, y : %d\n", x - 400, y - 400);
		//printf("camx : %f, camy : %f\n", camxrotate, camyrotate);
		//printf("nx : %f", nx);
		//printf("%f, %f, %f\n", Vewy, Vewx, Vewz);

		if (camxrotate <= -360 || camxrotate >= 360)
			camxrotate = 0;

		if (camyrotate < -170)
			camyrotate = -170;
		else if (camyrotate > -10)
			camyrotate = -10;
		bx = nx;
		by = ny;
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		Charx += 3 * cos((-camxrotate + 90) * 3.141592 / 180);
		Charz += 3 * sin((-camxrotate + 90) * 3.141592 / 180);
		break;
	case 'a':
		Charx += 3 * cos((-camxrotate) * 3.141592 / 180);
		Charz += 3 * sin((-camxrotate) * 3.141592 / 180);
		break;
	case 's':
		Charx -= 3 * cos((-camxrotate + 90) * 3.141592 / 180);
		Charz -= 3 * sin((-camxrotate + 90) * 3.141592 / 180);
		break;
	case 'd':
		Charx -= 3 * cos((-camxrotate) * 3.141592 / 180);
		Charz -= 3 * sin((-camxrotate) * 3.141592 / 180);
		break;
	case 'c':
		glutSetCursor(GLUT_CURSOR_NONE);
		if (RotateCam)
			RotateCam = false;
		else
			RotateCam = true;
		break;
	case 27://ESCŰ�� ����
		exit(0);
		break;
	}
	glutPostRedisplay();
}//end of Keyboard

void TimerFunction(int value)
{
	if (RotateCam)
		glutWarpPointer(400, 300);
	glutPostRedisplay();
	glutTimerFunc(Time, TimerFunction, 1);
}//end of TimerFunction
