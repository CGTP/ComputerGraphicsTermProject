#ifndef __TEXTURE_LOAD_H
#define __TEXTURE_LOAD_H

#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
// json ���� ���� �߰� ���
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

// json ���� ���� �߰� ���

void nomal_Texture(GLuint []);
void tree_Texture(GLuint []);
void head_Texture(GLuint[]);
void body_Texture(GLuint[]);
void arm_Texture(GLuint[], GLuint[]);
void leg_Texture(GLuint[], GLuint[]);

void drawBoxFront(int, bool, GLuint);//�ڽ� �׸��� �Լ�
void drawBoxBack(int, bool, GLuint);
void drawBoxTop(int, bool, GLuint);
void drawBoxBottom(int, bool, GLuint);
void drawBoxRight(int, bool, GLuint);
void drawBoxLeft(int, bool, GLuint);

void draw_Block(int, GLuint[]);	// �ؽ��� ���ε� ���� ����� �޾� �׸���.

static GLubyte *pBytes; // �����͸� ����ų ������
static BITMAPINFO *info; // ��Ʈ�� ��� ������ ����

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