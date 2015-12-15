#include "Texture_Load.h"

// 미니맵 그리는 함수, 변수
void draw_MiniMap(int CharX, int CharZ){
	for (int i = 0; i < 72; ++i){
		for (int j = 0; j < 27; ++j){
			int dataX = (i * 3), dataY = (i * 3) + 3;
			int LimitH = (j * 3) + 3;
			int char_X = (CharX / 120) + 36, char_Z = (CharZ / 120) + 13;
			glBegin(GL_POLYGON);
			if (map_DATA[1][i][j] == 1){
				glColor3f(0, 0, 1);
			}
			else{
				if (i == char_X && j == char_Z){
					glColor3f(1, 0, 0);
				}
				else{
					glColor3f(0.1, 0.1, 0.1);
				}
			}
			glVertex3f(dataX, 0, 0);
			glVertex3f(dataX, LimitH, 0);
			glVertex3f(dataY, LimitH, 0);
			glVertex3f(dataY, 0, 0);
			glEnd();
		}
	}
}

void draw_Crosshair(bool sight){
	if (sight){
		glColor3f(0, 0, 1);
		glBegin(GL_QUADS);// Crosshair
		glVertex2f(396, 304);
		glVertex2f(404, 304);
		glVertex2f(404, 296);
		glVertex2f(396, 296);
		glEnd();
	}
	else{
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);// Crosshair
		glVertex2f(380, 300);
		glVertex2f(390, 300);

		glVertex2f(410, 300);
		glVertex2f(420, 300);

		glVertex2f(400, 280);
		glVertex2f(400, 290);

		glVertex2f(400, 310);
		glVertex2f(400, 320);
		glEnd();
	}
}