#ifndef __TEXTURE_LOAD_H
#define __TEXTURE_LOAD_H

#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void nomal_Texture(GLuint []);
void tree_Texture(GLuint []);
void head_Texture(GLuint[]);
void body_Texture(GLuint[]);
void arm_Texture(GLuint[], GLuint[]);
void leg_Texture(GLuint[], GLuint[]);

void drawBoxFront(int, bool, GLuint);//박스 그리는 함수
void drawBoxBack(int, bool, GLuint);
void drawBoxTop(int, bool, GLuint);
void drawBoxBottom(int, bool, GLuint);
void drawBoxRight(int, bool, GLuint);
void drawBoxLeft(int, bool, GLuint);

static GLubyte *pBytes; // 데이터를 가리킬 포인터
static BITMAPINFO *info; // 비트맵 헤더 저장할 변수

static GLuint block_Nomal_object[6];
static GLuint block_Tree_object[6];
static GLuint character_head_object[6];
static GLuint character_body_object[6];
static GLuint character_arm_top_object[6];
static GLuint character_arm_bottom_object[6];
static GLuint character_leg_top_object[6];
static GLuint character_leg_bottom_object[6];


void block_Texture(int w, int h);
void character_Texture(int w, int h);
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

#endif