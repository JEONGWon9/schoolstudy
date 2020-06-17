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

WndGL* selectTile;
void methodSelectTileUpdate(float dt);

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

	wgTile = createOpenGL(5, 125, 200, 200, methodTileUpdate, 200, 200);

	const char* strCollision[3] = {"모두이동불가", "공중이동불가", "모두이동가능"};
	hCbCollision = createWndComboBox(5, 335, 130, 120, strCollision, 3, NULL, NULL);
	
	selectTile = createOpenGL(5, 365, 50, 50, methodSelectTileUpdate, 300, 300);
	createWndStatic(60, 380, 80, 20, "SelectTile", NULL, NULL);

	//
	// Right
	//
	createWndGroup(280, 2, 640, 670, "MapCanvas", NULL, NULL);
	hEbMapNum = (HWND*)malloc(sizeof(HWND) * 2);
	for (i = 0; i < 2; i++)
		hEbMapNum[i] = createWndEditBox(300 + 60 * i, 30, 35, 25, "100", WndEditBoxStyle_int, NULL, NULL);
	createWndStatic(340,30, 10, 25, "x", NULL, NULL);

	const char* strMap[2] = {"Open Map", "Save Map"};
	hBtnMapOpen = (HWND*)malloc(sizeof(HWND) * 2);
	for (i = 0; i < 2; i++)
		hBtnMapOpen[i] = createWndButton(400 + 105 * i, 30, 100, 25, strMap[i], NULL, btnMapOpenUpdate);

	wgMap = createOpenGL(300, 65, 600, 600, methodMapUpdate, 300, 300);
}

void freeMapEditor()
{
    // to do.....
	delete wcsMapEditor;
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

void drawMapEditor(float dt)
{
	// opengl
}

void keyMapEditor(iKeyState stat, iPoint point)
{
	// opengl

	RECT rt;
	GetWindowRect(wcsMapEditor->hwndParent, &rt);
	RECT rtTile;// (5, 105, 200, 200) (13(+8), 156(+51), 200, 200)
	GetWindowRect(wgTile->gl->hWnd, &rtTile);
	RECT rtMap;// (300, 40, 300, 300) (308(+8), 91(+51), 300, 300)
	GetWindowRect(wgMap->gl->hWnd, &rtMap);
	int caption = GetSystemMetrics(SM_CYCAPTION);// 23
	int menu = GetSystemMetrics(SM_CYMENU);// 20
	int xframe = GetSystemMetrics(SM_CXFRAME);// 4
	int yframe = GetSystemMetrics(SM_CYFRAME);// 4
	int xBorder = GetSystemMetrics(SM_CXBORDER);// 1
	int yBorder = GetSystemMetrics(SM_CYBORDER);// 1

	iRect tileRt = iRectMake(rtTile.left, rtTile.top, rtTile.right - rtTile.left, rtTile.bottom - rtTile.top);
	tileRt.origin.x = tileRt.origin.x - rt.left - xframe * 2;
	tileRt.origin.y = tileRt.origin.y - rt.top - caption - menu - yframe * 2;
	tileRt.origin.x += xBorder; tileRt.size.width += xBorder * 2;// GetClientRect
	tileRt.origin.y += yBorder;   tileRt.size.height += yBorder * 2;
	iRect mapRt = iRectMake(rtMap.left, rtMap.top, rtMap.right - rtMap.left, rtMap.bottom - rtMap.top);
	mapRt.origin.x = mapRt.origin.x - rt.left - xframe * 2;
	mapRt.origin.y = mapRt.origin.y - rt.top - caption - menu - yframe * 2;
	mapRt.origin.x += xBorder; mapRt.size.width += xBorder * 2;// GetClientRect
	mapRt.origin.y += yBorder; mapRt.size.height += yBorder * 2;

	//printf("rt(%d, %d, %d, %d)tile(%d, %d, %d, %d)map(%d, %d, %d, %d) (%d, %d, %d, %d) point(%f, %f)\n",
	//   rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top,
	//   rtTile.left, rtTile.top, rtTile.right - rtTile.left, rtTile.bottom - rtTile.top,
	//   rtMap.left, rtMap.top, rtMap.right - rtMap.left, rtMap.bottom - rtMap.top,
	//   caption, menu, xframe, yframe,
	//   point.x, point.y);

	if (containPoint(point, tileRt))
	{
		point -= tileRt.origin;
		printf("tile(%f, %f)\n", point.x, point.y);
	}
	else if (containPoint(point, mapRt))
	{
		point -= mapRt.origin;
		printf("map(%f, %f)\n", point.x, point.y);
	}

	wgTile->gl->hWnd;
	wgMap->gl->hWnd;
	
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

	setRGBA(1, 1, 1, 1);
	int numX = getWndInt(hEbOpenImage[0]);
	int numY = getWndInt(hEbOpenImage[1]);
	int w = texs[0]->width;
	int h = texs[0]->height;
	for (int j = 0; j < numY; j++)
	{
		for (int i = 0; i < numX; i++)
		{
			drawImage(texs[numX * j + i], w * i, h * j, TOP | LEFT);
		}
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
	
	//offset
	//map - width ,height
	//window rect
}

void methodSelectTileUpdate(float dt)
{
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}
