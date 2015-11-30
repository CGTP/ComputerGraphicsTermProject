#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
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
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
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

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�
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
	//glFlush(); // ȭ�鿡 ����ϱ�
	glutSwapBuffers();     // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value){

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
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
	//����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);

	//���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Ŭ���� ���� ���� : ��������
	gluPerspective(60.0f, (float)w / (float)h, 0.1, 5000.0);

	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);

	//�� �� ��� ���� �缳��
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
		//��ȣ's �����ڵ�
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

	// ����
	glBindTexture(GL_TEXTURE_2D, character_head_object[0]);
	pBytes = LoadDIBitmap("ImageData/Head/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, character_head_object[1]);
	pBytes = LoadDIBitmap("ImageData/Head/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//����
	glBindTexture(GL_TEXTURE_2D, character_head_object[2]);
	pBytes = LoadDIBitmap("ImageData/Head/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//������
	glBindTexture(GL_TEXTURE_2D, character_head_object[3]);
	pBytes = LoadDIBitmap("ImageData/Head/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//��
	glBindTexture(GL_TEXTURE_2D, character_head_object[4]);
	pBytes = LoadDIBitmap("ImageData/Head/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//�Ʒ�
	glBindTexture(GL_TEXTURE_2D, character_head_object[5]);
	pBytes = LoadDIBitmap("ImageData/Head/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 16, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void body_Texture(){
	glGenTextures(6, character_body_object);

	// ����
	glBindTexture(GL_TEXTURE_2D, character_body_object[0]);
	pBytes = LoadDIBitmap("ImageData/Body/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, character_body_object[1]);
	pBytes = LoadDIBitmap("ImageData/Body/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ����
	glBindTexture(GL_TEXTURE_2D, character_body_object[2]);
	pBytes = LoadDIBitmap("ImageData/Body/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ������
	glBindTexture(GL_TEXTURE_2D, character_body_object[3]);
	pBytes = LoadDIBitmap("ImageData/Body/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ��
	glBindTexture(GL_TEXTURE_2D, character_body_object[4]);
	pBytes = LoadDIBitmap("ImageData/Body/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, character_body_object[5]);
	pBytes = LoadDIBitmap("ImageData/Body/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 16, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void arm_Texture(){
	glGenTextures(6, character_arm_object);
	// ����
	glBindTexture(GL_TEXTURE_2D, character_arm_object[0]);
	pBytes = LoadDIBitmap("ImageData/Arm/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, character_arm_object[1]);
	pBytes = LoadDIBitmap("ImageData/Arm/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ����
	glBindTexture(GL_TEXTURE_2D, character_arm_object[2]);
	pBytes = LoadDIBitmap("ImageData/Arm/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ������
	glBindTexture(GL_TEXTURE_2D, character_arm_object[3]);
	pBytes = LoadDIBitmap("ImageData/Arm/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ��
	glBindTexture(GL_TEXTURE_2D, character_arm_object[4]);
	pBytes = LoadDIBitmap("ImageData/Arm/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, character_arm_object[5]);
	pBytes = LoadDIBitmap("ImageData/Arm/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void leg_Texture(){
	glGenTextures(6, character_leg_object);
	// ����
	glBindTexture(GL_TEXTURE_2D, character_leg_object[0]);
	pBytes = LoadDIBitmap("ImageData/Leg/Front.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, character_leg_object[1]);
	pBytes = LoadDIBitmap("ImageData/Leg/Back.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ����
	glBindTexture(GL_TEXTURE_2D, character_leg_object[2]);
	pBytes = LoadDIBitmap("ImageData/Leg/Left.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ������
	glBindTexture(GL_TEXTURE_2D, character_leg_object[3]);
	pBytes = LoadDIBitmap("ImageData/Leg/Right.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 24, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ��
	glBindTexture(GL_TEXTURE_2D, character_leg_object[4]);
	pBytes = LoadDIBitmap("ImageData/Leg/Top.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, character_leg_object[5]);
	pBytes = LoadDIBitmap("ImageData/Leg/Bottom.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 8, 8, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}























GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info){
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ������.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� ������ ����.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� ��������.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� ��������.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}