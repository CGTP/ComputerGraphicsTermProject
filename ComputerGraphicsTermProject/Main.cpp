#define _CRT_SECURE_NO_WARNINGS
#include "Texture_Load.h"
#include <math.h>


GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
typedef struct Bullet
{
	float x, y, z;
	float fx, fy, fz;
	Bullet * next;
}Bullet;

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Keyboardup(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

void drawCharacter();//ĳ���� ��ο� �Լ�
void drawZombie(); // ���� ��ο� �Լ�
void init_Texture();//�ؽ��� �ε� �Լ�
void animationCharleg();//ĳ���� �ٸ� �ִϸ��̼� �Լ�
void animationChararm();//ĳ���� �� �ִϸ��̼� �Լ�
void Target(int x, int y);//ī�޶� �������� �Լ�
void Keyinput(int key);//Ű���� �����Է��� ���� �Է�ó�� �Լ�
void drawHud();//HUD �׸��� �Լ�
void crashCheck();//�浹üũ

void drawPistol();//���ѱ׸���
void bulletCreate();//�Ѿ� ����
void bulletDestroy(Bullet * Del);//�Ѿ� �ı�
void drawBullet();//�Ѿ� �׸���

int Time = 10, Bullet_Time = 1;//Ÿ�̸� ���Žð�
int width, height;
char Input;

int rifleammo = 120, rifleload = 30, hp = 100;
char ammo[10], health[10];

//ĳ���� �� ī�޶� ���� ����
float camxrotate = 0, camyrotate = -90, Viewx = 0, Viewy = 0, Viewz = -1000, Camx, Camy, Camz;
float Charx = 0, Charz = 0, Chary = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
float testx = 0, texty = 0;
float gravity = 0;
int Charspeed = 8, Camdistance = 400, MouseSens = 25;
bool RotateCam = true, FirstPersonView = true;
bool Keybuffer[256];

// FPS ������ ���� ����
float fps;
char draw_FPS[100];
void update_FPS();

//�ִϸ��̼� ����
int character_up_state = 2, character_down_state = 0, legtimer = 0;//�̵� �ִϸ��̼� ���п�
float head_angle_x;//�Ӹ�ȸ��
float left_sholder_x, left_sholder_y, left_sholder_z, right_sholder_x, right_sholder_y, right_sholder_z, left_elbow_x, right_elbow_x;//��ȸ��
float left_leg_x, left_leg_y, left_knee_x, right_leg_x, right_leg_y, right_knee_x, left_leg_z, right_leg_z;//�ٸ�ȸ��
bool sight = false, jump = false, crouch = false;//������

//�� ������ ����
int map_DATA[6][72][27];

//�浹üũ �Ÿ�
int crashdist = 20;

//�Ѿ˵�����
Bullet * Head = NULL;
Bullet * Temp = NULL;
Bullet * CTemp = NULL;
Bullet * DTemp = NULL;

// ���� ����
bool turn_Light = true;
void show_Light(){
	GLfloat AmbientLight[] = { 0.1, 0.1, 0.1, 1.0f };
	GLfloat DiffuseLight[] = { 0.8, 0.8, 0.8, 1.0f };
	GLfloat lightpos[] = { Charx, 200, Charz, 1 };
	GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	if (sight)
	{
		glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, (0, 0, 1));
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, (30.0));
	}
	else{
		glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, (0, 0, 1));
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, (70.0));
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
}


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
	glutTimerFunc(Bullet_Time, TimerFunction, 2);

	glutPassiveMotionFunc(Motion);//���콺���
	glutMouseFunc(Mouse);//���콺�Է�
	glutMotionFunc(Motion);//Ŭ���ÿ��� �����̰Բ� ���콺��� ����

	glutKeyboardFunc(Keyboard);//Ű�����Է�
	glutKeyboardUpFunc(Keyboardup);//Ű���� ��ư�� ���� ��

	PlaySound("SoundData/BGM.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

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
	gluPerspective(60.0f, (float)width / (float)height, 0.1, 10000.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);      // ���� Ȱ��ȭ
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	if (turn_Light == true){
		glEnable(GL_LIGHT0);
		show_Light();
	}
	else{
		glDisable(GL_LIGHT0);
	}

	//3D Draw----------------------------------------------------------------------
	glLoadIdentity();
	update_FPS();
	if (FirstPersonView)
	{
		if (character_down_state == 3)
			gluLookAt(Charx, Chary + 100, Charz, Charx + Viewx, Chary + Viewy + 170, Charz + Viewz, 0.0, 1.0, 0.0);
		else
			gluLookAt(Charx, Chary + 170, Charz, Charx + Viewx, Chary + Viewy + 170, Charz + Viewz, 0.0, 1.0, 0.0);
	}
	else
	{
		if (character_down_state == 3)
			gluLookAt(Charx + Camx, Chary + Camy + 120, Charz + Camz, Charx + Viewx, Chary + Viewy + 190, Charz + Viewz, 0.0, 1.0, 0.0);
		else
			gluLookAt(Charx + Camx, Chary + Camy + 190, Charz + Camz, Charx + Viewx, Chary + Viewy + 190, Charz + Viewz, 0.0, 1.0, 0.0);
	}

	glPushMatrix();
	//������
	glEnable(GL_DEPTH_TEST);                              // ������ �� ����
	glEnable(GL_CULL_FACE);                               // �ĸ� ����

	glPushMatrix();//ĳ���� �׸���
	if (character_down_state == 0 || character_down_state == 1 || character_down_state == 2)
		glTranslatef(Charx, Chary + 70, Charz);      //ĳ���� ��ġ �̵�
	else if (character_down_state == 3)
		glTranslatef(Charx, Chary, Charz);      //ĳ���� ��ġ �̵�

	glRotatef(camxrotate + 180, 0, 1, 0);   //ĳ���� ���� ��ü ȸ��
	drawCharacter();//ĳ���� �׸���
	if (character_up_state == 1 || character_up_state == 2)
		drawPistol();//���ѱ׸���
	glPopMatrix();//ĳ���ͱ׸��� end

	//3D END------------------------------------------------------------------------------
	drawBullet();//�Ѿ˱׸���

	glPushMatrix();//���� �׸���
	glTranslatef(0, 70, 0);
	drawZombie();
	glPopMatrix();//���� �׸��� end


	glPushMatrix();//��ϱ׸���
	glTranslatef(60, 0, 60);

	glPushMatrix();//��
	draw_Ground(block_Nomal_object);
	glPopMatrix();//��end
	glPushMatrix();//����
	draw_Wall(block_Brick_object);
	glPopMatrix();//����end
	glPushMatrix();//����
	draw_Wooden(block_Wooden_object);
	glPopMatrix();//����end
	glPushMatrix();//��
	draw_Stone(block_Stone_object);
	glPopMatrix();//��end

	glPopMatrix();//��ϱ׸��� end

	//2D Draw-----------------------------------------------------------------------------
	drawHud();
	//2D END------------------------------------------------------------------------------
	glPopMatrix();
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		bulletCreate();
		glutTimerFunc(Bullet_Time, TimerFunction, 2);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (FirstPersonView){
			if (sight){
				sight = false;
				turn_Light = true;
			}
			else{
				sight = true;
				turn_Light = true;
			}
		}
		else{}

	}
}//end of Mouse

void Motion(int x, int y)
{
	Target(x, y);
}

void Keyboard(unsigned char key, int x, int y)
{
	Keybuffer[key] = true;
	switch (key)
	{
	case ' '://�����̽���
		if (jump){}
		else
		{
			jump = true;
			gravity = 15;
		}
		break;
	}
}//end of Keyboard

void Keyboardup(unsigned char key, int x, int y)
{
	Keybuffer[key] = false;
	if (!Keybuffer['w'] && !Keybuffer['a'] && !Keybuffer['s'] && !Keybuffer['d'])
		character_down_state = 0;
	if (Keybuffer['x'] == false)
	{
		Charspeed = 8;
		crouch = false;
	}
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

		Chary += gravity;
		if (jump)
		{
			gravity -= 0.5;
			character_down_state = 3;
		}


		for (int i = 0; i < 256; i++)
			if (Keybuffer[i])
				Keyinput(i);
		crashCheck();
		glutPostRedisplay();
		glutTimerFunc(Time, TimerFunction, 1);
		break;
	case 2:
		if (Head != NULL)
		{
			Temp = Head;
			while (Temp != NULL)
			{
				Temp->x += Temp->fx;
				Temp->y += Temp->fy;
				Temp->z += Temp->fz;
				if ((Temp->x < (-37 * 120)) || (Temp->x >(37 * 120)) || (Temp->y < 0) || (Temp->y >(7 * 120)) || (Temp->z < (-14 * 120)) || (Temp->z >(14 * 120)))
				{
					Bullet * Del = Temp;
					Temp = Temp->next;
					bulletDestroy(Del);
				}
				else
					Temp = Temp->next;
			}
			glutPostRedisplay();
			glutTimerFunc(Bullet_Time, TimerFunction, 2);
		}

		break;
	}


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
	glPopMatrix(); //�Ӹ� end

	glPushMatrix(); //Save ����
	glScaled(1.0, 1.5, 0.5);
	drawBoxFront(30, false, character_body_object[0]);
	drawBoxBack(30, false, character_body_object[1]);
	drawBoxLeft(30, false, character_body_object[2]);
	drawBoxRight(30, false, character_body_object[3]);
	drawBoxTop(30, false, character_body_object[4]);
	drawBoxBottom(30, false, character_body_object[5]);
	glPopMatrix(); //���� end


	if (sight){}
	else
	{
		if (character_up_state == 1 || character_up_state == 2)
		{
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
			glPushMatrix();
			glScaled(0.5, 0.75, 0.5);
			drawBoxFront(30, true, character_arm_bottom_object[0]);
			drawBoxBack(30, true, character_arm_bottom_object[1]);
			drawBoxLeft(30, true, character_arm_bottom_object[2]);
			drawBoxRight(30, true, character_arm_bottom_object[3]);
			drawBoxTop(30, true, character_arm_top_object[5]);
			drawBoxBottom(30, true, character_arm_top_object[5]);
			glPopMatrix();
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
		}
		else if (character_up_state == 0)
		{
			glPushMatrix(); //Save ������ �
			glTranslated(-45, 44, 0);
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
			glPushMatrix();
			glScaled(0.5, 0.75, 0.5);
			drawBoxFront(30, true, character_arm_bottom_object[0]);
			drawBoxBack(30, true, character_arm_bottom_object[1]);
			drawBoxLeft(30, true, character_arm_bottom_object[2]);
			drawBoxRight(30, true, character_arm_bottom_object[3]);
			drawBoxTop(30, true, character_arm_top_object[5]);
			drawBoxBottom(30, true, character_arm_top_object[5]);
			glPopMatrix();
			glPopMatrix();//������ �Ȳ�ġ ����
			glPopMatrix();//������ � ����


			glPushMatrix(); //Save ���� � 
			glTranslated(45, 44, 0);
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
			glScaled(0.5, 0.75, 0.5);
			drawBoxFront(30, true, character_arm_bottom_object[0]);
			drawBoxBack(30, true, character_arm_bottom_object[1]);
			drawBoxLeft(30, true, character_arm_bottom_object[2]);
			drawBoxRight(30, true, character_arm_bottom_object[3]);
			drawBoxTop(30, true, character_arm_top_object[5]);
			drawBoxBottom(30, true, character_arm_top_object[5]);
			glPopMatrix();//���� �Ȳ�ġ ����
			glPopMatrix();//���Ⱦ ����
		}
	}


	glPushMatrix(); //Save ������ ���
	glTranslated(-15, -40, 0);
	glRotatef(right_leg_x, 1, 0, 0);
	glRotatef(right_leg_y, 0, 1, 0);
	glRotatef(right_leg_z, 0, 0, 1);
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
	glRotatef(left_leg_z, 0, 0, 1);
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

void drawZombie(){
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
	glPopMatrix(); //�Ӹ� end

	glPushMatrix(); //Save ����
	glScaled(1.0, 1.5, 0.5);
	drawBoxFront(30, false, zombie_body_object[0]);
	drawBoxBack(30, false, zombie_body_object[1]);
	drawBoxLeft(30, false, zombie_body_object[2]);
	drawBoxRight(30, false, zombie_body_object[3]);
	drawBoxTop(30, false, zombie_body_object[4]);
	drawBoxBottom(30, false, zombie_body_object[5]);
	glPopMatrix(); //���� end



	glPushMatrix(); //Save ������ �
	glTranslated(-45, 44, 0);
	glRotatef(-right_sholder_x + 210, 1, 0, 0);
	glRotatef(right_sholder_y, 0, 1, 0);
	glRotatef(right_sholder_z, 0, 0, 1);
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
	glPushMatrix();
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, zombie_arm_bottom_object[0]);
	drawBoxBack(30, true, zombie_arm_bottom_object[1]);
	drawBoxLeft(30, true, zombie_arm_bottom_object[2]);
	drawBoxRight(30, true, zombie_arm_bottom_object[3]);
	drawBoxTop(30, true, zombie_arm_top_object[5]);
	drawBoxBottom(30, true, zombie_arm_top_object[5]);
	glPopMatrix();
	glPopMatrix();//������ �Ȳ�ġ ����
	glPopMatrix();//������ � ����


	glPushMatrix(); //Save ���� � 
	glTranslated(45, 44, 0);
	glRotatef(-left_sholder_x - 90, 1, 0, 0);
	glRotatef(left_sholder_y, 0, 1, 0);
	glRotatef(left_sholder_z, 0, 0, 1);
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

void animationChararm()
{
	switch (character_up_state)
	{
	case 2://����
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
		//left_sholder_x = 0;
		left_sholder_y = 70;
		left_sholder_z = -75;
		//right_sholder_x = -60;
		right_sholder_y = 30;
		right_sholder_z = 0;
		left_elbow_x = 25;
		right_elbow_x = -30;
		break;
	case 0://�⺻�ڼ�
		//left_sholder_x = -90;
		left_sholder_y = 0;
		left_sholder_z = 0;
		//right_sholder_x = 0;
		right_sholder_y = 0;
		right_sholder_z = 0;
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
		left_leg_z = 0;
		left_knee_x = 0;
		right_leg_x = 0;
		right_leg_y = 0;
		right_leg_z = 0;
		right_knee_x = 0;
		break;
	case 1://����,����
		left_leg_z = 0;
		right_leg_z = 0;
		if (legtimer < 150)
		{
			legtimer += 2;
			if (legtimer < 75)
			{
				left_leg_x = legtimer - 45;
				right_leg_x = 30 - legtimer;
				left_knee_x = 0;
				if (legtimer < 38)
					right_knee_x = legtimer;
				else
					right_knee_x = 38 - (legtimer - 38);
			}
			else
			{
				left_leg_x = 105 - legtimer;
				right_leg_x = legtimer - 120;
				right_knee_x = 0;

				if (legtimer < 113)
					left_knee_x = legtimer - 75;
				else
					left_knee_x = 38 - (legtimer - 113);
			}
		}
		else
			legtimer = 0;
		break;
	case 2://�¿��̵�
		break;
	case 3://�ɱ�
		left_leg_x = -75;
		left_leg_y = 0;
		left_leg_z = 40;
		left_knee_x = 130;
		right_leg_x = -75;
		right_leg_y = 0;
		right_leg_z = -15;
		right_knee_x = 130;
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

		Viewz = 10000 * sin((camyrotate)* 3.141592 / 180) * cos((camxrotate)* 3.141592 / 180);
		Viewx = 10000 * sin((camyrotate)* 3.141592 / 180) * sin((camxrotate)* 3.141592 / 180);
		Viewy = 10000 * cos((camyrotate)* 3.141592 / 180);

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
		if (jump)
			character_down_state = 3;
		else
			character_down_state = 1;
	}
	else if (key == 's')
	{
		Charx -= Charspeed * cos((-camxrotate - 90) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate - 90) * 3.141592 / 180);
		if (jump)
			character_down_state = 3;
		else
			character_down_state = 1;
	}
	if (key == 'a')
	{
		Charx -= Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz -= Charspeed * sin((-camxrotate) * 3.141592 / 180);
		if (jump)
			character_down_state = 3;
		else
			character_down_state = 1;
	}
	else if (key == 'd')
	{
		Charx += Charspeed * cos((-camxrotate) * 3.141592 / 180);
		Charz += Charspeed * sin((-camxrotate) * 3.141592 / 180);
		if (jump)
			character_down_state = 3;
		else
			character_down_state = 1;
	}


	switch (key)
	{
	case '1':
		character_up_state = 1;
		break;
	case '2':
		character_up_state = 2;
		break;
	case '3':
		character_up_state = 0;
		break;
	case 'l':
		if (turn_Light == false){
			turn_Light = true;
		}
		else{
			turn_Light = false;
		}
		Keybuffer[key] = false;
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
		if (FirstPersonView){
			FirstPersonView = false;
			sight = false;
			turn_Light = true;
		}
		else{
			FirstPersonView = true;
			turn_Light = true;
		}
		Keybuffer[key] = false;
		break;
	case 'x':
		character_down_state = 3;
		Charspeed = 4;
		crouch = true;
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

	glDisable(GL_LIGHTING);      // ���� Ȱ��ȭ
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);

	draw_Crosshair(sight);// ũ�ν� ��� ����

	draw_MiniMap(Charx, Charz);// �̴ϸ� ����

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
	glTranslatef(640, 25, 0);
	glRasterPos2f(0.0, 0.0);
	sprintf(draw_FPS, "FPS : %f", fps);
	len = (int)strlen(draw_FPS);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, draw_FPS[i]);
	glPopMatrix();

	glPopMatrix();
}

void drawPistol()
{
	glPushMatrix();
	if (sight){
		glTranslatef(0, 100, 0);
	}
	else{
		glTranslatef(0, 25, 0);
	}
	glRotatef(-right_sholder_x - 90, 1, 0, 0);
	if (sight){ glTranslatef(0, -15, 50); }
	else{ glTranslatef(-20, 10, 100); }

	glColor3f(0.1, 0.1, 0.1);

	glPushMatrix();//������
	glTranslatef(0, -10, 0);
	glScalef(0.5, 1.0, 0.5);
	glRotatef(15, 1, 0, 0);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix();//�ѾƷ��κ�
	glTranslatef(0, 2, +15);
	glScalef(0.25, 0.1, 1.0);
	glutSolidCube(40);
	glPopMatrix();

	glPushMatrix();//�����κ�
	glColor3f(0.3, 0.3, 0.3);
	glTranslatef(0, 8, +15);
	glScalef(0.25, 0.2, 1.0);
	glutSolidCube(40);
	glPopMatrix();

	glPushMatrix();//������
	glColor3f(0.0, 0.8, 0.0);
	glTranslatef(3, 14, 0);
	glutSolidCube(2);
	glTranslatef(-6, 0, 0);
	glutSolidCube(2);
	glPopMatrix();

	if (sight){}
	else{
		glPushMatrix();//���Ƽ�
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0, 14, 35);
		glutSolidCube(1);
		glPopMatrix();
	}

	glPopMatrix();
}

void drawBullet()
{
	if (Head != NULL)
	{
		Temp = Head;
		while (Temp != NULL)
		{
			glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(Temp->x, Temp->y, Temp->z);
			if (FirstPersonView)
				glutSolidSphere(2, 6, 6);
			else
				glutSolidSphere(10, 6, 6);
			glPopMatrix();
			Temp = Temp->next;
		}
	}
}

void crashCheck()
{
	int X = (Charx / 120);
	int Y = (Chary / 120) + 1;
	int Z = (Charz / 120);


	if (Charx < 0)
		X -= 1;
	if (Charz < 0)
		Z -= 1;
	if (Chary < 0)
	{
		Chary = 0;
		gravity = 0;
		jump = false;
	}

	for (int y = Y; y < Y + 2; y++)
	{
		for (int z = Z - 1; z < Z + 2; z++)
		{
			for (int x = X - 1; x < X + 2; x++)
			{
				if (map_DATA[Y - 1][X][Z] == 1)
				{
				}
				if (map_DATA[y][x + 36][z + 13] == 1)
				{
					if ((x == X) && (z == Z))
					{
						if (Charx < x * 120 + 60)
							Charx = x * 120;
						else if (Charx > x * 120 + 60)
							Charx = x * 120 + 120;
						else if (Charz < z * 120 + 60)
							Charz = z * 120;
						else if (Charz > z * 120 + 60)
							Charz = z * 120 + 120;
					}
					else if ((x == X - 1) && (z == Z - 1))
					{
						if ((Charx < ((x * 120) + 120 + crashdist)) && (Charz < ((z * 120) + 120 + crashdist)))
						{
							Charx = ((x * 120) + 120 + crashdist);
							Charz = ((z * 120) + 120 + crashdist);
						}
					}
					else if ((x == X - 1) && (z == Z + 1))
					{
						if ((Charx < ((x * 120) + 120 + crashdist)) && (((z * 120) - crashdist) < Charz))
						{
							Charx = ((x * 120) + 120 + crashdist);
							Charz = ((z * 120) - crashdist);
						}
					}
					else if ((x == X + 1) && (z == Z - 1))
					{
						if ((((x * 120) - crashdist) < Charx) && (Charz < ((z * 120) + 120 + crashdist)))
						{
							Charx = ((x * 120) - crashdist);
							Charz = ((z * 120) + 120 + crashdist);
						}
					}
					else if ((x == X + 1) && (z == Z + 1))
					{
						if ((((x * 120) - crashdist) < Charx) && (((z * 120) - crashdist) < Charz))
						{
							Charx = ((x * 120) - crashdist);
							Charz = ((z * 120) - crashdist);
						}
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
	}//end of y for
}

void bulletCreate()
{
	//printf("1");
	Bullet * New = (Bullet*)malloc(sizeof(Bullet));
	if (FirstPersonView)
	{
		if (sight)
		{
			New->x = Charx + 50 * sin((camyrotate)* 3.141592 / 180) * sin((camxrotate)* 3.141592 / 180);
			New->y = Chary + 50 * cos((camyrotate)* 3.141592 / 180) + 165;
			New->z = Charz + 50 * sin((camyrotate)* 3.141592 / 180) * cos((camxrotate)* 3.141592 / 180);
		}
		else
		{
			New->x = Charx + 30 * sin((camyrotate - 20)* 3.141592 / 180) * sin((camxrotate - 10)* 3.141592 / 180);
			New->y = Chary + 30 * cos((camyrotate - 20)* 3.141592 / 180) + 170;
			New->z = Charz + 30 * sin((camyrotate - 20)* 3.141592 / 180) * cos((camxrotate - 10)* 3.141592 / 180);
		}
	}
	else
	{
		New->x = Charx + 140 * sin((camyrotate - 20)* 3.141592 / 180) * sin((camxrotate - 10)* 3.141592 / 180);
		New->y = Chary + 140 * cos((camyrotate - 20)* 3.141592 / 180) + 170;
		New->z = Charz + 140 * sin((camyrotate - 20)* 3.141592 / 180) * cos((camxrotate - 10)* 3.141592 / 180);
	}
	New->fz = 30 * sin((camyrotate)* 3.141592 / 180) * cos((camxrotate)* 3.141592 / 180);
	New->fx = 30 * sin((camyrotate)* 3.141592 / 180) * sin((camxrotate)* 3.141592 / 180);
	New->fy = 30 * cos((camyrotate)* 3.141592 / 180);
	New->next = NULL;
	//printf("%f, %f, %f\n", New->fx, New->fy, New->fz);
	//printf("Viewx : %f, Viewy : %f, Viewz : %f\n", Viewx, Viewy, Viewz);

	if (Head == NULL)
		Head = New;
	else
	{
		//printf("create\n");
		CTemp = Head;
		while (CTemp != NULL)
		{
			if (CTemp->next != NULL)
				CTemp = CTemp->next;
			else
			{
				CTemp->next = New;
				break;
			}
		}
		//printf("createend\n");
	}
}

void bulletDestroy(Bullet * Del)
{
	DTemp = Head;
	//Bullet * Target;
	//printf("dest\n");
	while (DTemp != NULL)
	{
		if (Head == Del)
		{
			Head = Del->next;
			DTemp = Head;
			free(Del);
			break;
		}
		else if (DTemp->next == Del)
		{
			Del = DTemp->next;
			DTemp->next = Del->next;
			free(Del);
			break;
		}

		else
			DTemp = DTemp->next;
	}
	//printf("destend\n");
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