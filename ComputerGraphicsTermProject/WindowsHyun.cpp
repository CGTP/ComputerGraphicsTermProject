#define _CRT_SECURE_NO_WARNINGS
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
void animationChararm();//ĳ���� �� �ִϸ��̼� �Լ�
void Target(int x, int y);//ī�޶� �������� �Լ�
void Keyinput(int key);//Ű���� �����Է��� ���� �Է�ó�� �Լ�
void drawHud();//HUD �׸��� �Լ�
void crashCheck();//�浹üũ

void drawTestbox();/////////////////////////////////////////////////�׽�Ʈ�ڽ�

int Time = 10;//Ÿ�̸� ���Žð�
int width, height;
char Input;

int rifleammo = 120, rifleload = 30, hp = 100;
char ammo[10], health[10];

//ĳ���� �� ī�޶� ���� ����
float camxrotate = 0, camyrotate = -90, Viewx = 0, Viewy = 0, Viewz = -1000, Camx, Camy, Camz;
float Charx = 0, Charz = 0, Chary = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
float testx = 0, texty = 0;
int Charspeed = 50, Camdistance = 400, MouseSens = 25;
bool RotateCam = true, FirstPersonView = true;
bool Keybuffer[256];

// FPS ������ ���� ����
float fps;
char draw_FPS[100];
void update_FPS();

//�ִϸ��̼� ����
int character_up_state = 0, character_down_state = 0, timer = 0;//�̵� �ִϸ��̼� ���п�
float head_angle_x;//�Ӹ�ȸ��
float left_sholder_x, left_sholder_y, left_sholder_z, right_sholder_x, right_sholder_y, right_sholder_z, left_elbow_x, right_elbow_x;//��ȸ��
float left_leg_x, left_leg_y, left_knee_x, right_leg_x, right_leg_y, right_knee_x;//�ٸ�ȸ��

//�� ������ ����
int map_DATA[6][72][27];

//�浹üũ �Ÿ�
int crashdist = 20;

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
	for (int i = 0; i < 256; i++)
		Keybuffer[i] = false;

	//�ʿ��� �ݹ� �Լ� ����
	glutDisplayFunc(DrawScene); //��� �Լ��� ����
	glutTimerFunc(Time, TimerFunction, 1);//Ÿ�̸� �ݹ� �Լ�

	glutPassiveMotionFunc(Motion);//���콺���
	glutMouseFunc(Mouse);//���콺�Է�
	glutMotionFunc(Motion);//Ŭ���ÿ��� �����̰Բ� ���콺��� ����

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

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	update_FPS();
	gluPerspective(60.0f, (float)width / (float)height, 0.1, 5000.0);
	glMatrixMode(GL_MODELVIEW);

	//3D Draw----------------------------------------------------------------------
	glLoadIdentity();
	if (FirstPersonView)
		gluLookAt(Charx, Chary + 170, Charz, Charx + Viewx, Chary + Viewy, Charz + Viewz, 0.0, 1.0, 0.0);
	else
		gluLookAt(Charx + Camx, Chary + Camy + 70, Charz + Camz, Charx + Viewx, Chary + Viewy, Charz + Viewz, 0.0, 1.0, 0.0);

	//������
	glEnable(GL_DEPTH_TEST);                              // ������ �� ����
	glEnable(GL_CULL_FACE);                               // �ĸ� ����

	glPushMatrix();//ĳ���� �׸���
	glTranslatef(Charx, Chary + 70, Charz);		//ĳ���� ��ġ �̵�
	glRotatef(camxrotate + 180, 0, 1, 0);	//ĳ���� ���� ��ü ȸ��
	drawCharacter();	//ĳ���� �׸���
	glPopMatrix();
	//3D END------------------------------------------------------------------------------
	//drawTestbox();

	draw_wall_background(wall_background_object);

	glTranslatef(60, 0, 60);

	glPushMatrix();
	draw_Ground(block_Nomal_object);
	glPopMatrix();

	glPushMatrix();
	draw_Wall(block_Brick_object);
	glPopMatrix();

	glPushMatrix();
	draw_Wooden(block_Wooden_object);
	glPopMatrix();

	glPushMatrix();
	draw_Stone(block_Stone_object);
	glPopMatrix();

	glPopMatrix();

	int X = (Charx / 120);
	int Z = (Charz / 120);

	//printf("%d / %d\n", X, Z);


	//

	//2D Draw-----------------------------------------------------------------------------
	drawHud();
	//2D END------------------------------------------------------------------------------

	glutSwapBuffers(); //ȭ�鿡 ����ϱ�
}//end of drawScene

GLvoid Reshape(int w, int h)
{
	//����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);
	width = w;
	height = h;

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
	Target(x, y);
}

void Keyboard(unsigned char key, int x, int y)
{
	Keybuffer[key] = true;
	glutPostRedisplay();
}//end of Keyboard

void Keyboardup(unsigned char key, int x, int y)
{
	Keybuffer[key] = false;
	if (!Keybuffer['w'] && !Keybuffer['a'] && !Keybuffer['s'] && !Keybuffer['d'])
		character_down_state = 0;
}

void TimerFunction(int value)
{
	switch (value)
	{
	case 1:
		if (RotateCam)
			glutWarpPointer(400, 300);
		animationCharleg();//ĳ���� �ٸ� �ִϸ��̼�
		animationChararm();//ĳ���� �� �ִϸ��̼�



		crashCheck();



		for (int i = 0; i < 256; i++)
		{
			if (Keybuffer[i])
				Keyinput(i);
		}
		break;
	case 2:
		break;
	}
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
	glRotatef(-right_sholder_x + 210, 1, 0, 0);
	glRotatef(right_sholder_y, 0, 1, 0);
	glRotatef(right_sholder_z, 0, 0, 1);
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
	glRotatef(-left_sholder_x - 90, 1, 0, 0);
	glRotatef(left_sholder_y, 0, 1, 0);
	glRotatef(left_sholder_z, 0, 0, 1);
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

void animationChararm()
{
	switch (character_up_state)
	{
	case 0:
		//left_sholder_x = 0;
		left_sholder_y = 70;
		left_sholder_z = -75;
		//right_sholder_x = -60;
		right_sholder_y = 30;
		right_sholder_z = 0;
		left_elbow_x = 25;
		right_elbow_x = -30;
		break;
	case 1://������
		break;
	case 2://����
		left_sholder_x = 0;
		left_sholder_y = 0;
		right_sholder_x = 0;
		right_sholder_y = 0;
		left_elbow_x = 0;
		right_elbow_x = 0;
		break;
	}
}

void animationCharleg()
{
	switch (character_down_state){
	case 0://������ ������ ��
		left_leg_x = 0;
		left_leg_y = 0;
		left_knee_x = 0;
		right_leg_x = 0;
		right_leg_y = 0;
		right_knee_x = 0;
		break;
	case 1://����,����
		if (timer < 150)
		{
			timer += 2;
			if (timer < 75)
			{
				left_leg_x = timer - 45;
				right_leg_x = 30 - timer;
				left_knee_x = 0;
				if (timer < 38)
					right_knee_x = timer;
				else
					right_knee_x = 38 - (timer - 38);
			}
			else
			{
				left_leg_x = 105 - timer;
				right_leg_x = timer - 120;
				right_knee_x = 0;

				if (timer < 113)
					left_knee_x = timer - 75;
				else
					left_knee_x = 38 - (timer - 113);
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
	brick_Texture(block_Brick_object);
	wooden_Texture(block_Wooden_object);
	stone_Texture(block_Stone_object);

	head_Texture(character_head_object);
	body_Texture(character_body_object);
	arm_Texture(character_arm_top_object, character_arm_bottom_object);
	leg_Texture(character_leg_top_object, character_leg_bottom_object);

	zombie_head_Texture(zombie_head_object);
	zombie_body_Texture(zombie_body_object);
	zombie_arm_Texture(zombie_arm_top_object, zombie_arm_bottom_object);
	zombie_leg_Texture(zombie_leg_top_object, zombie_leg_bottom_object);

	wall_background_Texture(wall_background_object);
}

void Target(int x, int y)
{
	if (RotateCam)
	{
		nx = 400 - x;
		ny = 300 - y;

		camxrotate = camxrotate + (nx / MouseSens);
		camyrotate = camyrotate + (ny / MouseSens);
		left_sholder_x = camyrotate;
		right_sholder_x = camyrotate;

		Viewz = 1000 * sin((camyrotate)* 3.141592 / 180) * cos((camxrotate)* 3.141592 / 180);
		Viewx = 1000 * sin((camyrotate)* 3.141592 / 180) * sin((camxrotate)* 3.141592 / 180);
		Viewy = 1000 * cos((camyrotate)* 3.141592 / 180);

		Camz = -Camdistance * sin((camyrotate)* 3.141592 / 180) * cos((camxrotate + 15)* 3.141592 / 180);
		Camx = -Camdistance * sin((camyrotate)* 3.141592 / 180) * sin((camxrotate + 15)* 3.141592 / 180);
		Camy = -Camdistance * cos((camyrotate - 15)* 3.141592 / 180);


		if (camxrotate <= -360 || camxrotate >= 360)
			camxrotate = 0;

		if (camyrotate < -179)
			camyrotate = -179;
		else if (camyrotate > -1)
			camyrotate = -1;
		bx = nx;
		by = ny;

	}
}



void Keyinput(int key)
{
	if (key == 'w')
	{
		Charx += Charspeed * cos((-camxrotate - 90) * 3.141592 / 180);
		Charz += Charspeed * sin((-camxrotate - 90) * 3.141592 / 180);
		character_down_state = 1;
	}
	else if (key == 's')
	{
		Charx -= Charspeed * cos((-camxrotate - 90) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate - 90) * 3.141592 / 180);
		character_down_state = 1;
	}
	if (key == 'a')
	{
		Charx -= Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate) * 3.141592 / 180);
		character_down_state = 2;
	}
	else if (key == 'd')
	{
		Charx += Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz += Charspeed * sin((-camxrotate) * 3.141592 / 180);
		character_down_state = 2;
	}


	switch (key)
	{
	case '1':
		Chary += 10;
		break;
	case '2':
		Chary -= 10;
		break;
	case 'c':
		glutSetCursor(GLUT_CURSOR_NONE);
		if (RotateCam)
			RotateCam = false;
		else
			RotateCam = true;
		Keybuffer[key] = false;
		break;
	case 'f':
		if (FirstPersonView)
			FirstPersonView = false;
		else
			FirstPersonView = true;
		Keybuffer[key] = false;
		break;
	case '+':
		Camdistance--;
		if (Camdistance < 50)
			Camdistance = 50;
		break;
	case '-':
		Camdistance++;
		if (Camdistance > 1000)
			Camdistance = 1000;
		break;
	case '[':
		MouseSens++;
		if (MouseSens < 1)
			MouseSens = 1;
		printf("���� ���콺 ������ %d �Դϴ�.(default : 25)\n", MouseSens);
		Keybuffer[key] = false;
		break;
	case ']':
		MouseSens--;
		if (MouseSens > 100)
			MouseSens = 100;
		printf("���� ���콺 ������ %d �Դϴ�.(default : 25)\n", MouseSens);
		Keybuffer[key] = false;
		break;
	case 27:
		exit(0);
		break;
	}
}

void drawHud()
{
	glPushMatrix();

	glViewport(0, 0, 800, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);// Crosshair
	glVertex2f(370, 300);
	glVertex2f(390, 300);

	glVertex2f(410, 300);
	glVertex2f(430, 300);

	glVertex2f(400, 270);
	glVertex2f(400, 290);

	glVertex2f(400, 310);
	glVertex2f(400, 330);
	glEnd();

	glPushMatrix();//�Ѿ� ǥ��
	glColor3f(0, 1, 0);
	glTranslatef(680, 570, 0);
	glRasterPos2f(0.0, 0.0);
	sprintf(ammo, "%d / %d", rifleload, rifleammo);
	int len = (int)strlen(ammo);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ammo[i]);
	glPopMatrix();

	glPushMatrix();//ü�� ǥ��
	glColor3f(1, 0, 0);
	glTranslatef(20, 570, 0);
	glRasterPos2f(0.0, 0.0);
	sprintf(health, "%d", hp);
	len = (int)strlen(ammo);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, health[i]);
	glPopMatrix();

	glPushMatrix();//FPS ǥ��
	glColor3f(1, 0, 0);
	glTranslatef(20, 25, 0);
	glRasterPos2f(0.0, 0.0);
	sprintf(draw_FPS, "FPS : %f", fps);
	len = (int)strlen(draw_FPS);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, draw_FPS[i]);
	glPopMatrix();

	glPopMatrix();
}

void drawTestbox()
{

	glPushMatrix();//ĳ���Ͱ� �ٶ󺸴� ���� ��ο�
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(Charx + Viewx, Chary + Viewy, Charz + Viewz);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();//�ٴ� �׸���
	glTranslatef(0, -100, 0);
	glScalef(1, 0.01, 1);
	glutWireCube(2000);
	glPopMatrix();//�ٴ� �׸��� ����

	glPushMatrix();//�ٴ� �׸���
	glColor3f(1, 0, 0);//������ z��
	glTranslatef(0, 0, -1000);
	glutSolidCube(100);
	glPopMatrix();//�ٴ� �׸��� ����

	glPushMatrix();//�ٴ� �׸���
	glColor3f(0, 0, 1);//�Ķ���
	glTranslatef(0, 0, 1000);//z��
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
}

void drawPistol()
{
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glPopMatrix();
}

void crashCheck()
{
	int X = (Charx / 120);
	int Z = (Charz / 120);

	if (Charx < 0)
		X -= 1;
	if (Charz < 0)
		Z -= 1;

	//printf("%d / %d\n", X, Z);
	//printf("%f / %f\n", X, Z);

	for (int z = Z - 1; z < Z + 2; z++)
	{
		for (int x = X - 1; x < X + 2; x++)
		{
			if (map_DATA[1][x + 36][z + 13] == 1)
			{
				if ((x == X - 1) && (z == Z - 1))
				{
					/*if (Charx < ((x * 120) + 120 + crashdist))
					Charx = ((x * 120) + 120 + crashdist);
					if (Charz < ((z * 120) + 120 + crashdist))
					Charz = ((z * 120) + 120 + crashdist);*/
				}
				else if ((x == X - 1) && (z == Z + 1))
				{
					/*if (Charx < ((x * 120) + 120 + crashdist))
					Charx = ((x * 120) + 120 + crashdist);
					if (((z * 120) - crashdist) < Charz)
					Charz = ((z * 120) - crashdist);*/
				}
				else if ((x == X + 1) && (z == Z - 1))
				{
					/*if (((x * 120) - crashdist) < Charx)
					Charx = ((x * 120) - crashdist);
					if (Charz < ((z * 120) + 120 + crashdist))
					Charz = ((z * 120) + 120 + crashdist);*/
				}
				else if ((x == X + 1) && (z == Z + 1))
				{
					/*if (((x * 120) - crashdist) < Charx)
					Charx = ((x * 120) - crashdist);
					if (((z * 120) - crashdist) < Charz)
					Charz = ((z * 120) - crashdist);*/
				}


				else if (x == X - 1)
				{
					if (Charx < ((x * 120) + 120 + crashdist))
						Charx = ((x * 120) + 120 + crashdist);
				}
				else if (X + 1 == x)
				{
					if (((x * 120) - crashdist) < Charx)
						Charx = ((x * 120) - crashdist);
				}

				else if (z == Z - 1)
				{
					if (Charz < ((z * 120) + 120 + crashdist))
						Charz = ((z * 120) + 120 + crashdist);
				}
				else if (Z + 1 == z)
				{
					if (((z * 120) - crashdist) < Charz)
						Charz = ((z * 120) - crashdist);
				}
			}//end of if
		}//end of inner for
	}//end of outer for
}

void update_FPS(){
	static DWORD frameCount = 0;            //������ ī��Ʈ��
	static float timeElapsed = 0.0f;            //�帥 �ð�
	static DWORD lastTime = timeGetTime();   //������ �ð�(temp����)

	DWORD curTime = timeGetTime();      //���� �ð�
	float timeDelta = (curTime - lastTime)*0.001f;        //timeDelta(1�������� �帥 �ð�) 1�ʴ����� �ٲ��ش�.

	timeElapsed += timeDelta;

	frameCount++;

	if (timeElapsed >= 1.0f)         //�帥�ð��� 1���̻��̸� ���� �ϰ������ ó��
	{
		fps = (float)frameCount / timeElapsed;
		frameCount = 0;
		timeElapsed = 0.0f;
	}
	else
	{
		//Sleep(0.002f * 1000);   // 100fps   
	}


	lastTime = curTime;
}