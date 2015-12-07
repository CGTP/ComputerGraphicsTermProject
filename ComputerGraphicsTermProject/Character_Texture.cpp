#include "Texture_Load.h"

void head_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Steave/Head/Front.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Steave/Head/Back.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Steave/Head/Left.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Steave/Head/Right.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Steave/Head/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Steave/Head/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void body_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Steave/Body/Front.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Steave/Body/Back.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Steave/Body/Left.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Steave/Body/Right.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Steave/Body/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Steave/Body/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void arm_Texture(GLuint object[], GLuint object2[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Steave/Arm/Front_Top.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Steave/Arm/Back_Top.bmp");

	// ����
	Load_TextureBMP(object, 2, "ImageData/Steave/Arm/Left_Top.bmp");

	// ������
	Load_TextureBMP(object, 3, "ImageData/Steave/Arm/Right_Top.bmp");

	// ��
	Load_TextureBMP(object, 4, "ImageData/Steave/Arm/Top.bmp");

	// �Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Steave/Arm/Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 0, "ImageData/Steave/Arm/Front_Bottom.bmp");

	// �ĸ�
	Load_TextureBMP(object2, 1, "ImageData/Steave/Arm/Back_Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 2, "ImageData/Steave/Arm/Left_Bottom.bmp");

	// ������
	Load_TextureBMP(object2, 3, "ImageData/Steave/Arm/Right_Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void leg_Texture(GLuint object[], GLuint object2[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Steave/Leg/Front_Top.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Steave/Leg/Back_Top.bmp");

	// ����
	Load_TextureBMP(object, 2, "ImageData/Steave/Leg/Left_Top.bmp");

	// ������
	Load_TextureBMP(object, 3, "ImageData/Steave/Leg/Right_Top.bmp");

	// ��
	Load_TextureBMP(object, 4, "ImageData/Steave/Leg/Top.bmp");

	// �Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Steave/Leg/Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 0, "ImageData/Steave/Leg/Front_Bottom.bmp");

	// �ĸ�
	Load_TextureBMP(object2, 1, "ImageData/Steave/Leg/Back_Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 2, "ImageData/Steave/Leg/Left_Bottom.bmp");

	// ������
	Load_TextureBMP(object2, 3, "ImageData/Steave/Leg/Right_Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}
