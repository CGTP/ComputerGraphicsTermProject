#include "Texture_Load.h"


void draw_Location_Box(GLuint object[], int x, int y, int h){
	glPushMatrix();
	glTranslatef(120 * x, -70 + (120 * (h - 1)), 120 * y);
	draw_Block(60, object);
	glPopMatrix();
}


void draw_Ground(GLuint object[]){
	glPushMatrix();
	for (int i = -36; i < 36; ++i){
		for (int j = -13; j <= 13; ++j){
			draw_Location_Box(object, i, j, 0);
		}
	}
	glPopMatrix();
}

void draw_Wall(GLuint object[]){
	glPushMatrix();
	for (int i = -27; i <= 27; ++i){
		if (i == -26) i = 27;
		for (int k = 1; k <= 4; ++k){
			for (int j = -13; j <= 13; ++j){
				if (j == -9 || j == -8 || j == -7 || j == 9 || j == 8 || j == 7){
				}
				else{
					draw_Location_Box(object, i, j, k);
				}
			}
		}
	}
	glPopMatrix();
}

void draw_Wooden(GLuint object[]){
	glPushMatrix();
	for (int i = -26; i <= -25; ++i){
		for (int j = -4; j <= -3; ++j){
			for (int k = 1; k <= 2; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}
	glPopMatrix();


	glPushMatrix();
	for (int i = -15; i <= -13; ++i){
		for (int j = 5; j <= 7; ++j){
			draw_Location_Box(object, i, j, 1);
		}
	}
	draw_Location_Box(object, -15, 7, 2);
	draw_Location_Box(object, -14, 6, 2);
	draw_Location_Box(object, -14, 5, 2);
	draw_Location_Box(object, -13, 5, 2);
	draw_Location_Box(object, -13, 6, 2);
	draw_Location_Box(object, -13, 7, 2);
	draw_Location_Box(object, -13, 6, 3);

	glPopMatrix();

}

void draw_Stone(GLuint object[]){
	glPushMatrix();
	for (int i = -23; i <= -21; ++i){
		for (int j = 5; j <= 12; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}
	glPopMatrix();


	glPushMatrix();
	for (int i = -16; i <= -9; ++i){
		for (int j = 11; j <= 13; ++j){
			for (int k = 1; k <= 3; ++k){
				if (j == 12 && (k == 1 || k == 2)){
				}
				else{
					draw_Location_Box(object, i, j, k);
				}
			}
		}
	}
	glPopMatrix();
}