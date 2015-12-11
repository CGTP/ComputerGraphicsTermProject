#define _CRT_SECURE_NO_WARNINGS
#include "Texture_Load.h"
#include <math.h>
#include <string.h>


GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Keyboardup(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

void drawCharacter();//ĳ���� ��ο� �Լ�
void drawZomie(); // ���� ĳ���� ��ο� �Լ�
void init_Texture();//�ؽ��� �ε� �Լ�
void animationCharleg();//ĳ���� �ٸ� �ִϸ��̼� �Լ�
void Target(int x, int y);//ī�޶� �������� �Լ�
void Keyinput(int key);//Ű���� �����Է��� ���� �Է�ó�� �Լ�

int Time = 10;//Ÿ�̸� ���Žð�
char Input;

//ĳ���� �� ī�޶� ���� ����
float camxrotate = 0, camyrotate = -90, Viewx = 0, Viewy = 0, Viewz = -1000, Camx, Camy, Camz;
float Charx = 0, Charz = 0, Chary = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
float testx = 0, texty = 0;
int Charspeed = 20, Camdistance = 400, MouseSens = 25;
bool RotateCam = true, FirstPersonView = true;
bool Keybuffer[256];

// FPS ������ ���� ����
long fpsStartTime = 0L;             // Frame ���� �ð�
int frameCnt = 0;                      // ���ư� Frame ����
double timeElapsed = 0.0f;         // �� ���� ���� �ð� ����
float fps;
char draw_FPS[100];
int font = (int)GLUT_BITMAP_TIMES_ROMAN_24;
void renderBitmapCharacter(float x, float y, float z, void *font, char *string);


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

	glLoadIdentity();
	//------------------------------------------------------------------------
	// FPS ���ϴ� �κ�
	long fpsEndTime = timeGetTime();
	float timeDelta = (fpsEndTime - fpsStartTime) * 0.001f;
	// Frame ���� ���� 
	frameCnt++;
	timeElapsed += timeDelta;
	// FPS�� ���ϱ�.
	if (timeElapsed >= 1.0f){
		fps = (frameCnt / timeElapsed);
		frameCnt = 0;
		timeElapsed = 0.0f;
	}

	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	sprintf(draw_FPS, "FPS : %f", fps);
	char state2[100];
	sprintf(state2, "X : %d, Y : %d, Height : %d", int(Charx / 120), int(Charz / 120), int(Chary / 120));

	renderBitmapCharacter(-750, 540, -1000, (void *)font, draw_FPS);
	renderBitmapCharacter(-750, 500, -1000, (void *)font, state2);

	glDisable(GL_DEPTH_TEST);
	glPopMatrix();
	//------------------------------------------------------------------------
	if (FirstPersonView)
	{
		gluLookAt(Charx, Chary + 100, Charz, Charx + Viewx, Chary + Viewy, Charz + Viewz, 0.0, 1.0, 0.0);
	}
	else
	{
		gluLookAt(Charx + Camx, Chary + Camy, Charz + Camz, Charx + Viewx, Chary + Viewy, Charz + Viewz, 0.0, 1.0, 0.0);
	}

	//������
	glEnable(GL_DEPTH_TEST);                              // ������ �� ����
	glEnable(GL_CULL_FACE);                               // �ĸ� ����

	glPushMatrix();
	glTranslatef(Charx + Viewx, Chary + Viewy, Charz + Viewz);
	glutSolidCube(40);
	glPopMatrix();

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

	glPushMatrix();
	drawZomie();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(Charx, Chary, Charz);
	glRotatef(camxrotate + 180, 0, 1, 0);
	drawCharacter();
	glPopMatrix();

	//------------------------------------------------------------------------
	// FPS ���ϴ� �κ�.
	fpsStartTime = timeGetTime();
	//------------------------------------------------------------------------
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
	gluPerspective(60.0f, (float)w / (float)h, 0.1, 10000.0);

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
		character_state = 0;
}

void TimerFunction(int value)
{
	if (RotateCam)
		glutWarpPointer(400, 300);
	animationCharleg();//ĳ���� �ٸ� �ִϸ��̼�

	for (int i = 0; i < 256; i++)
	{
		if (Keybuffer[i])
			Keyinput(i);
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

void drawZomie(){
	glPushMatrix(); //Save �Ӹ�
	glTranslated(0, 75, 0);
	glRotatef(-(camyrotate + 90) / 3, 1, 0, 0);
	glScaled(1.0, 1.0, 0.7);
	drawBoxFront(30, false, zombie_head_object[0]);
	drawBoxBack(30, false, zombie_head_object[1]);
	drawBoxLeft(30, false, zombie_head_object[2]);
	drawBoxRight(30, false, zombie_head_object[3]);
	drawBoxTop(30, false, zombie_head_object[4]);
	drawBoxBottom(30, false, zombie_head_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save ����
	glScaled(1.0, 1.5, 0.5);
	drawBoxFront(30, false, zombie_body_object[0]);
	drawBoxBack(30, false, zombie_body_object[1]);
	drawBoxLeft(30, false, zombie_body_object[2]);
	drawBoxRight(30, false, zombie_body_object[3]);
	drawBoxTop(30, false, zombie_body_object[4]);
	drawBoxBottom(30, false, zombie_body_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save ������ �
	glTranslated(-45, 44, 0);
	glRotatef(right_sholder_x, 1, 0, 0);
	glRotatef(right_sholder_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_arm_top_object[0]);
	drawBoxBack(30, true, zombie_arm_top_object[1]);
	drawBoxLeft(30, true, zombie_arm_top_object[2]);
	drawBoxRight(30, true, zombie_arm_top_object[3]);
	drawBoxTop(30, true, zombie_arm_top_object[4]);
	drawBoxBottom(30, true, zombie_arm_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ������ �Ȳ�ġ
	glTranslated(0, -45, 0);
	glRotatef(right_elbow_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_arm_bottom_object[0]);
	drawBoxBack(30, true, zombie_arm_bottom_object[1]);
	drawBoxLeft(30, true, zombie_arm_bottom_object[2]);
	drawBoxRight(30, true, zombie_arm_bottom_object[3]);
	drawBoxTop(30, true, zombie_arm_top_object[5]);
	drawBoxBottom(30, true, zombie_arm_top_object[5]);
	glPopMatrix();//������ �Ȳ�ġ ����

	glPopMatrix();//������ � ����


	glPushMatrix(); //Save ���� �
	glTranslated(45, 44, 0);
	glRotatef(left_sholder_x, 1, 0, 0);
	glRotatef(left_sholder_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_arm_top_object[0]);
	drawBoxBack(30, true, zombie_arm_top_object[1]);
	drawBoxLeft(30, true, zombie_arm_top_object[2]);
	drawBoxRight(30, true, zombie_arm_top_object[3]);
	drawBoxTop(30, true, zombie_arm_top_object[4]);
	drawBoxBottom(30, true, zombie_arm_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ���� �Ȳ�ġ
	glTranslated(0, -45, 0);
	glRotatef(left_elbow_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_arm_bottom_object[0]);
	drawBoxBack(30, true, zombie_arm_bottom_object[1]);
	drawBoxLeft(30, true, zombie_arm_bottom_object[2]);
	drawBoxRight(30, true, zombie_arm_bottom_object[3]);
	drawBoxTop(30, true, zombie_arm_top_object[5]);
	drawBoxBottom(30, true, zombie_arm_top_object[5]);
	glPopMatrix();//���� �Ȳ�ġ ����

	glPopMatrix();//���Ⱦ ����



	glPushMatrix(); //Save ������ ���
	glTranslated(-15, -40, 0);
	glRotatef(right_leg_x, 1, 0, 0);
	glRotatef(right_leg_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_leg_top_object[0]);
	drawBoxBack(30, true, zombie_leg_top_object[1]);
	drawBoxLeft(30, true, zombie_leg_top_object[2]);
	drawBoxRight(30, true, zombie_leg_top_object[3]);
	drawBoxTop(30, true, zombie_leg_top_object[4]);
	drawBoxBottom(30, true, zombie_leg_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ������ ����
	glTranslated(0, -45, 0);
	glRotatef(right_knee_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_leg_bottom_object[0]);
	drawBoxBack(30, true, zombie_leg_bottom_object[1]);
	drawBoxLeft(30, true, zombie_leg_bottom_object[2]);
	drawBoxRight(30, true, zombie_leg_bottom_object[3]);
	drawBoxTop(30, true, zombie_leg_top_object[4]);
	drawBoxBottom(30, true, zombie_leg_top_object[5]);
	glPopMatrix();//������ ���� ����

	glPopMatrix();//������ ��� ����


	glPushMatrix(); //Save ���� ���
	glTranslated(15, -40, 0);
	glRotatef(left_leg_x, 1, 0, 0);
	glRotatef(left_leg_y, 0, 1, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_leg_top_object[0]);
	drawBoxBack(30, true, zombie_leg_top_object[1]);
	drawBoxLeft(30, true, zombie_leg_top_object[2]);
	drawBoxRight(30, true, zombie_leg_top_object[3]);
	drawBoxTop(30, true, zombie_leg_top_object[4]);
	drawBoxBottom(30, true, zombie_leg_top_object[5]);
	glScaled(2, 1.333333, 2);

	glPushMatrix(); //Save ���� ����
	glTranslated(0, -45, 0);
	glRotatef(left_knee_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_leg_bottom_object[0]);
	drawBoxBack(30, true, zombie_leg_bottom_object[1]);
	drawBoxLeft(30, true, zombie_leg_bottom_object[2]);
	drawBoxRight(30, true, zombie_leg_bottom_object[3]);
	drawBoxTop(30, true, zombie_leg_top_object[4]);
	drawBoxBottom(30, true, zombie_leg_top_object[5]);
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
}

void Target(int x, int y)
{
	if (RotateCam)
	{
		nx = 400 - x;
		ny = 300 - y;

		camxrotate = camxrotate + (nx / MouseSens);
		camyrotate = camyrotate + (ny / MouseSens);

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
		character_state = 1;
	}
	else if (key == 's')
	{
		Charx -= Charspeed * cos((-camxrotate - 90) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate - 90) * 3.141592 / 180);
		character_state = 1;
	}
	if (key == 'a')
	{
		Charx -= Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate) * 3.141592 / 180);
		character_state = 2;
	}
	else if (key == 'd')
	{
		Charx += Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz += Charspeed * sin((-camxrotate) * 3.141592 / 180);
		character_state = 2;
	}
	//-------------------------------------------------------
	// ������ ���� ���ϰ� �ϱ� ���ؼ�.
	if (key == 'r'){
		Chary += 5;
	}
	if (key == 't'){
		Chary -= 5;
	}
	//-------------------------------------------------------
	if (key == 'c')
	{
		glutSetCursor(GLUT_CURSOR_NONE);
		if (RotateCam)
			RotateCam = false;
		else
			RotateCam = true;
		Keybuffer[key] = false;
	}
	else if (key == 'f')
	{
		if (FirstPersonView)
			FirstPersonView = false;
		else
			FirstPersonView = true;
		Keybuffer[key] = false;
	}
	else if (key == '+')
	{
		Camdistance--;
		if (Camdistance < 50)
			Camdistance = 50;
	}
	else if (key == '-')
	{
		Camdistance++;
		if (Camdistance > 1000)
			Camdistance = 1000;
	}
	else if (key == '[')
	{
		MouseSens++;
		if (MouseSens < 1)
			MouseSens = 1;
		printf("���� ���콺 ������ %d �Դϴ�.(default : 25)\n", MouseSens);
		Keybuffer[key] = false;
	}
	else if (key == ']')
	{
		MouseSens--;
		if (MouseSens > 100)
			MouseSens = 100;
		printf("���� ���콺 ������ %d �Դϴ�.(default : 25)\n", MouseSens);
		Keybuffer[key] = false;
	}

	if (key == 27)
	{
		exit(0);
	}
}

void renderBitmapCharacter(float x, float y, float z, void *font, char *string){
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}