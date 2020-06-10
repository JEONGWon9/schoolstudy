#include "DlgQuest.h"
#include "ScriptData.h"

HWND hDlgQuest;

WndCtrlSystem* wcsQuest;




void dragDlgQuest(const char* path)
{
	//check .nom 
	if (strcmp(&path[strlen(path) - 4], QUEST_EXTENSION))
		return;
	loadDataQuest(path);
}

void loadDlgQuest(HWND hwnd, HINSTANCE hinstance)
{
	hDlgQuest = NULL;//dlgNomproc


	wcsQuest = new WndCtrlSystem(hDlgQuest, hinstance);
	wcsQuest->dragAcceptFiles(dragDlgQuest);
	setWndCtrlSystem(wcsQuest);


	//add ctrl..

}

void freeDlgQuest()
{
	delete wcsQuest;
	DestroyWindow(hDlgQuest);
}



void showDlgQuest(bool show)
{
	if (show == false)
		ShowWindow(hDlgQuest, SW_HIDE);
	else
	{
		ShowWindow(hDlgQuest, SW_RESTORE);
		SetFocus(hDlgQuest);
	}
}

void dragDlgQuest(WPARAM wParam, LPARAM lParam)
{
	wcsQuest->dropFiles(wParam, lParam);

}

LRESULT colorDlgQuest(WPARAM wParam, LPARAM lParam)
{

	return wcsQuest->color(wParam, lParam);
}

void updateDlgQuest(WPARAM wParam, LPARAM lParam)
{
	wcsQuest->update(wParam, lParam);


}

void drawDlgQuest(float dt)
{

}

void keyDlgQuest(iKeyState stat, iPoint point)
{

}

LRESULT CALLBACK dlgQuestProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

		LRESULT result;

	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORDLG:
		result = wcsQuest->color(wParam, lParam);
		if (result)
			return result;
		break;
	case WM_DROPFILES:
	{
		wcsQuest->dropFiles(wParam, lParam);
	}
	case WM_COMMAND:
	{
		wcsQuest->update(wParam, lParam);
	}
	break;

	case WM_CLOSE:
		// unshow
		// destroy
		//ShowWindow(hDlgQuest, SW_HIDE);
		showDlgQuest(false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


void loadDataQuest(const char* path)
{			
			
}			
void saveDataQuest(const char* path)
{

}
