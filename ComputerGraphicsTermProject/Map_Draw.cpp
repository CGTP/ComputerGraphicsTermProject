#include "Texture_Load.h"


void draw_Location_Box(GLuint object[], int x, int y, int h){
	glPushMatrix();
	glTranslatef(120 * x, -70 + (120 * (h - 1)), 120 * y);
	draw_Block(60, object);
	glPopMatrix();
}

void draw_Location_Ground(GLuint object[], int x, int y, int h){
	glPushMatrix();
	glTranslatef(120 * x, -70 + (120 * (h - 1)), 120 * y);
	draw_Ground(60, object);
	glPopMatrix();
}

void draw_Ground(GLuint object[]){
	glPushMatrix();
	for (int i = -36; i < 36; ++i){
		for (int j = -13; j <= 13; ++j){
			draw_Location_Ground(object, i, j, 0);
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
	for (int i = -27; i <= 27; ++i){
		if (i == -26) i = 27;
		for (int k = 5; k <= 5; ++k){
			for (int j = -13; j <= 13; ++j){
					draw_Location_Box(object, i, j, k);
			}
		}
	}
	glPopMatrix();
}

void draw_Wooden(GLuint object[]){
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -26; i <= -25; ++i){
		for (int j = -4; j <= -3; ++j){
			for (int k = 1; k <= 2; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -15; i <= -13; ++i){
		for (int j = 5; j <= 7; ++j){
			draw_Location_Box(object, i, j, 1);
		}
	}
	draw_Location_Box(object, -15, 5, 2);
	draw_Location_Box(object, -14, 6, 2);
	draw_Location_Box(object, -14, 5, 2);
	draw_Location_Box(object, -13, 5, 2);
	draw_Location_Box(object, -13, 6, 2);
	draw_Location_Box(object, -13, 7, 2);
	draw_Location_Box(object, -13, 5, 3);
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -7; i <= -6; ++i){
		for (int j = 8; j <= 9; ++j){
			draw_Location_Box(object, i, j, 1);
		}
	}
	draw_Location_Box(object, -6, 8, 2);
	draw_Location_Box(object, -7, 9, 2);
	draw_Location_Box(object, -6, 9, 2);
	draw_Location_Box(object, -6, 9, 3);
	glPopMatrix();
	//-----------------------------------------------------------------------------------------

}

void draw_Stone(GLuint object[]){
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -23; i <= -21; ++i){
		for (int j = 5; j <= 12; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -16; i <= -9; ++i){
		for (int j = 10; j <= 13; ++j){
			for (int k = 1; k <= 4; ++k){
				if ((j == 12 || j == 11) && (k == 1 || k == 2 || k == 3)){
				}
				else{
					draw_Location_Box(object, i, j, k);
				}
			}
		}
	}
	for (int i = 1; i <= 3; ++i){
		draw_Location_Box(object, -16, 11, i);
	}

	for(int i = 1; i <= 3; ++i){
		draw_Location_Box(object, -9, 12, i);
	}
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -24; i <= -22; ++i){
		for (int j = -6; j <= -4; ++j){
			for (int k = 1; k <= 3; ++k){
					draw_Location_Box(object, i, j, k);
			}
		}
	}

	for (int k = 1; k <= 3; ++k){
		draw_Location_Box(object, -21, -6, k);
	}

	for (int i = -23; i <= -21; ++i){
		for (int j = -12; j <= -7; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}

	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -14; i <= -12; ++i){
		for (int j = -1; j <= 1; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}

	for (int k = 1; k <= 3; ++k){
		draw_Location_Box(object, -11, -1, k);
	}

	for (int i = -13; i <= -11; ++i){
		for (int j = -3; j <= -2; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}

	for (int k = 1; k <= 3; ++k){
		draw_Location_Box(object, -10, -3, k);
	}

	for (int i = -12; i <= -10; ++i){
		for (int j = -5; j <= -4; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = 1; i <= 3; ++i){
		for (int j = -12; j <= -10; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}

	for (int k = 1; k <= 3; ++k){
		draw_Location_Box(object, 4, -10, k);
	}

	for (int i = 2; i <= 4; ++i){
		for (int j = -10; j <= -8; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}

	for (int k = 1; k <= 3; ++k){
		draw_Location_Box(object, 5, -8, k);
	}

	for (int i = 3; i <= 5; ++i){
		for (int j = -8; j <= -6; ++j){
			for (int k = 1; k <= 3; ++k){
				draw_Location_Box(object, i, j, k);
			}
		}
	}

	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = -14; i <= -6; ++i){
		for (int j = -13; j <= -10; ++j){
			for (int k = 1; k <= 4; ++k){
				if ((j == -12 || j == -11) && (k == 1 || k == 2 || k == 3)){
				}
				else{
					draw_Location_Box(object, i, j, k);
				}
			}
		}
	}
	for (int i = 1; i <= 3; ++i){
		draw_Location_Box(object, -14, -11, i);
	}

	for (int i = 1; i <= 3; ++i){
		draw_Location_Box(object, -6, -12, i);
	}
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = 6; i <= 10; ++i){
		for (int j = -8; j <= -2; ++j){
			for (int k = 1; k <= 3; ++k){
				if ( (i == 6 && j == -8) || (i == 7 && j == -8) || 
				    (i == 7 && j == -7) || (i == 6 && j == -7) ||
					(i == 6 && j == -6) || (i == 6 && j == -5) ||
					(i == 9 && j == -2) || (i == 9 && j == -3) ||
					(i == 10 && j == -2) || (i == 10 && j == -3) ||
					(i == 10 && j == -4) || (i == 10 && j == -5)){
				}
				else{
					draw_Location_Box(object, i, j, k);
				}
			}
		}
	}
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = 11; i <= 15; ++i){
		for (int j = -2; j <= 4; ++j){
			for (int k = 1; k <= 3; ++k){
				if ((i == 14 && j == -2) || (i == 14 && j == -1) ||
					(i == 15 && j == -2) || (i == 15 && j == -1) ||
					(i == 15 && j == 0) || (i == 15 && j == 1) ||
					(i == 11 && j == 1) || (i == 11 && j == 2) ||
					(i == 11 && j == 3) || (i == 11 && j == 4) ||
					(i == 12 && j == 3) || (i == 12 && j == 4)){
				}
				else{
					draw_Location_Box(object, i, j, k);
				}
			}
		}
	}
	glPopMatrix();
	//-----------------------------------------------------------------------------------------
	glPushMatrix();
	for (int i = 15; i <= 26; ++i){
		for (int j = 11; j <= 13; ++j){
			for (int k = 1; k <= 3; ++k){
					draw_Location_Box(object, i, j, k);
			}
		}
	}
	glPopMatrix();

}