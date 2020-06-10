#pragma once

#include "iStd.h"

void loadDlgItem(HWND hwnd, HINSTANCE hinstance);
void freeDlgItem();
void showDlgItem(bool show);
void drawDlgItem(float dt);
void keyDlgItem(iKeyState stat, iPoint point);


LRESULT CALLBACK dlgItemProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


#define ITEM_EXTENSION ".itm"

void loadDataItem(const char* path);
			 
void saveDataItem(const char* path);
