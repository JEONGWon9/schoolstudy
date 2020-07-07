#pragma once

#include "iStd.h"

void load2048();
void free2048();
void draw2048(float dt);
void key2048(iKeyState stat, iPoint point);

// left / right / up / down

// 1. 같은 숫자 합해진다.(한번만) 끝으로 보낸다.
// 2. 반대편에 최고 숫자보다 작은 숫자가 랜덤 하나 생성

// 종료 
// 움직일수 없을때(합쳐질게 없을때 && 더이상 생길수 없을)

// N x N
// number(1, 2, 4, 8, 1024, 2048, 4096 ) 

#define T_NUM_X 2
#define T_NUM_Y 2
#define T_SIZE_W 60 
#define T_SIZE_H 60

struct BLOCK
{
	int number;
	iImage* img;// 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096
	BLOCK* com;// bool combine;
	float createDt;
	float combineDt;
};
#define _createDt 0.1f
#define _combineDt 0.1f

void addBlock(int x, int y, int num, bool create=false, bool combine=false);
void copyBlock(BLOCK* to, BLOCK* from);
void moveBlock(int direction);

iPoint positionOfIndex(int x, int y);

// 0 소멸, 1 증가, 2 그대로
enum BlockStat {
	BlockStatDestroy = 0,
	BlockStatIncrease,
	BlcokStatKeep,
};
struct EffectBlock
{
	Texture* tex;
	iPoint sp, ep;
	int number;
	BlockStat bs;
	BLOCK* b;
};

extern int directionCreate;
#define _effectBlockDt 0.2f

void loadEffectBlock();
void freeEffectBlock();
bool drawEffectBlock(float dt);

void addEffectBlock(BLOCK* b, iPoint cp, BlockStat stat);
void changeEffectBlock(BLOCK* b, iPoint ep);

// -----------------------------------
// popGameover
// -----------------------------------
extern iPopup* popGameover;

void createPopGameover();
void freePopGameover();
void showPopGameover(bool show);
void drawPopGameover(float dt);
bool keyPopGameover(iKeyState stat, iPoint point);


