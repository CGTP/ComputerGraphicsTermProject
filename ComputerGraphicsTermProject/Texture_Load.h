#ifndef __TEXTURE_LOAD_H
#define __TEXTURE_LOAD_H

#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// OpenGL Aux ������� ���� ��� �߰�
#include "OpenGL_Aux/GLAUX.H"
#pragma comment(lib, "./OpenGL_Aux/GLAUX")
// OpenGL Aux ������� ���� ��� �߰� ����

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
void brick_Texture(GLuint[]);
void wooden_Texture(GLuint[]);
void stone_Texture(GLuint[]);

void head_Texture(GLuint[]);
void body_Texture(GLuint[]);
void arm_Texture(GLuint[], GLuint[]);
void leg_Texture(GLuint[], GLuint[]);

void zombie_head_Texture(GLuint[]);
void zombie_body_Texture(GLuint[]);
void zombie_arm_Texture(GLuint[], GLuint[]);
void zombie_leg_Texture(GLuint[], GLuint[]);

void drawBoxFront(int, bool, GLuint);//�ڽ� �׸��� �Լ�
void drawBoxBack(int, bool, GLuint);
void drawBoxTop(int, bool, GLuint);
void drawBoxBottom(int, bool, GLuint);
void drawBoxRight(int, bool, GLuint);
void drawBoxLeft(int, bool, GLuint);

void draw_Block(int, GLuint[]);	// �ؽ��� ���ε� ���� ����� �޾� �׸���.
void draw_Map_Block(int, GLuint[], int); // ����ȭ�� ���� �� �缳��.
void draw_Ground(int, GLuint[]);
void draw_Wall(GLuint []); // ���׸��� �Լ�
void draw_Ground(GLuint []);	// ���׸��� �Լ�
void draw_Wooden(GLuint[]);	// �����ڽ� �׷��ش�.
void draw_Stone(GLuint[]);	// ������ �׷��ش�.

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

static GLuint zombie_head_object[6];
static GLuint zombie_body_object[6];
static GLuint zombie_arm_top_object[6];
static GLuint zombie_arm_bottom_object[6];
static GLuint zombie_leg_top_object[6];
static GLuint zombie_leg_bottom_object[6];

extern int map_DATA[6][72][27]; // ����, ����, ����

void Load_TextureBMP(GLuint [], int, char *);
AUX_RGBImageRec *LoadBMP(char *Filename);

#endif