#include"iWindow.h"
#include"iStd.h"

int ctrlNum;
static HWND hWnd;
static HINSTANCE hInstance;

void initwndCtrlSystem()
{
	InitCommonControls();
	ctrlNum = 0;

}
HWND* hBtn;
HWND hBtnCheck;

void testCheckButton(WPARAM wParam,LPARAM lParam)
{
	HWND hwnd = (HWND)lParam;
	for (int i = 0; i < 3; i++)
	{
		if (hwnd == hBtn[i])
		{
			printf("Selected Button =  %d\n ",i);
			if (i == 0)
				showChooseColor(NULL);
			else
				openFileDlg(i == 1 ? true : false, TEXT("JSW Files\0*.jsw\0ALL File\0*.*\0\0"));//파일확장자명\0.*.확장자\0
			return;
		}
	}

	if (hwnd == hBtnCheck)
	{
		setCheckBox(hwnd, !getCheckBox(hwnd));

		return;
	}
}


void testCtrlSystem(HWND hwnd,HINSTANCE hinstance)
{
	hWnd = hwnd;
	hInstance = hinstance;
	//createWndStatic(10, 10, 10, 10, "게임 아카데미");
	createWndStatic(10, 10, 200,80, 
		"게임 아카데미\n 경성대에 있나 없나\n 부산인가 ? \n서울인가 ? \n제주인가 ? \n강원도다");

	const char* strBtn[3] = { "Color","Open","Save" };

	hBtn = (HWND*)malloc(sizeof(HWND) * 3);

	for (int i = 0; i < 3; i++)
	{
		hBtn[i] = createWndButton(10+220*i, 120, 200, 80, strBtn[i]);		
	}
	hBtnCheck = createWndCheckBox(10, 220, 200, 80, "동의함");


}

HWND createWndStatic(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);
	HWND hwnd = CreateWindow(WC_STATIC, ws,
		WS_CHILD | WS_VISIBLE | ES_CENTER, x, y, width, height,
		(HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;

	free(ws);

	return hwnd;
}


HWND createWndButton(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);
	HWND hwnd = CreateWindow(WC_BUTTON, ws,
		WS_TABSTOP | 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, width, height,
		(HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;

	free(ws);

	return hwnd;
}

HWND createWndCheckBox(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);
	HWND hwnd = CreateWindow(WC_BUTTON, ws,
		WS_TABSTOP |
		WS_CHILD | WS_VISIBLE | BS_CHECKBOX, x, y, width, height,
		(HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;

	free(ws);

	return hwnd;
}

bool getCheckBox(HWND hwnd)
{
	return SendMessage(hwnd, (UINT)BM_GETCHECK, (WPARAM)0, (LPARAM)0);

}
void setCheckBox(HWND hwnd, bool on)
{
	SendMessage(hwnd, BM_SETCHECK, on ? BST_CHECKED : BST_UNCHECKED, 0);

}


void showChooseColor(methodChooseColor method)
{
	CHOOSECOLOR cc;
	memset(&cc, 0x00, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;//parent wnd
	COLORREF color[16];
	cc.lpCustColors = color;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	if (!ChooseColor(&cc))
		return;

	int r = (cc.rgbResult & 0x0000ff);
	int g = (cc.rgbResult & 0x00ff00) >> 8;
	int b = (cc.rgbResult & 0xff0000) >> 16;

	printf("r = %d, g = %d , b = %d\n", r, g, b);

	if (method)
		method(r, g, b);

}
//const char* openFileDlg(bool open, const char* filter)
static char* strOpenPath = NULL;
const char* openFileDlg(bool open, LPCWSTR filter)
{
	wchar_t wstrPath[1024];

	OPENFILENAME ofn;
	memset(&ofn, 0x00, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFile = wstrPath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	bool success = false;
	if (open) success = GetOpenFileName(&ofn);
	else success = GetSaveFileName(&ofn);

	if (success)
	{
		wsprintf(wstrPath, TEXT("%s"), ofn.lpstrFile);
		if (strOpenPath)
			free(strOpenPath);
		strOpenPath = utf16_to_utf8(wstrPath);
		printf("strOpenPath = %s\n", strOpenPath);
		return strOpenPath;
	}
	return NULL;
}