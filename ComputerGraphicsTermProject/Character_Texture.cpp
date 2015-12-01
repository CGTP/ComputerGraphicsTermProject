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

	// 정면
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Head/Front.bmp", &info);
	character_Texture(16, 16);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Head/Back.bmp", &info);
	character_Texture(16, 16);

	//왼쪽
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Head/Left.bmp", &info);
	character_Texture(16, 16);

	//오른쪽
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Head/Right.bmp", &info);
	character_Texture(16, 16);

	//위
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Head/Top.bmp", &info);
	character_Texture(16, 16);

	//아래
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Head/Bottom.bmp", &info);
	character_Texture(16, 16);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void body_Texture(GLuint object[]){
	glGenTextures(6, object);

	// 정면
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Body/Front.bmp", &info);
	character_Texture(16, 24);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Body/Back.bmp", &info);
	character_Texture(16, 24);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Body/Left.bmp", &info);
	character_Texture(8, 24);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Body/Right.bmp", &info);
	character_Texture(8, 24);

	// 위
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Body/Top.bmp", &info);
	character_Texture(16, 8);

	// 아래
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Body/Bottom.bmp", &info);
	character_Texture(16, 8);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void arm_Texture(GLuint object[], GLuint object2[]){
	glGenTextures(6, object);
	glGenTextures(6, object2);

	// 정면
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Arm/Front_Top.bmp", &info);
	character_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Arm/Back_Top.bmp", &info);
	character_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Arm/Left_Top.bmp", &info);
	character_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Arm/Right_Top.bmp", &info);
	character_Texture(8, 12);

	// 위
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Arm/Top.bmp", &info);
	character_Texture(8, 8);

	// 아래
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Arm/Bottom.bmp", &info);
	character_Texture(8, 8);

	// 정면
	glBindTexture(GL_TEXTURE_2D, object2[0]);
	pBytes = LoadDIBitmap("ImageData/Arm/Front_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object2[1]);
	pBytes = LoadDIBitmap("ImageData/Arm/Back_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, object2[2]);
	pBytes = LoadDIBitmap("ImageData/Arm/Left_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, object2[3]);
	pBytes = LoadDIBitmap("ImageData/Arm/Right_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}

void leg_Texture(GLuint object[], GLuint object2[]){
	glGenTextures(6, object);
	glGenTextures(6, object2);
	// 정면
	glBindTexture(GL_TEXTURE_2D, object[0]);
	pBytes = LoadDIBitmap("ImageData/Leg/Front_Top.bmp", &info);
	character_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object[1]);
	pBytes = LoadDIBitmap("ImageData/Leg/Back_Top.bmp", &info);
	character_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, object[2]);
	pBytes = LoadDIBitmap("ImageData/Leg/Left_Top.bmp", &info);
	character_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, object[3]);
	pBytes = LoadDIBitmap("ImageData/Leg/Right_Top.bmp", &info);
	character_Texture(8, 12);

	// 위
	glBindTexture(GL_TEXTURE_2D, object[4]);
	pBytes = LoadDIBitmap("ImageData/Leg/Top.bmp", &info);
	character_Texture(8, 8);

	// 아래
	glBindTexture(GL_TEXTURE_2D, object[5]);
	pBytes = LoadDIBitmap("ImageData/Leg/Bottom.bmp", &info);
	character_Texture(8, 8);


	// 정면
	glBindTexture(GL_TEXTURE_2D, object2[0]);
	pBytes = LoadDIBitmap("ImageData/Leg/Front_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 후면
	glBindTexture(GL_TEXTURE_2D, object2[1]);
	pBytes = LoadDIBitmap("ImageData/Leg/Back_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 왼쪽
	glBindTexture(GL_TEXTURE_2D, object2[2]);
	pBytes = LoadDIBitmap("ImageData/Leg/Left_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 오른쪽
	glBindTexture(GL_TEXTURE_2D, object2[3]);
	pBytes = LoadDIBitmap("ImageData/Leg/Right_Bottom.bmp", &info);
	character_Texture(8, 12);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
}
