#include "Texture_Load.h"

void zombie_head_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Zombie/Head/Front.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Zombie/Head/Back.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Zombie/Head/Left.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Zombie/Head/Right.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Zombie/Head/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Zombie/Head/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void zombie_body_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Zombie/Body/Front.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Zombie/Body/Back.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Zombie/Body/Left.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Zombie/Body/Right.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Zombie/Body/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Zombie/Body/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void zombie_arm_Texture(GLuint object[], GLuint object2[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Zombie/Arm/Front_Top.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Zombie/Arm/Back_Top.bmp");

	// ����
	Load_TextureBMP(object, 2, "ImageData/Zombie/Arm/Left_Top.bmp");

	// ������
	Load_TextureBMP(object, 3, "ImageData/Zombie/Arm/Right_Top.bmp");

	// ��
	Load_TextureBMP(object, 4, "ImageData/Zombie/Arm/Top.bmp");

	// �Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Zombie/Arm/Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 0, "ImageData/Zombie/Arm/Front_Bottom.bmp");

	// �ĸ�
	Load_TextureBMP(object2, 1, "ImageData/Zombie/Arm/Back_Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 2, "ImageData/Zombie/Arm/Left_Bottom.bmp");

	// ������
	Load_TextureBMP(object2, 3, "ImageData/Zombie/Arm/Right_Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void zombie_leg_Texture(GLuint object[], GLuint object2[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Zombie/Leg/Front_Top.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Zombie/Leg/Back_Top.bmp");

	// ����
	Load_TextureBMP(object, 2, "ImageData/Zombie/Leg/Left_Top.bmp");

	// ������
	Load_TextureBMP(object, 3, "ImageData/Zombie/Leg/Right_Top.bmp");

	// ��
	Load_TextureBMP(object, 4, "ImageData/Zombie/Leg/Top.bmp");

	// �Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Zombie/Leg/Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 0, "ImageData/Zombie/Leg/Front_Bottom.bmp");

	// �ĸ�
	Load_TextureBMP(object2, 1, "ImageData/Zombie/Leg/Back_Bottom.bmp");

	// ����
	Load_TextureBMP(object2, 2, "ImageData/Zombie/Leg/Left_Bottom.bmp");

	// ������
	Load_TextureBMP(object2, 3, "ImageData/Zombie/Leg/Right_Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}
