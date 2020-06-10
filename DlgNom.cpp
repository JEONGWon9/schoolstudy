#include "DlgNom.h"
#include "ScriptData.h"


HWND hDlgNom;

WndCtrlSystem* wcsNom;

void dragDlgNom(const char* path)
{
	//check .nom 
	if (strcmp(&path[strlen(path) - 4], NOM_EXTENSION))
		return;
	loadDataNom(path);
}


void loadDlgNom(HWND hwnd, HINSTANCE hinstance)
{
	hDlgNom = NULL;//dlgNomproc


	wcsNom = new WndCtrlSystem(hDlgNom, hinstance);
	wcsNom->dragAcceptFiles(dragDlgNom);
	setWndCtrlSystem(wcsNom);


	//add ctrl..

}

void freeDlgNom()
{
	delete wcsNom;
	DestroyWindow(hDlgNom);
}
void showDlgNom(bool show)
{
	if (show == false)
		ShowWindow(hDlgNom, SW_HIDE);
	else
	{
		ShowWindow(hDlgNom, SW_RESTORE);
		SetFocus(hDlgNom);
	}
}

void drawDlgNom(float dt)
{

}

void keyDlgNom(iKeyState stat, iPoint point)
{

}

LRESULT CALLBACK dlgNomProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

		LRESULT result;

	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORDLG:
		result = wcsNom->color(wParam, lParam);
		if (result)
			return result;
		break;
	case WM_DROPFILES:
	{
		wcsNom->dropFiles(wParam, lParam);
	}
	case WM_COMMAND:
	{
		wcsNom->update(wParam, lParam);
	}
	break;

	case WM_CLOSE:
		// unshow
		// destroy
		//ShowWindow(hDlgNom, SW_HIDE);
		showDlgNom(false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}


void loadDataNom(const char* path)
{

}
void saveDataNom(const char* path)
{

}
