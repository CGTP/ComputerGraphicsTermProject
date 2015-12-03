/*#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>*/

#include "Texture_Load.h"
#include <math.h>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Keyboardup(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

void drawCharacter();//ĳ���� ��ο� �Լ�
void init_Texture();//�ؽ��� �ε� �Լ�
void animationCharleg();//ĳ���� �ٸ� �ִϸ��̼� �Լ�

int Time = 10;//Ÿ�̸� ���Žð�
char Input;

//ĳ���� �� ī�޶� ���� ����
float camxrotate = 0, camyrotate = -90, Vewx = 0, Vewy = 0, Vewz = -1000, Charx = 0, Charz = 0, Chary = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
int Charspeed = 5;
bool RotateCam = true, FirstPersonView = true;

//�ִϸ��̼� ����
int character_state = 0, timer = 0;//�̵� �ִϸ��̼� ���п�
float head_angle_x;//�Ӹ�ȸ��
float left_sholder_x, left_sholder_y, right_sholder_x, right_sholder_y, left_elbow_x, right_elbow_x;//��ȸ��
float left_leg_x, left_leg_y, left_knee_x, right_leg_x, right_leg_y, right_knee_x;//�ٸ�ȸ��

void main()
{
	srand((unsigned)time(NULL));

	//������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //���÷��� ��� ����
	glutInitWindowPosition(500, 0); // ������ ��ġ ����
	glutInitWindowSize(800, 600); //������ ũ�� ����
	glutCreateWindow("ComputerGrapgics TermProject"); //������ ����(������ �̸�)

	//���� ���� �ʱ�ȭ �Լ�
	glutSetCursor(GLUT_CURSOR_NONE);//���콺Ŀ�� ���ֱ�
	init_Texture();//�ؽ��� �ҷ�����

	//�ʿ��� �ݹ� �Լ� ����
	glutDisplayFunc(DrawScene); //��� �Լ��� ����
	glutTimerFunc(Time, TimerFunction, 1);//Ÿ�̸� �ݹ� �Լ�
	glutMouseFunc(Mouse);//���콺�Է�
	//glutMotionFunc(Motion);
	glutPassiveMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);//Ű�����Է�
	glutKeyboardUpFunc(Keyboardup);//Ű���� ��ư�� ���� ��
	glutReshapeFunc(Reshape);//�ٽñ׸���

	glutMainLoop();//�̺�Ʈ ���� �����ϱ�

}

//������ ��� �Լ�
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//��������'black'������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�

	glLoadIdentity();
	if (FirstPersonView)
		gluLookAt(Charx, Chary + 100, Charz, Vewx, Vewy, Vewz, 0.0, 1.0, 0.0);
	else
		gluLookAt(-Vewx / 50, -Vewy / 50, -Vewz / 50, Charx, Chary + 110, Charz, 0.0, 1.0, 0.0);


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

	for (int i = -8; i < 9; ++i){
		for (int j = -8; j < 9; ++j){
			glPushMatrix();//�ٴ� ��� �׸���
			glTranslatef(120 * i, -190, 120*j);
			draw_Block(60, block_Nomal_object);
			glPopMatrix();//�ٴ� ��� �׸��� ����
		}
	}

	glPushMatrix();
	glTranslatef(Charx, Chary, Charz);
	glRotatef(camxrotate, 0, 1, 0);
	drawCharacter();
	glPopMatrix();


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
		Charx += Charspeed * cos((-camxrotate + 90) * 3.141592 / 180);
		Charz += Charspeed * sin((-camxrotate + 90) * 3.141592 / 180);
		character_state = 1;
		break;
	case 'a':
		Charx += Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz += Charspeed * sin((-camxrotate) * 3.141592 / 180);
		character_state = 2;
		break;
	case 's':
		Charx -= Charspeed * cos((-camxrotate + 90) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate + 90) * 3.141592 / 180);
		character_state = 1;
		break;
	case 'd':
		Charx -= Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate) * 3.141592 / 180);
		character_state = 2;
		break;
	case 'c':
		glutSetCursor(GLUT_CURSOR_NONE);
		if (RotateCam)
			RotateCam = false;
		else
			RotateCam = true;
		break;
	case 'f':
		if (FirstPersonView)
			FirstPersonView = false;
		else
			FirstPersonView = true;
		break;
	case 27://ESCŰ�� ����
		exit(0);
		break;
	default:
		character_state = 0;
		break;
	}

	glutPostRedisplay();
}//end of Keyboard

void Keyboardup(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': case 's':case 'a': case 'd':
		character_state = 0;
		break;
	}
}

void TimerFunction(int value)
{
	if (RotateCam)
		glutWarpPointer(400, 300);
	animationCharleg();//ĳ���� �ٸ� �ִϸ��̼�

	glutPostRedisplay();
	glutTimerFunc(Time, TimerFunction, 1);
}//end of TimerFunction

void drawCharacter(){
	glPushMatrix(); //Save �Ӹ�
	glTranslated(0, 75, 0);
	glRotatef(-(camyrotate + 90) / 3, 1, 0, 0);
	glScaled(1.0, 1.0, 0.7);
	drawBoxFront(30, false, character_head_object[0]);
	drawBoxBack(30, false, character_head_object[1]);
	drawBoxLeft(30, false, character_head_object[2]);
	drawBoxRight(30, false, character_head_object[3]);
	drawBoxTop(30, false, character_head_object[4]);
	drawBoxBottom(30, false, character_head_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save ����
	glScaled(1.0, 1.5, 0.5);
	drawBoxFront(30, false, character_body_object[0]);
	drawBoxBack(30, false, character_body_object[1]);
	drawBoxLeft(30, false, character_body_object[2]);
	drawBoxRight(30, false, character_body_object[3]);
	drawBoxTop(30, false, character_body_object[4]);
	drawBoxBottom(30, false, character_body_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save ������ �
	glTranslated(-45, 44, 0);
	glRotatef(right_sholder_x, 1, 0, 0);
	glRotatef(right_sholder_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_arm_top_object[0]);
	drawBoxBack(30, true, character_arm_top_object[1]);
	drawBoxLeft(30, true, character_arm_top_object[2]);
	drawBoxRight(30, true, character_arm_top_object[3]);
	drawBoxTop(30, true, character_arm_top_object[4]);
	drawBoxBottom(30, true, character_arm_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ������ �Ȳ�ġ
	glTranslated(0, -45, 0);
	glRotatef(right_elbow_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_arm_bottom_object[0]);
	drawBoxBack(30, true, character_arm_bottom_object[1]);
	drawBoxLeft(30, true, character_arm_bottom_object[2]);
	drawBoxRight(30, true, character_arm_bottom_object[3]);
	drawBoxTop(30, true, character_arm_top_object[5]);
	drawBoxBottom(30, true, character_arm_top_object[5]);
	glPopMatrix();//������ �Ȳ�ġ ����

	glPopMatrix();//������ � ����


	glPushMatrix(); //Save ���� �
	glTranslated(45, 44, 0);
	glRotatef(left_sholder_x, 1, 0, 0);
	glRotatef(left_sholder_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_arm_top_object[0]);
	drawBoxBack(30, true, character_arm_top_object[1]);
	drawBoxLeft(30, true, character_arm_top_object[2]);
	drawBoxRight(30, true, character_arm_top_object[3]);
	drawBoxTop(30, true, character_arm_top_object[4]);
	drawBoxBottom(30, true, character_arm_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ���� �Ȳ�ġ
	glTranslated(0, -45, 0);
	glRotatef(left_elbow_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_arm_bottom_object[0]);
	drawBoxBack(30, true, character_arm_bottom_object[1]);
	drawBoxLeft(30, true, character_arm_bottom_object[2]);
	drawBoxRight(30, true, character_arm_bottom_object[3]);
	drawBoxTop(30, true, character_arm_top_object[5]);
	drawBoxBottom(30, true, character_arm_top_object[5]);
	glPopMatrix();//���� �Ȳ�ġ ����

	glPopMatrix();//���Ⱦ ����



	glPushMatrix(); //Save ������ ���
	glTranslated(-15, -40, 0);
	glRotatef(right_leg_x, 1, 0, 0);
	glRotatef(right_leg_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_leg_top_object[0]);
	drawBoxBack(30, true, character_leg_top_object[1]);
	drawBoxLeft(30, true, character_leg_top_object[2]);
	drawBoxRight(30, true, character_leg_top_object[3]);
	drawBoxTop(30, true, character_leg_top_object[4]);
	drawBoxBottom(30, true, character_leg_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ������ ����
	glTranslated(0, -45, 0);
	glRotatef(right_knee_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_leg_bottom_object[0]);
	drawBoxBack(30, true, character_leg_bottom_object[1]);
	drawBoxLeft(30, true, character_leg_bottom_object[2]);
	drawBoxRight(30, true, character_leg_bottom_object[3]);
	drawBoxTop(30, true, character_leg_top_object[4]);
	drawBoxBottom(30, true, character_leg_top_object[5]);
	glPopMatrix();//������ ���� ����

	glPopMatrix();//������ ��� ����


	glPushMatrix(); //Save ���� ���
	glTranslated(15, -40, 0);
	glRotatef(left_leg_x, 1, 0, 0);
	glRotatef(left_leg_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_leg_top_object[0]);
	drawBoxBack(30, true, character_leg_top_object[1]);
	drawBoxLeft(30, true, character_leg_top_object[2]);
	drawBoxRight(30, true, character_leg_top_object[3]);
	drawBoxTop(30, true, character_leg_top_object[4]);
	drawBoxBottom(30, true, character_leg_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ���� ����
	glTranslated(0, -45, 0);
	glRotatef(left_knee_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_leg_bottom_object[0]);
	drawBoxBack(30, true, character_leg_bottom_object[1]);
	drawBoxLeft(30, true, character_leg_bottom_object[2]);
	drawBoxRight(30, true, character_leg_bottom_object[3]);
	drawBoxTop(30, true, character_leg_top_object[4]);
	drawBoxBottom(30, true, character_leg_top_object[5]);
	glPopMatrix(); //���� ���� ����

	glPopMatrix(); //���ʰ�� ����
}

void animationCharleg()
{
	switch (character_state){
	case 0://������ ��������
		left_sholder_x = 0;
		left_sholder_y = 0;
		right_sholder_x = 0;
		right_sholder_y = 0;
		left_elbow_x = 0;
		right_elbow_x = 0;
		left_leg_x = 0;
		left_leg_y = 0;
		left_knee_x = 0;
		right_leg_x = 0;
		right_leg_y = 0;
		right_knee_x = 0;
		break;
	case 1://����,����
		//printf("%d\n", timer);
		if (timer < 150)
		{
			timer++;
			if (timer < 75)
			{
				left_leg_x = timer - 45;
				right_leg_x = 30 - timer;
				right_knee_x = timer - 10;
				//left_knee_x = 105-timer;
			}
			else
			{
				left_leg_x = 105 - timer;
				right_leg_x = timer - 120;
				right_knee_x = 120 - timer;
				//left_knee_x = timer - 120;
			}
		}
		else
			timer = 0;
		break;
	case 2://�¿��̵�
		break;
	}
}

void init_Texture(){
	nomal_Texture(block_Nomal_object);
	tree_Texture(block_Tree_object);
	head_Texture(character_head_object);
	body_Texture(character_body_object);
	arm_Texture(character_arm_top_object, character_arm_bottom_object);
	leg_Texture(character_leg_top_object, character_leg_bottom_object);
}