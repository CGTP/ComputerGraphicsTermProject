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
	// 정면
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	//왼쪽
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	//오른쪽
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Around.bmp", &info);
	block_Texture(256, 256);

	//위
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Top.bmp", &info);
	block_Texture(256, 256);

	//아래
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Block/Nomal/Bottom.bmp", &info);
	block_Texture(256, 256);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void tree_Texture(GLuint object[]){
	glGenTextures(6, object);
	// 정면
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	//왼쪽
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	//오른쪽
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Around.bmp", &info);
	block_Texture(256, 256);

	//위
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Top.bmp", &info);
	block_Texture(256, 256);

	//아래
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Block/Tree/Bottom.bmp", &info);
	block_Texture(256, 256);

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