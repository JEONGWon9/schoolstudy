#include "MapEditor.h"

WndCtrlSystem* wcsMapEditor;

// Left - state
HWND hCbState;

// Left - 0. offset
HWND* hEbOff;

// Left - 1. image
HWND hBtnOpenImage;
void btnOpenImageUpdate(HWND hwnd);
HWND* hEbOpenImage;

WndGL* wgTile;
void methodTileUpdate(float dt);

// Left - 2. collision
HWND hCbCollision;

// Right - world map
HWND* hEbMapNum;
HWND* hBtnMapOpen;
void btnMapOpenUpdate(HWND hwnd);

WndGL* wgMap;
void methodMapUpdate(float dt);

HWND hTbTest;

WndGL* selectTile;
void methodSelectTileUpdate(float dt);


int selectedTileIndex;
MapTile* mapTile;
//iPoint prevPoint;
iPoint offMap;
iPoint offTile;
bool moving;

void loadMapEditor(HWND hwnd)
{
	int i;

	initWndCtrlSystem();

	wcsMapEditor = new WndCtrlSystem(hwnd);
	setWndCtrlStyem(wcsMapEditor);
	createWndGroup(2, 5, 250, 430, "MapTileSet", NULL, NULL);
    // to do....
	const char* strState[3] = {"이동", "이미지", "충돌"};
	hCbState = createWndComboBox(5, 25, 80, 160, strState, 3, NULL, NULL);

	hEbOff = (HWND*)malloc(sizeof(HWND) * 2);
	for (i = 0; i < 2; i++)
	{
		createWndStatic(5 + 80 * i, 45, 10, 25, i == 0 ? "X" : "Y", NULL, NULL);
		hEbOff[i] = createWndEditBox(20 + 80*i, 60, 60, 25, "0", WndEditBoxStyle_int, NULL, NULL);
	}

	// open, numX, numY
	hBtnOpenImage = createWndButton(5, 95, 100, 25, "Open Image", NULL, btnOpenImageUpdate);
	hEbOpenImage = (HWND*)malloc(sizeof(HWND) * 2);
	for (i = 0; i < 2; i++)
		hEbOpenImage[i] = createWndEditBox(110 + 40*i, 95, 35, 25, "5", WndEditBoxStyle_int, NULL, NULL);

	wgTile = createOpenGL(5, 125, 240, 200, methodTileUpdate, 240, 200);

	const char* strCollision[3] = {"모두이동불가", "공중이동불가", "모두이동가능"};
	hCbCollision = createWndComboBox(5, 335, 130, 120, strCollision, 3, NULL, NULL);
	
	void tbTestUpdate(HWND hwnd);
	hTbTest = createWndTrackBar(50, 500, 200, 30, "0\n100\n50", NULL, tbTestUpdate, 1);




	selectTile = createOpenGL(5, 365, 50, 50, methodSelectTileUpdate, 300, 300);
	createWndStatic(60, 380, 80, 20, "SelectTile", NULL, NULL);

	//
	// Right
	//
	createWndGroup(280, 2, 640, 670, "MapCanvas", NULL, NULL);
	hEbMapNum = (HWND*)malloc(sizeof(HWND) * 2);
	for (i = 0; i < 2; i++)
		hEbMapNum[i] = createWndEditBox(300 + 60 * i, 30, 35, 25, "50", WndEditBoxStyle_int, NULL, ebMapNumUpdate);
	createWndStatic(340,30, 10, 25, "x", NULL, NULL);

	const char* strMap[2] = {"Open Map", "Save Map"};
	hBtnMapOpen = (HWND*)malloc(sizeof(HWND) * 2);
	for (i = 0; i < 2; i++)
		hBtnMapOpen[i] = createWndButton(400 + 105 * i, 30, 100, 25, strMap[i], NULL, btnMapOpenUpdate);

	wgMap = createOpenGL(300, 65, 600, 600, methodMapUpdate, 600, 600);

	selectedTileIndex = -1;
	int numX = getWndInt(hEbMapNum[0]);
	int numY = getWndInt(hEbMapNum[1]);
	mapTile = (MapTile*)malloc(sizeof(MapTile) * numX * numY);
	for (int j = 0; j < numY; j++)
		for (i = 0; i < numX; i++)
			mapTile[numX * j + i].imgIndex = -1;
	offMap = iPointZero;
	offTile = iPointZero;
	moving = false;
}

void tbTestUpdate(HWND hwnd)
{
	int pos = getWndTrackBarPos(hwnd);
	setWndTrackBarPos(hwnd, pos);
	printf("pos %d\n", pos);
}

void ebMapNumUpdate(HWND hwnd)
{
	free(mapTile);

	int numX = getWndInt(hEbMapNum[0]);
	int numY = getWndInt(hEbMapNum[1]);
	mapTile = (MapTile*)malloc(sizeof(MapTile) * numX * numY);
}


void freeMapEditor()
{
    // to do.....
	delete wcsMapEditor;
	free(mapTile);
}

void dragMapEditor(WPARAM wParam, LPARAM lParam)
{
	wcsMapEditor->dropFiles(wParam, lParam);
}

LRESULT colorMapEditor(WPARAM wParam, LPARAM lParam)
{
	return wcsMapEditor->color(wParam, lParam);
}

void updateMapEditor(WPARAM wParam, LPARAM lParam)
{
	wcsMapEditor->update(wParam, lParam);
}
void scrollMapEditor(WPARAM wParam, LPARAM lParam)
{
	wcsMapEditor->scroll(wParam, lParam);
}

void drawMapEditor(float dt)
{
	// opengl
}


Texture** texs = NULL;
char* strImagePath = NULL;
void btnOpenImageUpdate(HWND hwnd)
{
	const char* path = openFileDlg(true, TEXT("Image Files(*.png, *.jpg)\0*.png;*.jpg\0"));
	if (path)
	{
		int len = strlen(path);
		strImagePath = (char*)calloc(sizeof(char), 1 + len);
		strcpy(strImagePath, path);
	}
}

void methodTileUpdate(float dt)
{
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (strImagePath)
	{
		int numX = getWndInt(hEbOpenImage[0]);
		int numY = getWndInt(hEbOpenImage[1]);
		if (texs)
		{
			int i, j = numX * numY;
			for (i = 0; i < j; i++)
				freeImage(texs[i]);
			free(texs);
		}
		texs = createDivideImage(numX, numY, strImagePath);

		free(strImagePath);
		strImagePath = NULL;
	}

	
	if (texs == NULL)
		return;

	int w = texs[0]->width;
	int h = texs[1]->height;
	int numX = getWndInt(hEbOpenImage[0]);
	int numY = getWndInt(hEbOpenImage[1]);

	setRGBA(1, 1, 1, 1);
	for (int j = 0; j < numY; j++)
	{
		for (int i = 0; i < numX; i++)
			drawImage(texs[numX * j + i], w * i, h * j, TOP | LEFT);
	}
	
	int num = numX * numY;
	for (int i = 0; i < num; i++)
		drawRect(w * (i % numX), h * (i / numX), w, h, 0);

	if (selectedTileIndex != -1)//선택.
	{
		setRGBA(1, 0, 0, 1);
		drawRect(w * (selectedTileIndex % numX), h * (selectedTileIndex / numX), w, h, 0);
		setRGBA(1, 1, 1, 1);
	}
}

void btnMapOpenUpdate(HWND hwnd)
{
	bool open = (hBtnMapOpen[0] == hwnd);
	const char* path = openFileDlg(open, TEXT("Map Files(*.map)\0*.map\0"));
	if (path)
	{
		// to do...
	}
	

}

void methodMapUpdate(float dt)
{
	// world map
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (texs == NULL)
		return;

	int w = texs[0]->width;
	int h = texs[1]->height;
	int numX = getWndInt(hEbMapNum[0]);
	int numY = getWndInt(hEbMapNum[1]);

	int x = offMap.x;
	int y = offMap.y;

	for (int j = 0; j < numY; j++)
	{
		for (int i = 0; i < numX; i++)
		{
			MapTile* mt = &mapTile[numX * j + i];
			if (mt->imgIndex != -1)
			{
				setRGBA(1,1,1,1);
				drawImage(texs[mt->imgIndex], x + w * i, y + h * j, TOP | LEFT);
			}

			if (mt->collision == 0)
				setRGBA(1, 0, 0, 0.5f);
			else if (mt->collision == 1)
				setRGBA(1, 1, 0, 0.5f);
			else
				continue;
			fillRect(x + w * i, y + h * j, w, h, 0);
		}
	}

	setRGBA(1, 1, 1, 1);
	int num = numX * numY;
	for (int i = 0; i < num; i++)
		drawRect(x + w * (i % numX), y + h * (i / numX), w, h, 0);
	
	//map - width ,height
	//window rect

}

void methodSelectTileUpdate(float dt)
{
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void keyMapEditor(iKeyState stat, iPoint point)
{
	if (texs == NULL)
		return;

	int w = texs[0]->width;
	int h = texs[1]->height;

	if (checkOpenGLPosition(wcsMapEditor->hwndParent, wgTile->gl->hWnd, point))
	{
		//printf("tile(%f,%f)\n", point.x, point.y);

		int numX = getWndInt(hEbOpenImage[0]);
		int numY = getWndInt(hEbOpenImage[1]);
		if (stat == iKeyStateBegan)
		{
			int x = point.x - offTile.x; x /= w;
			int y = point.y - offTile.y; y /= h;
			selectedTileIndex = numX * y + x;
		}
	}
	else if (checkOpenGLPosition(wcsMapEditor->hwndParent, wgMap->gl->hWnd, point))
	{
		//printf("Map(%f,%f)\n", point.x, point.y);
		int numX = getWndInt(hEbMapNum[0]);
		int numY = getWndInt(hEbMapNum[1]);

		int cb = indexWndComboBox(hCbState);
		if (cb == 0)// move
		{
			if (stat == iKeyStateBegan)
			{
				moving = true;
				prevPoint = point;
			}
			else if (stat == iKeyStateMoved)
			{
				if (moving)
				{
					offMap += (point - prevPoint);
					prevPoint = point;
				}
			}
			else if (stat == iKeyStateEnded)
			{
				moving = false;
			}
		}
		else if (cb == 1)// image
		{
			if (stat == iKeyStateBegan)
			{
				moving = true;

				int x = point.x - offMap.x; x /= w;
				int y = point.y - offMap.y; y /= h;
				MapTile* mt = &mapTile[numX * y + x];
				mt->imgIndex = selectedTileIndex;
			}
			else if (stat == iKeyStateMoved)
			{
				if (moving)
				{
					int x = point.x - offMap.x; x /= w;
					int y = point.y - offMap.y; y /= h;
					MapTile* mt = &mapTile[numX * y + x];
					mt->imgIndex = selectedTileIndex;
				}
			}
			else if (stat == iKeyStateEnded)
			{
				moving = false;
			}
		}
		else if (cb == 2)// collision
		{
			int collision = indexWndComboBox(hCbCollision);
			if (stat == iKeyStateBegan)
			{
				moving = true;

				int x = point.x - offMap.x; x /= w;
				int y = point.y - offMap.y; y /= h;
				MapTile* mt = &mapTile[numX * y + x];
				mt->collision = collision;
			}
			else if (stat == iKeyStateMoved)
			{
				if (moving)
				{
					int x = point.x - offMap.x; x /= w;
					int y = point.y - offMap.y; y /= h;
					MapTile* mt = &mapTile[numX * y + x];
					mt->collision = collision;
				}
			}
			else if (stat == iKeyStateEnded)
			{
				moving = false;
			}
		}
	}
	

	//switch (stat)
	//{
	//case iKeyStateBegan:
	// break;
	//case iKeyStateMoved:
	//	for (int i = 0; i < num; i++)
	//	{
	//		if (containPoint(point, tileupdate[i]))
	//		{
	//			//printf("%f,%f \n",point.x,point.y);
	//			setRGBA(1, 0, 0, 1);
	//			drawRect(tileupdate[i], 0);
	//		}
	//	}
	//	break;
	//case iKeyStateEnded:
	//	break;
	//}


}

