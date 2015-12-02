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

void drawCharacter();//캐릭터 드로우 함수
void init_Texture();//텍스쳐 로드 함수
void animationCharleg();//캐릭터 다리 애니메이션 함수

int Time = 10;//타이머 갱신시간
char Input;

//캐릭터 및 카메라 관련 변수
float camxrotate = 0, camyrotate = -90, Vewx = 0, Vewy = 0, Vewz = -1000, Charx = 0, Charz = 0, Chary = 0;
float nx = 0, ny = 0, bx = 0, by = 0;
int Charspeed = 5;
bool RotateCam = true, FirstPersonView = true;

//애니메이션 변수
int character_state = 0, timer = 0;//이동 애니메이션 구분용
float head_angle_x;//머리회전
float left_sholder_x, left_sholder_y, right_sholder_x, right_sholder_y, left_elbow_x, right_elbow_x;//팔회전
float left_leg_x, left_leg_y, left_knee_x, right_leg_x, right_leg_y, right_knee_x;//다리회전

void main()
{
	srand((unsigned)time(NULL));

	//윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //디스플레이 모드 설정
	glutInitWindowPosition(500, 0); // 윈도우 위치 지정
	glutInitWindowSize(800, 600); //윈도우 크기 지정
	glutCreateWindow("ComputerGrapgics TermProject"); //윈도우 생성(윈도우 이름)

	//상태 변수 초기화 함수
	glutSetCursor(GLUT_CURSOR_NONE);//마우스커서 없애기
	init_Texture();//텍스쳐 불러오기

	//필요한 콜백 함수 설정
	glutDisplayFunc(DrawScene); //출력 함수의 지정
	glutTimerFunc(Time, TimerFunction, 1);//타이머 콜백 함수
	glutMouseFunc(Mouse);//마우스입력
	//glutMotionFunc(Motion);
	glutPassiveMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);//키보드입력
	glutKeyboardUpFunc(Keyboardup);//키보드 버튼을 뗐을 때
	glutReshapeFunc(Reshape);//다시그리기

	glutMainLoop();//이벤트 루프 실행하기

}

//윈도우 출력 함수
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//바탕색을'black'로지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기

	glLoadIdentity();
	if (FirstPersonView)
		gluLookAt(Charx, Chary+100, Charz, Vewx, Vewy, Vewz, 0.0, 1.0, 0.0);
	else
		gluLookAt(-Vewx/50, -Vewy/50, -Vewz/50, Charx, Chary+ 110, Charz, 0.0, 1.0, 0.0);


	//조명설정
	glEnable(GL_DEPTH_TEST);                              // 가려진 면 제거
	glEnable(GL_CULL_FACE);                               // 후면 제거


	glPushMatrix();//바닥 그리기
	glTranslatef(0, -100, 0);
	glScalef(1, 0.01, 1);
	glutWireCube(2000);
	glPopMatrix();//바닥 그리기 종료

	glPushMatrix();//바닥 그리기
	glColor3f(1, 0, 0);
	glTranslatef(0, 0, -1000);
	glutSolidCube(100);
	glPopMatrix();//바닥 그리기 종료

	glPushMatrix();//바닥 그리기
	glColor3f(0, 0, 1);
	glTranslatef(0, 0, 1000);
	glutSolidCube(100);
	glPopMatrix();//바닥 그리기 종료

	glPushMatrix();//바닥 그리기
	glColor3f(0, 1, 0);
	glTranslatef(1000, 0, 0);
	glutSolidCube(100);
	glPopMatrix();//바닥 그리기 종료

	glPushMatrix();//바닥 그리기
	glColor3f(1, 1, 0);
	glTranslatef(-1000, 0, 0);
	glutSolidCube(100);
	glPopMatrix();//바닥 그리기 종료


	glPushMatrix();//바닥 그리기
	glColor3f(1, 0, 1);
	glTranslatef(0, -1000, 0);
	glutSolidCube(100);
	glPopMatrix();//바닥 그리기 종료

	glPushMatrix();//바닥 그리기
	glColor3f(0, 1, 1);
	glTranslatef(0, 1000, 0);
	glutSolidCube(100);
	glPopMatrix();//바닥 그리기 종료



	glPushMatrix();
	glTranslatef(Charx, Chary, Charz);
	glRotatef(camxrotate, 0, 1, 0);
	drawCharacter();
	glPopMatrix();


	glutSwapBuffers(); //화면에 출력하기
}//end of drawScene

GLvoid Reshape(int w, int h)
{
	//뷰포트 변환 설정
	glViewport(0, 0, w, h);

	//투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//클리핑 공간 설정 : 원근투영
	gluPerspective(60.0f, (float)w / (float)h, 0.1, 5000.0);

	//모델 뷰 행렬 스택 재설정
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
	case 27://ESC키로 종료
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
	animationCharleg();//캐릭터 다리 애니메이션

	glutPostRedisplay();
	glutTimerFunc(Time, TimerFunction, 1);
}//end of TimerFunction

void drawCharacter(){
	glPushMatrix(); //Save 머리
	glTranslated(0, 75, 0);
	glRotatef(-(camyrotate+90)/3, 1, 0, 0);
	glScaled(1.0, 1.0, 0.7);
	drawBoxFront(30, false, character_head_object[0]);
	drawBoxBack(30, false, character_head_object[1]);
	drawBoxLeft(30, false, character_head_object[2]);
	drawBoxRight(30, false, character_head_object[3]);
	drawBoxTop(30, false, character_head_object[4]);
	drawBoxBottom(30, false, character_head_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save 몸통
	glScaled(1.0, 1.5, 0.5);
	drawBoxFront(30, false, character_body_object[0]);
	drawBoxBack(30, false, character_body_object[1]);
	drawBoxLeft(30, false, character_body_object[2]);
	drawBoxRight(30, false, character_body_object[3]);
	drawBoxTop(30, false, character_body_object[4]);
	drawBoxBottom(30, false, character_body_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save 오른팔 어께
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

	glPushMatrix(); //Save 오른팔 팔꿈치
	glTranslated(0, -45, 0);
	glRotatef(right_elbow_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_arm_bottom_object[0]);
	drawBoxBack(30, true, character_arm_bottom_object[1]);
	drawBoxLeft(30, true, character_arm_bottom_object[2]);
	drawBoxRight(30, true, character_arm_bottom_object[3]);
	drawBoxTop(30, true, character_arm_top_object[5]);
	drawBoxBottom(30, true, character_arm_top_object[5]);
	glPopMatrix();//오른팔 팔꿈치 종료

	glPopMatrix();//오른팔 어께 종료


	glPushMatrix(); //Save 왼팔 어께
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

	glPushMatrix(); //Save 왼팔 팔꿈치
	glTranslated(0, -45, 0);
	glRotatef(left_elbow_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_arm_bottom_object[0]);
	drawBoxBack(30, true, character_arm_bottom_object[1]);
	drawBoxLeft(30, true, character_arm_bottom_object[2]);
	drawBoxRight(30, true, character_arm_bottom_object[3]);
	drawBoxTop(30, true, character_arm_top_object[5]);
	drawBoxBottom(30, true, character_arm_top_object[5]);
	glPopMatrix();//왼팔 팔꿈치 종료

	glPopMatrix();//왼팔어께 종료



	glPushMatrix(); //Save 오른쪽 골반
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

	glPushMatrix(); //Save 오른쪽 무릎
	glTranslated(0, -45, 0);
	glRotatef(right_knee_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_leg_bottom_object[0]);
	drawBoxBack(30, true, character_leg_bottom_object[1]);
	drawBoxLeft(30, true, character_leg_bottom_object[2]);
	drawBoxRight(30, true, character_leg_bottom_object[3]);
	drawBoxTop(30, true, character_leg_top_object[4]);
	drawBoxBottom(30, true, character_leg_top_object[5]);
	glPopMatrix();//오른쪽 무릎 종료

	glPopMatrix();//오른쪽 골반 종료


	glPushMatrix(); //Save 왼쪽 골반
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

	glPushMatrix(); //Save 왼쪽 무릎
	glTranslated(0, -45, 0);
	glRotatef(left_knee_x, 1, 0, 0);
	glScaled(0.5, 0.75, 0.5);
	drawBoxFront(30, true, character_leg_bottom_object[0]);
	drawBoxBack(30, true, character_leg_bottom_object[1]);
	drawBoxLeft(30, true, character_leg_bottom_object[2]);
	drawBoxRight(30, true, character_leg_bottom_object[3]);
	drawBoxTop(30, true, character_leg_top_object[4]);
	drawBoxBottom(30, true, character_leg_top_object[5]);
	glPopMatrix(); //왼쪽 무릎 종료

	glPopMatrix(); //왼쪽골반 종료
}

void animationCharleg()
{
	switch (character_state){
	case 0://가만히 서있을때
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
	case 1://전진,후진
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
	case 2://좌우이동
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