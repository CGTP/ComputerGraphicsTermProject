#include "Texture_Load.h"

void nomal_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0,  "ImageData/Block/Nomal/Around.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Block/Nomal/Around.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Block/Nomal/Around.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Block/Nomal/Around.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Block/Nomal/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Block/Nomal/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void tree_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Block/Tree/Around.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Block/Tree/Around.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Block/Tree/Around.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Block/Tree/Around.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Block/Tree/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Block/Tree/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void brick_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Block/Brick/Around.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Block/Brick/Around.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Block/Brick/Around.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Block/Brick/Around.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Block/Brick/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Block/Brick/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void wooden_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Block/Wooden/Around.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Block/Wooden/Around.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Block/Wooden/Around.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Block/Wooden/Around.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Block/Wooden/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Block/Wooden/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void stone_Texture(GLuint object[]){
	// ����
	Load_TextureBMP(object, 0, "ImageData/Block/Stone/Around.bmp");

	// �ĸ�
	Load_TextureBMP(object, 1, "ImageData/Block/Stone/Around.bmp");

	//����
	Load_TextureBMP(object, 2, "ImageData/Block/Stone/Around.bmp");

	//������
	Load_TextureBMP(object, 3, "ImageData/Block/Stone/Around.bmp");

	//��
	Load_TextureBMP(object, 4, "ImageData/Block/Stone/Top.bmp");

	//�Ʒ�
	Load_TextureBMP(object, 5, "ImageData/Block/Stone/Bottom.bmp");

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}