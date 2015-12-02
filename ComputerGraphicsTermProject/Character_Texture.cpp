#include "Texture_Load.h"

void character_Texture(int w, int h){
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void head_Texture(GLuint object[]){
	glGenTextures(6, object);

	// ����
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Steave/Head/Front.bmp", &info);
	character_Texture(16, 16);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Steave/Head/Back.bmp", &info);
	character_Texture(16, 16);

	//����
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Steave/Head/Left.bmp", &info);
	character_Texture(16, 16);

	//������
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Steave/Head/Right.bmp", &info);
	character_Texture(16, 16);

	//��
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Steave/Head/Top.bmp", &info);
	character_Texture(16, 16);

	//�Ʒ�
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Steave/Head/Bottom.bmp", &info);
	character_Texture(16, 16);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void body_Texture(GLuint object[]){
	glGenTextures(6, object);

	// ����
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Steave/Body/Front.bmp", &info);
	character_Texture(16, 24);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Steave/Body/Back.bmp", &info);
	character_Texture(16, 24);

	// ����
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Steave/Body/Left.bmp", &info);
	character_Texture(8, 24);

	// ������
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Steave/Body/Right.bmp", &info);
	character_Texture(8, 24);

	// ��
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Steave/Body/Top.bmp", &info);
	character_Texture(16, 8);

	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Steave/Body/Bottom.bmp", &info);
	character_Texture(16, 8);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void arm_Texture(GLuint object[], GLuint object2[]){
	glGenTextures(6, object);
	glGenTextures(6, object2);

	// ����
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Front_Top.bmp", &info);
	character_Texture(8, 12);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Back_Top.bmp", &info);
	character_Texture(8, 12);

	// ����
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Left_Top.bmp", &info);
	character_Texture(8, 12);

	// ������
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Right_Top.bmp", &info);
	character_Texture(8, 12);

	// ��
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Top.bmp", &info);
	character_Texture(8, 8);

	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Bottom.bmp", &info);
	character_Texture(8, 8);

	// ����
	glBindTexture(GL_TEXTURE_2D, object2[0]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Front_Bottom.bmp", &info);
	character_Texture(8, 12);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object2[1]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Back_Bottom.bmp", &info);
	character_Texture(8, 12);

	// ����
	glBindTexture(GL_TEXTURE_2D, object2[2]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Left_Bottom.bmp", &info);
	character_Texture(8, 12);

	// ������
	glBindTexture(GL_TEXTURE_2D, object2[3]);
	pBytes = LoadDIBitmap("ImageData/Steave/Arm/Right_Bottom.bmp", &info);
	character_Texture(8, 12);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void leg_Texture(GLuint object[], GLuint object2[]){
	glGenTextures(6, object);
	glGenTextures(6, object2);
	// ����
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Front_Top.bmp", &info);
	character_Texture(8, 12);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Back_Top.bmp", &info);
	character_Texture(8, 12);

	// ����
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Left_Top.bmp", &info);
	character_Texture(8, 12);

	// ������
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Right_Top.bmp", &info);
	character_Texture(8, 12);

	// ��
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Top.bmp", &info);
	character_Texture(8, 8);

	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Bottom.bmp", &info);
	character_Texture(8, 8);


	// ����
	glBindTexture(GL_TEXTURE_2D, object2[0]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Front_Bottom.bmp", &info);
	character_Texture(8, 12);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object2[1]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Back_Bottom.bmp", &info);
	character_Texture(8, 12);

	// ����
	glBindTexture(GL_TEXTURE_2D, object2[2]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Left_Bottom.bmp", &info);
	character_Texture(8, 12);

	// ������
	glBindTexture(GL_TEXTURE_2D, object2[3]);
	pBytes = LoadDIBitmap("ImageData/Steave/Leg/Right_Bottom.bmp", &info);
	character_Texture(8, 12);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}
