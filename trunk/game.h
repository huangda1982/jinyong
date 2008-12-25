/*******************************************************************************
* func.h                                                    fileencoding=UTF-8 *
*******************************************************************************/

#include "claim.h"

#ifndef __FUNC_H__
#define __FUNC_H__

/*******************************************************************************
* Global Variables                                                             *
*******************************************************************************/

//默认调色板数据
extern T_RGB g_palette[256];

extern SDL_Surface* g_screenSurface;

extern T_RoleData g_roleData;

extern EmInGame g_inGame;

/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/

void DrawScenceOnScreen(int x, int y);
void UpdateScreen();

T_Position GetMapScenceXYPos(int mx, int my, int cx, int cy);

void DrawPic(SDL_Surface* destSurface, int index, int x, int y, uint32* idxBuffer, byte* picBuffer, int highlight);
#define DrawPicOnScreen(index, x, y, idxBuffer, picBuffer, highlight) \
	DrawPic(g_screenSurface, (index), (x), (y), (idxBuffer), (picBuffer), (highlight))

#endif //__FUNC_H__
