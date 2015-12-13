#include "Texture_Load.h"

void wall_background_Texture(GLuint object[]){

	Load_TextureBMP(object, 0, "ImageData/Wall/wall.bmp");
}

void draw_wall_background(GLuint object[]){
	glPushMatrix();
	// Front
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, object[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-4320, 3120, -1560);   //1
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-4320, -60, -1560);   //2
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(4320, -60, -1560);   //3
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(4320, 3120, -1560);   //4
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	// Back
	glTranslated(0, 0, 3240);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, object[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-4320, 3120, -1560);   //1
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(4320, 3120, -1560);   //4
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(4320, -60, -1560);   //2
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-4320, -60, -1560);   //3
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}