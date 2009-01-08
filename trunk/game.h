/*******************************************************************************
* game.h                                                    fileencoding=UTF-8 *
*******************************************************************************/

#include "claim.h"

#ifndef __GAME_H__
#define __GAME_H__

/*******************************************************************************
* Headers                                                                      *
*******************************************************************************/

#include <stdio.h>

#include <stdio.h>
#include <limits.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_mixer.h>

#include "const.h"
#include "typedef.h"

/*******************************************************************************
* Global Variables                                                             *
*******************************************************************************/

extern bool g_fullScreen;

extern T_RoleData g_roleData;

extern EmInGame g_inGame;

/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/

void* LoadFile(char* filename, void* buffer, size_t size);

T_Position GetMapScenceXYPos(int mx, int my, int cx, int cy);

void RedrawWithoutUpdate();
void Redraw();

int WaitKey();
int PollKey();
int InScence(int scence, EmInScence inScence);

#endif //__GAME_H__
