#pragma once

#include "iStd.h"

void loadDlgQuest(HWND hwnd, HINSTANCE hinstance);
void freeDlgQuest();
void showDlgQuest(bool show);
void drawDlgQuest(float dt);
void keyDlgQuest(iKeyState stat, iPoint point);

LRESULT CALLBACK dlgQuestProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


#define QUEST_EXTENSION ".qst"
void loadDataQuest(const char* path);
void saveDataQuest(const char* path);