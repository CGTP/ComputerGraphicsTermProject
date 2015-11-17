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

	//윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //디스플레이 모드 설정
	glutInitWindowPosition(500, 0); // 윈도우 위치 지정
	glutInitWindowSize(800, 600); //윈도우 크기 지정
	glutCreateWindow("CGExample1"); //윈도우 생성(윈도우 이름)

	//상태 변수 초기화 함수
	glutSetCursor(GLUT_CURSOR_NONE);//마우스커서 없애기

	//필요한 콜백 함수 설정
	glutDisplayFunc(DrawScene); //출력 함수의 지정
	glutTimerFunc(Time, TimerFunction, 1);//타이머 콜백 함수
	glutMouseFunc(Mouse);//마우스입력
	//glutMotionFunc(Motion);
	glutPassiveMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);//키보드입력
	glutReshapeFunc(Reshape);//다시그리기

	glutMainLoop();//이벤트 루프 실행하기

}

//윈도우 출력 함수
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//바탕색을'black'로지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 전체를 칠하기

	glLoadIdentity();
	gluLookAt(Charx, 0.0, Charz, Vewx, Vewy, Vewz, 0.0, 1.0, 0.0);



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
	case 27://ESC키로 종료
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
