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
		hEbMapNum[i] = createWndEditBox(300 + 60 * i, 30, 35, 25, "100", WndEditBoxStyle_int, NULL, NULL);
	createWndStatic(340,30, 10, 25, "x", NULL, NULL);

	const char* strMap[2] = {"Open Map", "Save Map"};
	hBtnMapOpen = (HWND*)malloc(sizeof(HWND) * 2);
	for (i = 0; i < 2; i++)
		hBtnMapOpen[i] = createWndButton(400 + 105 * i, 30, 100, 25, strMap[i], NULL, btnMapOpenUpdate);

	wgMap = createOpenGL(300, 65, 600, 600, methodMapUpdate, 300, 300);
}

void tbTestUpdate(HWND hwnd)
{
	int pos = getWndTrackBarPos(hwnd);
	setWndTrackBarPos(hwnd, pos);
	printf("pos %d\n", pos);
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
void scrollMapEditor(WPARAM wParam, LPARAM lParam)
{
	wcsMapEditor->scroll(wParam, lParam);
}

void drawMapEditor(float dt)
{
	// opengl
}


void keyMapEditor(iKeyState stat, iPoint point)
{

	if (checkOpenGLPosition(wcsMapEditor->hwndParent, wgTile->gl->hWnd, point))
	{
		printf("tile(%f,%f)\n", point.x, point.y);
	}
	else if (checkOpenGLPosition(wcsMapEditor->hwndParent, wgMap->gl->hWnd, point))
	{
		printf("Map(%f,%f)\n", point.x, point.y);
	}


}



Texture** texs = NULL;
char* strImagePath = NULL;
iPoint Tilep = iPointZero;
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
	
	for (int i = 0; i < numX * numY; i++)
	{
		float x = Tilep.x + w * (i % numX);
		float y = Tilep.y + h * (i / numY);
		drawRect(x, y, w, h, 0);
	}

	setRGBA(1, 1, 1, 1);



	

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
	int numX = getWndInt(hEbMapNum[0]);
	int numY = getWndInt(hEbMapNum[1]);
	int w = 50;
	int h = 50;

	setRGBA(1,1,1,1);
	for (int i = 0; i < numX * numY; i++)
	{
		float x = Tilep.x + w * (i % numX);
		float y = Tilep.y + h * (i / numY);
		drawRect(x, y, w, h, 0);
	}
	//map - width ,height
	//window rect
}

void methodSelectTileUpdate(float dt)
{
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}
