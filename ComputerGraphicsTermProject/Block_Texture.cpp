#define _CRT_SECURE_NO_WARNINGS
#include "Texture_Load.h"

void block_Texture(int w, int h){
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void nomal_Texture(GLuint object[]){
	glGenTextures(6, object);
	// ����
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	//����
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	//������
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	//��
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Top.bmp", &info);
	block_Texture(256, 256);

	//�Ʒ�
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Bottom.bmp", &info);
	block_Texture(256, 256);

	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ
}

void tree_Texture(GLuint object[]){
	glGenTextures(6, object);
	// ����
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	// �ĸ�
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	//����
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	//������
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	//��
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Top.bmp", &info);
	block_Texture(256, 256);

	//�Ʒ�
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Bottom.bmp", &info);
	block_Texture(256, 256);

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