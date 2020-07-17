#include "Tetris.h"

#include "Loading.h"
#include "Menu.h"

NewBlock newBlock[5][4] =
{
	{// 1자 모양
		{	4, { {0,0}, {0,1}, {0,2}, {0,3} },	},
		{	4, { {0,0}, {1,0}, {2,0}, {3,0} },	},
		{	4, { {0,0}, {0,1}, {0,2}, {0,3} },	},
		{	4, { {0,0}, {1,0}, {2,0}, {3,0} },	},
	},
	{// ㄱ자 모양
		{	5, { {0,0}, {1,0}, {2,0}, {3,0}, {3,1} },	},
		{	5, { {0,0}, {1,0}, {0,1}, {0,2}, {0,3} },	},
		{	5, { {0,0}, {0,1}, {1,1}, {2,1}, {3,1} },	},
		{	5, { {0,3}, {1,3}, {1,2}, {1,1}, {1,0} },	},
	},
};

struct MyBlock
{
	int type, dir;
	iPoint p;
};
MyBlock mb;

void loadTetris()
{
	printf("loadTetris()\n");
	mb.type = 1;// 1 of 5
	mb.dir = 0;// 1 of 4
}

void freeTetris()
{
	printf("freeTetris()\n");
}

void drawTetris(float dt)
{
	setRGBA(1, 0, 0, 1);
	fillRect(0, 0, devSize.width, devSize.height);

	setRGBA(1, 1, 1, 1);

	NewBlock* nb = &newBlock[mb.type][mb.dir];
	for (int i = 0; i < nb->num; i++)
	{
		uint8* b = nb->block[i];
		fillRect(60*b[0], 60*b[1], 60, 60);
	}
}

void rotateBlock(bool cw)
{
	if (cw)
	{
		mb.dir++;
		if (mb.dir == 4)
			mb.dir = 0;
	}
	else
	{
		mb.dir--;
		if (mb.dir == -1)
			mb.dir = 3;
	}
}

void keyTetris(iKeyState stat, iPoint point)
{
	switch (stat) {

	case iKeyStateBegan:
		rotateBlock(point.x < devSize.width/2 ? true : false);
		break;

	case iKeyStateMoved:
		break;

	case iKeyStateEnded:
		break;
	}
}
