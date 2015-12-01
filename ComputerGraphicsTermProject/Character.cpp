#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//텍스쳐 관련 시작
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint character_head_object[6];
GLuint character_body_object[6];
GLuint character_arm_top_object[6];
GLuint character_arm_bottom_object[6];
GLuint character_leg_top_object[6];
GLuint character_leg_bottom_object[6];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

void head_Texture();//텍스쳐 적용부분
void body_Texture();
void arm_Texture();
void leg_Texture();
void parameteri_Texture(int, int);
//텍스쳐 관련 끝


//함수선언 시작
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);

void drawBoxFront(int, bool, GLuint);//박스 그리는 함수
void drawBoxBack(int, bool, GLuint);
void drawBoxTop(int, bool, GLuint);
void drawBoxBottom(int, bool, GLuint);
void drawBoxRight(int, bool, GLuint);
void drawBoxLeft(int, bool, GLuint);

void vLine();//좌표계 그리는 함수

void drawCharacter();
//함수선언 끝


//변수선언 시작
#define oneTimerSpeed 10
float fMapZ = 0.0;//화면회전관련 변수
float vMapX = 0.0;
float fView = 0.0;
float vMapY = 0.0;

//애니메이션 변수
int character_state = 1;//이동 애니메이션 구분용
float head_angle_x;//머리회전
float left_sholder_x, left_sholder_y, right_sholder_x, right_sholder_y, left_elbow_x, right_elbow_x;//팔회전
float left_leg_x, left_leg_y, left_knee_x, right_leg_x, right_leg_y, right_knee_x;//다리회전
int timer = 0;

//변수선언 끝


void main(int argc, char *argv[]){
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("WindowsHyun - 2012180004"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutTimerFunc(oneTimerSpeed, TimerFunction, 1);
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

	drawCharacter();
	


	glPopMatrix();
	//glFlush(); // 화면에 출력하기
	glutSwapBuffers();     // 화면에 출력하기
}

void TimerFunction(int value){

	switch (value){
	case 1:
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
			printf("%d\n", timer);
			if (timer < 150)
			{
				timer++;
				if (timer < 75)
				{
					left_leg_x = timer - 45;
					right_leg_x = 30 - timer;
					//right_knee_x = timer;
				}
				else
				{
					left_leg_x = 105 - timer;
					right_leg_x = timer - 120;
					//left_knee_x = (timer / 2);
				}
			}
			else
				timer = 0;
			break;
		case 2://좌우이동
			break;
		}
		glutTimerFunc(oneTimerSpeed, TimerFunction, 1); // 타이머함수 재 설정
		break;
	}

	glutPostRedisplay(); // 화면 재 출력
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

void parameteri_Texture(int w, int h){
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void head_Texture(){
	glGenTextures(6, character_head_object);

	// 정면
	glBindTexture(GL_TEXTURE_2D, character_head_object[0]);
	pBytes = LoadDIBitmap("ImageData/Head/Front.bmp", &info);
	parameteri_Texture(16, 16);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_head_object[1]);
	pBytes = LoadDIBitmap("ImageData/Head/Back.bmp", &info);
	parameteri_Texture(16, 16);

	//왼쪽
	glBindTexture(GL_TEXTURE_2D, character_head_object[2]);
	pBytes = LoadDIBitmap("ImageData/Head/Left.bmp", &info);
	parameteri_Texture(16, 16);

	//오른쪽
	glBindTexture(GL_TEXTURE_2D, character_head_object[3]);
	pBytes = LoadDIBitmap("ImageData/Head/Right.bmp", &info);
	parameteri_Texture(16, 16);

	//위
	glBindTexture(GL_TEXTURE_2D, character_head_object[4]);
	pBytes = LoadDIBitmap("ImageData/Head/Top.bmp", &info);
	parameteri_Texture(16, 16);

	//아래
	glBindTexture(GL_TEXTURE_2D, character_head_object[5]);
	pBytes = LoadDIBitmap("ImageData/Head/Bottom.bmp", &info);
	parameteri_Texture(16, 16);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void body_Texture(){
	glGenTextures(6, character_body_object);

	// 정면
	glBindTexture(GL_TEXTURE_2D, character_body_object[0]);
	pBytes = LoadDIBitmap("ImageData/Body/Front.bmp", &info);
	parameteri_Texture(16, 24);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_body_object[1]);
	pBytes = LoadDIBitmap("ImageData/Body/Back.bmp", &info);
	parameteri_Texture(16, 24);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_body_object[2]);
	pBytes = LoadDIBitmap("ImageData/Body/Left.bmp", &info);
	parameteri_Texture(8, 24);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_body_object[3]);
	pBytes = LoadDIBitmap("ImageData/Body/Right.bmp", &info);
	parameteri_Texture(8, 24);

	// 위
	glBindTexture(GL_TEXTURE_2D, character_body_object[4]);
	pBytes = LoadDIBitmap("ImageData/Body/Top.bmp", &info);
	parameteri_Texture(16, 8);

	// 아래
	glBindTexture(GL_TEXTURE_2D, character_body_object[5]);
	pBytes = LoadDIBitmap("ImageData/Body/Bottom.bmp", &info);
	parameteri_Texture(16, 8);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void arm_Texture(){
	glGenTextures(6, character_arm_top_object);
	glGenTextures(6, character_arm_bottom_object);

	// 정면
	glBindTexture(GL_TEXTURE_2D, character_arm_top_object[0]);
	pBytes = LoadDIBitmap("ImageData/Arm/Front_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_arm_top_object[1]);
	pBytes = LoadDIBitmap("ImageData/Arm/Back_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_arm_top_object[2]);
	pBytes = LoadDIBitmap("ImageData/Arm/Left_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_arm_top_object[3]);
	pBytes = LoadDIBitmap("ImageData/Arm/Right_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 위
	glBindTexture(GL_TEXTURE_2D, character_arm_top_object[4]);
	pBytes = LoadDIBitmap("ImageData/Arm/Top.bmp", &info);
	parameteri_Texture(8, 8);

	// 아래
	glBindTexture(GL_TEXTURE_2D, character_arm_top_object[5]);
	pBytes = LoadDIBitmap("ImageData/Arm/Bottom.bmp", &info);
	parameteri_Texture(8, 8);

	// 정면
	glBindTexture(GL_TEXTURE_2D, character_arm_bottom_object[0]);
	pBytes = LoadDIBitmap("ImageData/Arm/Front_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_arm_bottom_object[1]);
	pBytes = LoadDIBitmap("ImageData/Arm/Back_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_arm_bottom_object[2]);
	pBytes = LoadDIBitmap("ImageData/Arm/Left_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_arm_bottom_object[3]);
	pBytes = LoadDIBitmap("ImageData/Arm/Right_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void leg_Texture(){
	glGenTextures(6, character_leg_top_object);
	glGenTextures(6, character_leg_bottom_object);
	// 정면
	glBindTexture(GL_TEXTURE_2D, character_leg_top_object[0]);
	pBytes = LoadDIBitmap("ImageData/Leg/Front_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_leg_top_object[1]);
	pBytes = LoadDIBitmap("ImageData/Leg/Back_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_leg_top_object[2]);
	pBytes = LoadDIBitmap("ImageData/Leg/Left_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_leg_top_object[3]);
	pBytes = LoadDIBitmap("ImageData/Leg/Right_Top.bmp", &info);
	parameteri_Texture(8, 12);

	// 위
	glBindTexture(GL_TEXTURE_2D, character_leg_top_object[4]);
	pBytes = LoadDIBitmap("ImageData/Leg/Top.bmp", &info);
	parameteri_Texture(8, 8);

	// 아래
	glBindTexture(GL_TEXTURE_2D, character_leg_top_object[5]);
	pBytes = LoadDIBitmap("ImageData/Leg/Bottom.bmp", &info);
	parameteri_Texture(8, 8);


	// 정면
	glBindTexture(GL_TEXTURE_2D, character_leg_bottom_object[0]);
	pBytes = LoadDIBitmap("ImageData/Leg/Front_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, character_leg_bottom_object[1]);
	pBytes = LoadDIBitmap("ImageData/Leg/Back_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, character_leg_bottom_object[2]);
	pBytes = LoadDIBitmap("ImageData/Leg/Left_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, character_leg_bottom_object[3]);
	pBytes = LoadDIBitmap("ImageData/Leg/Right_Bottom.bmp", &info);
	parameteri_Texture(8, 12);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}


void drawCharacter(){
	glPushMatrix(); //Save 머리
	glTranslated(0, 75, 0);
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
	drawBoxTop(30, true, character_arm_top_object[4]);
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
	drawBoxTop(30, true, character_arm_top_object[4]);
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