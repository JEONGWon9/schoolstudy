#pragma once

#include "iStd.h"

void loadDlgNom(HWND hwnd, HINSTANCE hinstance);
void freeDlgNom();
void showDlgNom(bool show);
void drawDlgNom(float dt);
void keyDlgNom(iKeyState stat, iPoint point);

LRESULT CALLBACK dlgNomProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define NOM_EXTENSION ".nom"
void loadDataNom(const char* path);
void saveDataNom(const char* path);
