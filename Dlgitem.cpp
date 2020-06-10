#include "Dlgitem.h"
#include "ScriptData.h"

HWND hDlgItem;

WndCtrlSystem* wcsItem;



void dragDlgItem(const char* path)
{
	//check .nom 
	if (strcmp(&path[strlen(path) - 4], ITEM_EXTENSION))
		return;
	loadDataItem(path);
}

void loadDlgItem(HWND hwnd, HINSTANCE hinstance)
{
	hDlgItem = NULL;//dlgNomproc


	wcsItem = new WndCtrlSystem(hDlgItem, hinstance);
	wcsItem->dragAcceptFiles(dragDlgItem);
	setWndCtrlSystem(wcsItem);


	//add ctrl..

}

void freeDlgItemgNom()
{
	delete wcsItem;
	DestroyWindow(hDlgItem);
}
void showDlgItem(bool show)
{
	if (show == false)
		ShowWindow(hDlgItem, SW_HIDE);
	else
	{
		ShowWindow(hDlgItem, SW_RESTORE);
		SetFocus(hDlgItem);
	}
}

void dragDlgItem(WPARAM wParam, LPARAM lParam)
{
	wcsItem->dropFiles(wParam, lParam);

}

LRESULT colorDlgItem(WPARAM wParam, LPARAM lParam)
{

	return wcsItem->color(wParam, lParam);
}

void updateDlgItem(WPARAM wParam, LPARAM lParam)
{
	wcsItem->update(wParam, lParam);


}

void drawDlgItem(float dt)
{

}

void keyDlgItem(iKeyState stat, iPoint point)
{

}

LRESULT CALLBACK dlgItemProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

		LRESULT result;

	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORDLG:
		result = wcsItem->color(wParam, lParam);
		if (result)
			return result;
		break;
	case WM_DROPFILES:
	{
		wcsItem->dropFiles(wParam, lParam);
	}
	case WM_COMMAND:
	{
		wcsItem->update(wParam, lParam);
	}
	break;

	case WM_CLOSE:
		// unshow
		// destroy
		showDlgItem(false);
		//ShowWindow(hDlgItem, SW_HIDE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


void loadDataItem(const char* path)
{

}
void saveDataItem(const char* path)
{

}
