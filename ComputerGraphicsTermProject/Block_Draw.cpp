#include "Texture_Load.h"


void draw_Block(int size, GLuint object[]){
	drawBoxFront(size, false, object[0]);
	drawBoxBack(size, false, object[1]);
	drawBoxLeft(size, false, object[2]);
	drawBoxRight(size, false, object[3]);
	drawBoxTop(size, false, object[4]);
	drawBoxBottom(size, false, object[5]);
}