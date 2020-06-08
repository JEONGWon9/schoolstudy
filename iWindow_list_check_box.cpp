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
HWND* hBtnRadio;
HWND hCbWho, hLbWho, hBtnWhoAdd, hBtnWhoRemove;

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

	for (int i = 0; i < 3; i++)
	{
		if (hwnd == hBtnRadio[i])
		{
			setWndRadio(hBtnRadio[i], true);
			printf("Selected hBtnRadio =  %d\n ", i);
			
		}
		else
		{
			setWndRadio(hBtnRadio[i], false);

		}
	}
	if (hwnd == hBtnWhoAdd)
	{
		int index = indexWndComboBox(hCbWho);
		char* str = getWndComboBox(hCbWho, index);

		int last = countWndListBox(hLbWho)-1;

		addWndListBox(hLbWho, last, str);
		free(str);
	}
	else if (hwnd == hBtnWhoRemove)
	{
#if 0
		int index = indexWndListBox(hLbWho);
		if (index != countWndListBox(hLbWho) - 1)
		{
			removeWndListBox(hLbWho, index);
			setWndListBox(hLbWho,index);
		}
#else
		int index = indexWndComboBox(hCbWho);
		removeWndComboBox(hCbWho, index);
		setWndComboBox(hCbWho, index);
#endif

	}



}





void testCtrlSystem(HWND hwnd,HINSTANCE hinstance)
{

	hWnd = hwnd;
	hInstance = hinstance;

	DragAcceptFiles(hWnd, true);


	createWndStatic(10, 10, 200,80, 
		"게임 아카데미\n 경성대에 있나 없나\n 부산인가 ? \n서울인가 ? \n제주인가 ? \n강원도다");

	const char* strBtn[3] = { "Color","Open","Save" };

	hBtn = (HWND*)malloc(sizeof(HWND) * 3);

	for (int i = 0; i < 3; i++)
	{
		hBtn[i] = createWndButton(10+220*i, 120, 200, 80, strBtn[i]);		
	}
	hBtnCheck = createWndCheckBox(10, 220, 200, 80, "동의함");




	createWndGroup(5, 300, 290, 110, "설문지");
	hBtnRadio = (HWND*)malloc(sizeof(HWND) * 3);
	const char* strBtnRadio[3] = { "1","2","3" };
	for (int i = 0; i < 3; i++)
	{
		hBtnRadio[i] = createWndRadio(10 + 100 * i, 320, 80, 80, strBtnRadio[i]);
	}

	const char* strLine[9] = { "최정훈","정성원","김시윤","이호민","조태산","김종민","박수광","노동연","석선진" };
	hCbWho = createWndComboBox(10, 450, 120, 500, strLine, 9);

	const char* strList[2] = { "list of End"};

	hLbWho = createWndListBox(150, 450, 120, 100, strList, 1);

	hBtnWhoAdd = createWndButton(300 , 450, 80, 30, "add");
	hBtnWhoRemove = createWndButton(300, 450+40, 80, 30, "del");

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


HWND createWndRadio(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);
	HWND hwnd = CreateWindow(WC_BUTTON, ws,
		WS_TABSTOP |
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, x, y, width, height,
		(HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;

	free(ws);

	return hwnd;

}
bool getWndRadio(HWND hwnd)
{
	return SendMessage(hwnd, (UINT)BM_GETCHECK, (WPARAM)0, (LPARAM)0);
}
void setWndRadio(HWND hwnd, bool on)
{
	SendMessage(hwnd, BM_SETCHECK, on ? BST_CHECKED : BST_UNCHECKED, 0);
}


HWND createWndGroup(int x, int y, int width, int height, const char* str)
{
	wchar_t* ws = utf8_to_utf16(str);
	HWND hwnd = CreateWindow(WC_BUTTON, ws,
		WS_TABSTOP |
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX, x, y, width, height,
		(HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);

	ctrlNum++;

	free(ws);

	return hwnd;
}


//
// ComboBox
//


HWND createWndComboBox(int x, int y, int width, int height,
	const char** line, int lineNum)
{
	HWND hwnd = CreateWindow(WC_COMBOBOX, NULL,
		WS_TABSTOP |
		WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | CBS_HASSTRINGS, x, y, width, height,
		(HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);
	ctrlNum++;
	addWndComboBox(hwnd, line, lineNum);
	setWndComboBox(hwnd, 0);
	return hwnd;
}

void addWndComboBox(HWND hwnd, int index, const char* str)
{
	wchar_t* s = utf8_to_utf16(str);
	SendMessage(hwnd, CB_INSERTSTRING, (WPARAM)index, (LPARAM)s);
	free(s);
}

void addWndComboBox(HWND hwnd, const char** line, int lineNum)
{
	for (int i = 0; i < lineNum; i++)
		addWndComboBox(hwnd, i, line[i]);
}

void removeWndComboBox(HWND hwnd, int index)
{
	SendMessage(hwnd, CB_DELETESTRING, (WPARAM)index, (LPARAM)0);
}

int countWndComboBox(HWND hwnd)
{
	int index =SendMessage(hwnd, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
	return index;
}

char* getWndComboBox(HWND hwnd, int index)
{
	wchar_t wstr[128];
	SendMessage(hwnd, CB_GETLBTEXT, (WPARAM)index, (LPARAM)wstr);
	return utf16_to_utf8(wstr);
}

int indexWndComboBox(HWND hwnd)
{
	int index = SendMessage(hwnd, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	return index;
}

void setWndComboBox(HWND hwnd, int index)
{
	SendMessage(hwnd, CB_SETCURSEL, (WPARAM)index, (LPARAM)0);
}


//
// ListBox
//




HWND createWndListBox(int x, int y, int width, int height,
	const char** line, int lineNum)
{
	HWND hwnd = CreateWindow(WC_LISTBOX, NULL,
		WS_TABSTOP |
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY |
		WS_HSCROLL | WS_VSCROLL, x, y, width, height,
		(HWND)hWnd, (HMENU)ctrlNum, (HINSTANCE)hInstance, NULL);
	ctrlNum++;
	addWndListBox(hwnd, line, lineNum);
	setWndListBox(hwnd, 0);
	return hwnd;
}

void addWndListBox(HWND hwnd, int index, const char* str)
{
	wchar_t* s = utf8_to_utf16(str);
	SendMessage(hwnd, LB_INSERTSTRING, (WPARAM)index, (LPARAM)s);
	free(s);
}

void addWndListBox(HWND hwnd, const char** line, int lineNum)
{
	for (int i = 0; i < lineNum; i++)
		addWndListBox(hwnd, i, line[i]);
}
void removeWndListBox(HWND hwnd, int index)
{
	SendMessage(hwnd, LB_DELETESTRING, (WPARAM)index, (LPARAM)0);
}
int countWndListBox(HWND hwnd)
{
	int index = SendMessage(hwnd, LB_GETCOUNT, (WPARAM)0, (LPARAM)0);
	return index;
}
int indexWndListBox(HWND hwnd)
{
	int index = SendMessage(hwnd, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	return index;
}
char* getWndListBox(HWND hwnd, int index)
{
	wchar_t wstr[128];
	SendMessage(hwnd, LB_GETTEXT, (WPARAM)index, (LPARAM)wstr);
	return utf16_to_utf8(wstr);
}
void setWndListBox(HWND hwnd, int index)
{
	SendMessage(hwnd, LB_SETCURSEL, (WPARAM)index, (LPARAM)0);
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

HANDLE startOnlyRun(const wchar_t* className)
{
	HANDLE event = CreateEvent(NULL, TRUE, FALSE, className);
	if (GetLastError()==ERROR_ALREADY_EXISTS)
	{
		CloseHandle(event);
		return NULL;
	}
	return event;
}
void endOnlyRun(HANDLE event)
{
	CloseHandle(event);
}

static iCriticalSection* instanceCS = NULL;

iCriticalSection* iCriticalSection::instance() 
{
	if (instanceCS == NULL)
		instanceCS = new iCriticalSection();
	return instanceCS;
}

iCriticalSection::iCriticalSection()
{

	InitializeCriticalSection(&cs);

}
iCriticalSection::~iCriticalSection()
{
	DeleteCriticalSection(&cs);
	instanceCS = NULL;
}
void iCriticalSection::start()
{
	EnterCriticalSection(&cs);
}
void iCriticalSection::end()
{
	LeaveCriticalSection(&cs);
}

