#include "Game.h"

#include "Loading.h"
#include "Intro.h"
#include "Menu.h"
#include "Proc.h"
#include "Ending.h"

#include "Sadari.h"
#include "Jump.h"
#include "2048.h"
#include "Td.h"
#include "Tetris.h"

#include <process.h>

#pragma comment(lib, "ws2_32.lib")
char* getHttpHeader(const char* url, int port)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return NULL;

	struct hostent* host_entry = gethostbyname(url);
	if (host_entry == NULL)
		return NULL;

	int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == -1)
		return NULL;

	struct sockaddr_in server_addr;
	memset(&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	memcpy((void*)&server_addr.sin_addr, (void*)(host_entry->h_addr), sizeof(host_entry->h_addr));

	if (connect(client_socket, (struct sockaddr*) & server_addr, sizeof(server_addr)) == -1)
		return NULL;

	const char* s = "HEAD / HTTP/1.0\r\n\r\n";// only http head
	send(client_socket, s, strlen(s), 0);

	char* buf = (char*)calloc(sizeof(char), 10000);
	int bufLen = 0;
	while (1)
	{
		char b[10000];
		size_t len = recv(client_socket, b, 10000, 0);
		if (len > 0)
		{
			memcpy(&buf[bufLen], b, len);
			bufLen += len;
		}
		else
			break;
	}
	return buf;
}

unsigned int _stdcall threadPrint(void* parm)
{
	char* buf = getHttpHeader("www.ncsoft.com", 80);
	saveFile("thread.txt", buf, 10000);
	free(buf);

	int n = (int)parm;
	_endthreadex(n);
	return 0;
}

void loadGame()
{
#if 0
	threadPrint(NULL);
#else
	unsigned int id;
	HANDLE hand = (HANDLE)_beginthreadex(NULL, 0, threadPrint, (void*)0, NULL, &id);
#endif

#if 0
	loadIntro();
	gameState = gs_intro;
#else
	loadMenu();
	gameState = gs_menu;
#endif

	AudioInfo ai[4] = {
		{ "assets/must/snd/0.wav", false, 0.6f },
		{ "assets/must/snd/1.wav", false, 0.6f },
		{ "assets/must/snd/2.wav", true, 1.0f },
		{ "assets/must/snd/3.wav", true, 1.0f },
	};
	loadAudio(ai, 4);

	audioPlay(2);

	//initShortestPath();
}

void freeGame()
{
	switch (gameState) {
	case gs_intro:	freeIntro(); break;
	case gs_menu:	freeMenu(); break;
	case gs_proc:	freeProc(); break;
	case gs_ending:	freeEnding(); break;
	case gs_sadari: freeSadari(); break;
	case gs_jump:	freeJump(); break;
	case gs_2048:	free2048(); break;
	case gs_td:		freeTd(); break;
	case gs_tetris:	freeTetris(); break;
	}
	freeAudio();

	//freeShortestPath();
}

void drawGame(float dt)
{
	//drawShortestPath(dt);
	//return;

	switch (gameState) {
	case gs_intro:	drawIntro(dt); break;
	case gs_menu:	drawMenu(dt); break;
	case gs_proc:	drawProc(dt); break;
	case gs_ending:	drawEnding(dt); break;
	case gs_sadari:	drawSadari(dt); break;
	case gs_jump:	drawJump(dt); break;
	case gs_2048:	draw2048(dt); break;
	case gs_td:		drawTd(dt); break;
	case gs_tetris:	drawTetris(dt); break;
	}

	drawLoading(dt);
}

void keyGame(iKeyState stat, iPoint point)
{
	//keyShortestPath(stat, point);
	//return;

	if (keyLoading(stat, point))
		return;

	switch (gameState) {
	case gs_intro:	keyIntro(stat, point); break;
	case gs_menu:	keyMenu(stat, point); break;
	case gs_proc:	keyProc(stat, point); break;
	case gs_ending:	keyEnding(stat, point); break;
	case gs_sadari:	keySadari(stat, point); break;
	case gs_jump:	keyJump(stat, point); break;
	case gs_2048:	key2048(stat, point); break;
	case gs_td:		keyTd(stat, point); break;
	case gs_tetris:	keyTetris(stat, point); break;
	}
}

