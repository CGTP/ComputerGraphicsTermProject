#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);


void drawBoxFront(int );
void drawBoxBack(int);

void drawBoxTop(int);
void drawBoxBottom(int);

void drawBoxRight(int);
void drawBoxLeft(int);

void vLine();

float fMapZ = 0.0;
float vMapX = 0.0;
float fView = 0.0;
float vMapY = 0.0;


void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'Black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 설정된 색으로 젂체를 칠하기
	glEnable(GL_DEPTH_TEST);

	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	glRotated(vMapY, 0, 1.0, 0);
	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);

	glPushMatrix(); //Save
	vLine();
	glPopMatrix();

	
	drawBoxFront(50);
	drawBoxBack(50);
	drawBoxRight(50);
	drawBoxLeft(50);
	drawBoxTop(50);
	drawBoxBottom(50);

	glPopMatrix();
	//glFlush(); // 화면에 출력하기
	glutSwapBuffers();     // 화면에 출력하기
}

void TimerFunction(int value){
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == 'r'){
		vMapY += 3.0;
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
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	//뷰포트 변환 설정
	glViewport(0, 0, w, h);

	//투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//클리핑 공간 설정 : 원근투영
	gluPerspective(60.0f, (float)w / (float)h, 0.1, 5000.0);

	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);

	//모델 뷰 행렬 스택 재설정
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


void drawBoxFront(int size){
	glPushMatrix(); //Save
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-size, size, size);   //1
	glVertex3f(-size, -size, size);   //2
	glVertex3f(size, -size, size);   //3
	glVertex3f(size, size, size);   //4
	glEnd();
	glPopMatrix();
}

void drawBoxBack(int size){
	glPushMatrix(); //Save
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(-size, size, -size);   //5
	glVertex3f(size, size, -size);   //6
	glVertex3f(size, -size, -size);   //7
	glVertex3f(-size, -size, -size);   //8
	glEnd();
	glPopMatrix();
}

void drawBoxRight(int size){
	glPushMatrix(); //Save
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(size, size, size);   //4
	glVertex3f(size, -size, size);   //3   
	glVertex3f(size, -size, -size);   //7
	glVertex3f(size, size, -size);   //6
	glEnd();
	glPopMatrix();

}

void drawBoxLeft(int size){
	glPushMatrix(); //Save
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-size, size, size);   //1
	glVertex3f(-size, size, -size);   //5
	glVertex3f(-size, -size, -size);   //8   
	glVertex3f(-size, -size, size);   //2
	glEnd();
	glPopMatrix();

}

void drawBoxTop(int size){
	glPushMatrix(); //Save
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-size, size, size);  //1
	glVertex3f(size, size, size);   //4
	glVertex3f(size, size, -size);   //6
	glVertex3f(-size, size, -size);   //5
	glEnd();
	glPopMatrix();
}

void drawBoxBottom(int size){
	glPushMatrix(); //Save
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-size, -size, size);   //2
	glVertex3f(-size, -size, -size);   //8
	glVertex3f(size, -size, -size);   //7
	glVertex3f(size, -size, size);   //3
	glEnd();
	glPopMatrix();
}