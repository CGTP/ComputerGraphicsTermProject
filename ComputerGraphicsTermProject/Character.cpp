#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint character_head_object[6];
GLuint character_body_object[6];
GLuint character_arm_object[6];
GLuint character_leg_object[6];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);


void drawBoxFront(int, bool, GLuint);
void drawBoxBack(int, bool, GLuint);
void drawBoxTop(int, bool, GLuint);
void drawBoxBottom(int, bool, GLuint);
void drawBoxRight(int, bool, GLuint);
void drawBoxLeft(int, bool, GLuint);

void head_Texture();
void body_Texture();
void arm_Texture();
void leg_Texture();
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
	head_Texture();
	body_Texture();
	arm_Texture();
	leg_Texture();
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
	//vLine();
	glPopMatrix();


	glPushMatrix(); //Save
	glTranslated(0, 75, 0);
	glScaled(1.0, 1.0, 0.7);
	drawBoxFront(30, false, character_head_object[0]);
	drawBoxBack(30, false, character_head_object[1]);
	drawBoxLeft(30, false, character_head_object[2]);
	drawBoxRight(30, false, character_head_object[3]);
	drawBoxTop(30, false, character_head_object[4]);
	drawBoxBottom(30, false, character_head_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save
	glScaled(1.0, 1.5, 0.5);
	drawBoxFront(30, false, character_body_object[0]);
	drawBoxBack(30, false, character_body_object[1]);
	drawBoxLeft(30, false, character_body_object[2]);
	drawBoxRight(30, false, character_body_object[3]);
	drawBoxTop(30, false, character_body_object[4]);
	drawBoxBottom(30, false, character_body_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save right arm
	glTranslated(-45, 44, 0);
	glRotatef(30, 1, 0, 0);
	glScaled(0.5, 1.5, 0.5);
	drawBoxFront(30, true, character_arm_object[0]);
	drawBoxBack(30, true, character_arm_object[1]);
	drawBoxLeft(30, true, character_arm_object[2]);
	drawBoxRight(30, true, character_arm_object[3]);
	drawBoxTop(30, true, character_arm_object[4]);
	drawBoxBottom(30, true, character_arm_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save left arm
	glTranslated(45, 44, 0);
	glRotatef(-30, 1, 0, 0);
	glScaled(0.5, 1.5, 0.5);
	drawBoxFront(30, true, character_arm_object[0]);
	drawBoxBack(30, true, character_arm_object[1]);
	drawBoxLeft(30, true, character_arm_object[2]);
	drawBoxRight(30, true, character_arm_object[3]);
	drawBoxTop(30, true, character_arm_object[4]);
	drawBoxBottom(30, true, character_arm_object[5]);
	glPopMatrix();


	glPushMatrix(); //Save right leg
	glTranslated(-15, -40, 0);
	glRotatef(-30, 1, 0, 0);
	glScaled(0.5, 1.5, 0.5);
	drawBoxFront(30, true, character_leg_object[0]);
	drawBoxBack(30, true, character_leg_object[1]);
	drawBoxLeft(30, true, character_leg_object[2]);
	drawBoxRight(30, true, character_leg_object[3]);
	drawBoxTop(30, true, character_leg_object[4]);
	drawBoxBottom(30, true, character_leg_object[5]);
	glPopMatrix();

	glPushMatrix(); //Save right leg
	glTranslated(15, -40, 0);
	glRotatef(30, 1, 0, 0);
	glScaled(0.5, 1.5, 0.5);
	drawBoxFront(30, true, character_leg_object[0]);
	drawBoxBack(30, true, character_leg_object[1]);
	drawBoxLeft(30, true, character_leg_object[2]);
	drawBoxRight(30, true, character_leg_object[3]);
	drawBoxTop(30, true, character_leg_object[4]);
	drawBoxBottom(30, true, character_leg_object[5]);
	glPopMatrix();


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


void drawBoxFront(int size, bool shaft, GLuint image){
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	if (shaft == true){
		//인호's 샘플코드
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, 0, size);   //1
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -(size * 2), size);   //2
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -(size * 2), size);   //3
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, 0, size);   //4
	}
	else{
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, size, size);   //1
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -size, size);   //2
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -size, size);   //3
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, size, size);   //4
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawBoxBack(int size, bool shaft, GLuint image){
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	if (shaft == true){
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, 0, -size);   //5
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, 0, -size);   //6
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -(size * 2), -size);   //7
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -(size * 2), -size);   //8
	}
	else{
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, size, -size);   //5
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, size, -size);   //6
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -size, -size);   //7
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -size, -size);   //8
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawBoxLeft(int size, bool shaft, GLuint image){
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	if (shaft == true){
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(-size, 0, size);   //1
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, 0, -size);   //5
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -(size * 2), -size);   //8   
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(-size, -(size * 2), size);   //2
	}
	else{
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(-size, size, size);   //1
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, size, -size);   //5
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -size, -size);   //8   
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(-size, -size, size);   //2
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void drawBoxRight(int size, bool shaft, GLuint image){
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	if (shaft == true){
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(size, 0, size);   //4
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(size, -(size * 2), size);   //3   
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -(size * 2), -size);   //7
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, 0, -size);   //6
	}
	else{
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(size, size, size);   //4
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(size, -size, size);   //3   
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -size, -size);   //7
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, size, -size);   //6
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void drawBoxTop(int size, bool shaft, GLuint image){
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	if (shaft == true){
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(-size, 0, size);  //1
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(size, 0, size);   //4
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(size, 0, -size);   //6
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(-size, 0, -size);   //5
	}
	else{
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(-size, size, size);  //1
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(size, size, size);   //4
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(size, size, -size);   //6
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(-size, size, -size);   //5
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawBoxBottom(int size, bool shaft, GLuint image){
	glPushMatrix(); //Save
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	if (shaft == true){
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, -(size * 2), size);   //2
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -(size * 2), -size);   //8
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -(size * 2), -size);   //7
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, -(size * 2), size);   //3
	}
	else{
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(-size, -size, size);   //2
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(-size, -size, -size);   //8
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(size, -size, -size);   //7
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(size, -size, size);   //3
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}



void head_Texture(){
	glGenTextures(6, character_head_object);

	// 정면
	glBindTexture(GL_TEXTURE_2D, character_head_object[0]);
	pBytes = LoadDIBitmap("ImageData/Head/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_head_object[1]);
	pBytes = LoadDIBitmap("ImageData/Head/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//왼쪽
	glBindTexture(GL_TEXTURE_2D, character_head_object[2]);
	pBytes = LoadDIBitmap("ImageData/Head/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//오른쪽
	glBindTexture(GL_TEXTURE_2D, character_head_object[3]);
	pBytes = LoadDIBitmap("ImageData/Head/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//위
	glBindTexture(GL_TEXTURE_2D, character_head_object[4]);
	pBytes = LoadDIBitmap("ImageData/Head/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//아래
	glBindTexture(GL_TEXTURE_2D, character_head_object[5]);
	pBytes = LoadDIBitmap("ImageData/Head/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void body_Texture(){
	glGenTextures(6, character_body_object);

	// 정면
	glBindTexture(GL_TEXTURE_2D, character_body_object[0]);
	pBytes = LoadDIBitmap("ImageData/Body/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_body_object[1]);
	pBytes = LoadDIBitmap("ImageData/Body/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_body_object[2]);
	pBytes = LoadDIBitmap("ImageData/Body/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_body_object[3]);
	pBytes = LoadDIBitmap("ImageData/Body/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 위
	glBindTexture(GL_TEXTURE_2D, character_body_object[4]);
	pBytes = LoadDIBitmap("ImageData/Body/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 아래
	glBindTexture(GL_TEXTURE_2D, character_body_object[5]);
	pBytes = LoadDIBitmap("ImageData/Body/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void arm_Texture(){
	glGenTextures(6, character_arm_object);
	// 정면
	glBindTexture(GL_TEXTURE_2D, character_arm_object[0]);
	pBytes = LoadDIBitmap("ImageData/Arm/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_arm_object[1]);
	pBytes = LoadDIBitmap("ImageData/Arm/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_arm_object[2]);
	pBytes = LoadDIBitmap("ImageData/Arm/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_arm_object[3]);
	pBytes = LoadDIBitmap("ImageData/Arm/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 위
	glBindTexture(GL_TEXTURE_2D, character_arm_object[4]);
	pBytes = LoadDIBitmap("ImageData/Arm/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 아래
	glBindTexture(GL_TEXTURE_2D, character_arm_object[5]);
	pBytes = LoadDIBitmap("ImageData/Arm/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void leg_Texture(){
	glGenTextures(6, character_leg_object);
	// 정면
	glBindTexture(GL_TEXTURE_2D, character_leg_object[0]);
	pBytes = LoadDIBitmap("ImageData/Leg/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_leg_object[1]);
	pBytes = LoadDIBitmap("ImageData/Leg/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_leg_object[2]);
	pBytes = LoadDIBitmap("ImageData/Leg/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_leg_object[3]);
	pBytes = LoadDIBitmap("ImageData/Leg/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 위
	glBindTexture(GL_TEXTURE_2D, character_leg_object[4]);
	pBytes = LoadDIBitmap("ImageData/Leg/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 아래
	glBindTexture(GL_TEXTURE_2D, character_leg_object[5]);
	pBytes = LoadDIBitmap("ImageData/Leg/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}























GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info){
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인핚다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 갂다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 핛당을 핚다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 핛당핚다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장핚다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}