#ifndef __TEXTURE_LOAD_H
#define __TEXTURE_LOAD_H

#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// OpenGL Aux 사용으로 인한 모듈 추가
#include "OpenGL_Aux/GLAUX.H"
#pragma comment(lib, "./OpenGL_Aux/GLAUX")
// OpenGL Aux 사용으로 인한 모듈 추가 종료

// json 으로 인한 추가 모듈
#include <string>
#include <vector>
#include "json/json.h"
#if defined(_WIN32) || defined(_WIN64)
#if defined(_DEBUG)
#define JSON_DEBUG
#pragma comment(lib, "./lib_json/json_vc71_libmtd")
#else
#pragma comment(lib, "./lib_json/json_vc71_libmt")
#endif
#else // linux
#endif

// json 으로 인한 추가 모듈


static AUX_RGBImageRec as; // 테스트용 

void nomal_Texture(GLuint []);
void tree_Texture(GLuint []);
void brick_Texture(GLuint[]);
void wooden_Texture(GLuint[]);
void stone_Texture(GLuint[]);

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

void draw_Block(int, GLuint[]);	// 텍스쳐 맵핑된 블럭을 사이즈를 받아 그리기.
void draw_Wall(GLuint []); // 벽그리는 함수
void draw_Ground(GLuint []);	// 땅그리는 함수
void draw_Wooden(GLuint[]);	// 나무박스 그려준다.
void draw_Stone(GLuint[]);	// 벽돌을 그려준다.

static GLubyte *pBytes; // 데이터를 가리킬 포인터
static BITMAPINFO *info; // 비트맵 헤더 저장할 변수

static GLuint block_Nomal_object[6];
static GLuint block_Tree_object[6];
static GLuint block_Brick_object[6];
static GLuint block_Wooden_object[6];
static GLuint block_Stone_object[6];

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