#pragma once

#include "iStd.h"

#include "iWindow.h"

void loadMapEditor(HWND hwnd);
void freeMapEditor();
void dragMapEditor(WPARAM wParam, LPARAM lParam);
LRESULT colorMapEditor(WPARAM wParam, LPARAM lParam);
void updateMapEditor(WPARAM wParam, LPARAM lParam);
void drawMapEditor(float dt);
void keyMapEditor(iKeyState stat, iPoint point);
void scrollMapEditor(WPARAM wParam, LPARAM lParam);

/*
1. 이미지 스크롤

2. wgtile -> wgMap 좌표.

3.tile ->map으로 그리기
--기본--

4. 레이어//색변환//충돌체크처리//


*/