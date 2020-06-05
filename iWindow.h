#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#pragma comment(lib,"comctl32.lib")


void initwndCtrlSystem();

void testCtrlSystem(HWND hwnd, HINSTANCE hinstance);

HWND createWndStatic(int x, int y, int width, int height, const char* str);

HWND createWndButton(int x, int y, int width, int height, const char* str);


HWND createWndCheckBox(int x, int y, int width, int height, const char* str);


void testCheckButton(WPARAM wParam, LPARAM lParam);

bool getCheckBox(HWND hwnd);
void setCheckBox(HWND hwnd, bool on);

typedef void(*methodChooseColor)(int r, int g, int b);
void showChooseColor(methodChooseColor method);


//wchar_t ->pointer-LPCWSTR
const char* openFileDlg(bool open, LPCWSTR filter);
//const char* openFileDlg(bool open, const char* filter);