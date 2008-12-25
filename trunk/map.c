/*******************************************************************************
* map.c                                                     fileencoding=UTF-8 *
*******************************************************************************/

#include "claim.h"

/*******************************************************************************
* Headers                                                                      *
*******************************************************************************/

#include <limits.h>
#include <iconv.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "const.h"
#include "typedef.h"
#include "map.h"
#include "game.h"
#include "cmd.h"

/*******************************************************************************
* Global Variables                                                             *
*******************************************************************************/

//贴图的内容及索引
uint32* g_mapIdxBuff = NULL;
byte* g_mapPicBuff = NULL;

//主地图数据
sint16 g_map[MAP_WIDTH][MAP_HEIGHT] = {{0}};
sint16 g_ground[MAP_WIDTH][MAP_HEIGHT] = {{0}};
sint16 g_building[MAP_WIDTH][MAP_HEIGHT] = {{0}};
sint16 g_buildingX[MAP_WIDTH][MAP_HEIGHT] = {{0}};
sint16 g_buildingY[MAP_WIDTH][MAP_HEIGHT] = {{0}};

sint16 g_entrances[MAP_WIDTH][MAP_HEIGHT] = {{0}};

//步数，休息动画，船动画
int g_mStep = 0;
int g_mRest = 0;
int g_mShip = 0;

bool g_ship = FALSE;

/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/

//初始化入口
void InitialMapEntrances()
{
	memset(g_entrances, 0xff, sizeof(g_entrances));
	int i;
	for (i = 0; i < SCENCE_NUM; i++) {
		g_entrances[g_roleData.scences[i].mapEntrance1X][g_roleData.scences[i].mapEntrance1Y] = i;
		g_entrances[g_roleData.scences[i].mapEntrance2X][g_roleData.scences[i].mapEntrance2Y] = i;
	}
}

//判定主地图某个位置能否行走, 是否变成船
bool GoThroughMap(int mx, int my)
{
	bool GoThroughMap = FALSE;

	if (mx >= 0 && mx < MAP_WIDTH && my >= 0 && my < MAP_HEIGHT) {
		GoThroughMap = g_buildingX[mx][my] == 0;
		GoThroughMap &= g_map[mx][my] != 838;
		GoThroughMap &= g_map[mx][my] < 621 || g_map[mx][my] > 670;
	}

	g_ship = g_map[mx][my] >= 358 && g_map[mx][my] <= 362;
	g_ship |= g_map[mx][my] >= 506 && g_map[mx][my] <= 670;
	g_ship |= g_map[mx][my] >= 1016 && g_map[mx][my] <= 1022;

	return GoThroughMap;
}

//检测是否处于某入口, 并是否达成进入条件
bool GoIn(int mx, int my)
{
	bool goIn = FALSE;

	int scence = -1;
	if ((scence = g_entrances[mx][my] >= 0)) {
		if ((g_roleData.scences[scence].enCondition == 0)) {
			goIn = TRUE;
		} else if ((g_roleData.scences[scence].enCondition == 2)) { //是否有人轻功超过70
			int i;
			for (i = 0; i < MAX_TEAM_ROLE; i++) {
				if (g_roleData.common.team[i] >= 0 && g_roleData.roles[g_roleData.common.team[i]].speed > 70) {
					goIn = TRUE;
					break;
				}
			}
		}
	}

	return goIn;
}

//显示主地图贴图
void DrawMapPic(int index, int x, int y)
{
	DrawPicOnScreen(index, x, y, g_mapIdxBuff, g_mapPicBuff, 0);
}

void DrawMapWithoutUpdate()
{
	int mx;
	int my;
	int cx = g_mx;
	int cy = g_my;

	for (my = 0; my < MAP_HEIGHT; my++) {
		for (mx = 0; mx < MAP_WIDTH; mx++) {
			T_Position pos = GetMapScenceXYPos(mx, my, cx, cy);
			if ((pos.x + CELL_WIDTH >= 0 && pos.x < SCREEN_WIDTH + CELL_WIDTH)
				&& (pos.y + CELL_HEIGHT >= 0 && pos.y < SCREEN_HEIGHT + CELL_HEIGHT)) {
				DrawMapPic(g_map[mx][my] / 2, pos.x, pos.y);

				if (g_ground[mx][my] > 0) {
					DrawMapPic(g_ground[mx][my] / 2, pos.x, pos.y);
				}
			}
		}
	}

	for (my = 0; my < MAP_HEIGHT; my++) {
		for (mx = 0; mx < MAP_WIDTH; mx++) {
			T_Position pos = GetMapScenceXYPos(mx, my, cx, cy);
			if ((pos.x + CELL_WIDTH >= 0 && pos.x < SCREEN_WIDTH + CELL_WIDTH)
				&& (pos.y + CELL_HEIGHT >= 0 && pos.y < SCREEN_HEIGHT + CELL_HEIGHT)) {
				if (g_building[mx][my] > 0) {
					DrawMapPic(g_building[mx][my] / 2, pos.x, pos.y);
				}

				if (mx == g_mx && my == g_my) {
					if (g_ship) {
						DrawMapPic(SHIP_PIC_OFFSET + g_mFace * SHIP_PIC_NUM + g_mShip, pos.x, pos.y);
					} else if (g_mStep || !g_mRest) {
						DrawMapPic(WALK_PIC_OFFSET + g_mFace * WALK_PIC_NUM + g_mStep, pos.x, pos.y);
					} else {
						DrawMapPic(REST_PIC_OFFSET + g_mFace * REST_PIC_NUM + (g_mRest - 1), pos.x, pos.y);
					}
				}
			}
		}
	}
#if 0
	int   i1 = 0;
	int  i2 = 0;
	int  i = 0;
	int  sum = 0;
	int  x = 0;
	int y = 0;
	sint16 temp[MAP_WIDTH][MAP_HEIGHT];
	T_Position pos;

	//由上到下绘制, 先绘制中心点靠上的建筑
	for (sum = -29; sum < 41; sum++) {
		for (i = -15; i < 16; i++) {
			i1 = g_mx + i + (sum / 2);
			i2 = g_my - i + (sum - sum / 2);
			pos = GetMapScenceXYPos(i1, i2, g_mx, g_my);
			if ((i1 >= 0) && (i1 < 480) && (i2 >= 0) && (i2 < 480))
			{
				if ((sum >= -27) && (sum <= 28) && (i >= -9) && (i <= 9))
				{
					DrawMapPic(g_map[i1][i2] / 2, pos.x, pos.y);
					if (g_ground[i1][i2] > 0)
						DrawMapPic(g_ground[i1][i2] / 2, pos.x, pos.y);
				}
				temp[i1][i2] = g_building[i1][i2];
			} else {
				DrawMapPic(0, pos.x, pos.y);
			}
		}
	}

#if 0
	for sum = -29 to 40 do
		for i = -15 to 15 do
		{
			i1 = g_mx + i + (sum / 2);
			i2 = g_my - i + (sum - sum / 2);
			if ((i1 >= 0) && (i1 < 480) && (i2 >= 0) && (i2 < 480))
			{
				x = g_buildingY[i1, i2];
				y = g_buildingX[i1, i2];
				Pos = GetMapScenceXYPos(x, y, g_mx, g_my);
				if ((g_buildingX[i1, i2] > 0 && g_buildingX[i1 - 1, i2 - 1] <> g_buildingX[i1, i2] && g_buildingX[i1 + 1, i2 + 1] <> g_buildingX[i1, i2]) || (g_buildingY[i1 - 1, i2 - 1] <> g_buildingY[i1, i2] && g_buildingY[i1 + 1, i2 + 1] <> g_buildingY[i1, i2])) then
				{

					if (temp[x, y] > 0)
					{
						DrawMapPic(g_building[x, y] / 2, pos.x, pos.y);
						temp[x, y] = 0;
					}
				}

				//如在水面上则绘制船的贴图
				if ((i1 == g_mx) && (i2 == g_my))
					if ((g_ship == 0))
						if (g_mStep)
							DrawMapPic(WALK_PIC_OFFSET + g_mFace * WALK_PIC_NUM + g_mStep, SCREEN_CENTER_X, SCREEN_CENTER_Y)
						else
							DrawMapPic(2528 + g_mFace * 6 + g_mStep, SCREEN_CENTER_X, SCREEN_CENTER_Y)
					else
						DrawMapPic(3714 + g_mFace * 4 + (g_mStep + 1) / 2, SCREEN_CENTER_X, SCREEN_CENTER_Y);
				if ((temp[i1, i2] > 0) && (g_buildingX[i1, i2] == i2))
				{
					DrawMapPic(g_building[i1, i2] / 2, pos.x, pos.y);
					temp[i1, i2] = 0;
				}
			}

		}
#endif

	//SDL_UpdateRect(g_screenSurface, 0,0,g_screenSurface.w,g_screenSurface.h);
#endif
}

//显示主地图场景于屏幕
void DrawMap()
{
	DrawMapWithoutUpdate();
	UpdateScreen();
}

//于主地图行走
void InMap()
{
	uint32 next_time = SDL_GetTicks() + 3000;
	g_inGame = EmInGameMap;

	g_mStep = 0;
	g_mRest = 0;
	g_mShip = 0;

	CmdScreenFadeIn(NULL);

	//PlayMp3(16, -1);

	//事件轮询(并非等待)
	while (TRUE) {
		//如果当前处于标题画面, 则退出, 用于战斗失败
		//***********

		int mx = g_mx;
		int my = g_my;
		switch (g_mFace) {
			case 0:
				mx--;
				break;
			case 1:
				my++;
				break;
			case 2:
				my--;
				break;
			case 3:
				mx++;
				break;
			default:
				break;
		}

		if (GoIn(mx, my)) {
			CmdScreenFadeOut(NULL);
			InScence(g_entrances[mx][my], EmInScenceEnter);
			g_inGame = EmInGameMap;

			g_mStep = 0;
			g_mRest = 0;
			g_mShip = 0;

			CmdScreenFadeIn(NULL);
		}

		//主地图动态效果, 实际仅有主角的动作
		uint32 now = SDL_GetTicks();
		if (now > next_time) {
			if (g_mStep || ++g_mRest >= REST_PIC_NUM + 1) {
				g_mRest = 0;
				next_time = now + 3000;
			} else {
				next_time = now + 500;
			}
		}

		DrawMap();

		int key = PollKey();
		switch (key) {
			case KEYUP:
				g_mStep = 0;
				g_mShip = 0;
				break;
			case SDLK_UP:
				g_mFace = 0;
				if (++g_mStep >= WALK_PIC_NUM) g_mStep = 1;
				if (++g_mShip >= SHIP_PIC_NUM) g_mShip = 1;

				if (GoThroughMap(g_mx - 1, g_my)) {
					g_mx--;
				}
				break;
			case SDLK_RIGHT:
				g_mFace = 1;
				if (++g_mStep >= WALK_PIC_NUM) g_mStep = 1;
				if (++g_mShip >= SHIP_PIC_NUM) g_mShip = 1;

				if (GoThroughMap(g_mx, g_my + 1)) {
					g_my++;
				}
				break;
			case SDLK_LEFT:
				g_mFace = 2;
				if (++g_mStep >= WALK_PIC_NUM) g_mStep = 1;
				if (++g_mShip >= SHIP_PIC_NUM) g_mShip = 1;

				if (GoThroughMap(g_mx, g_my - 1)) {
					g_my--;
				}
				break;
			case SDLK_DOWN:
				g_mFace = 3;
				if (++g_mStep >= WALK_PIC_NUM) g_mStep = 1;
				if (++g_mShip >= SHIP_PIC_NUM) g_mShip = 1;

				if (GoThroughMap(g_mx + 1, g_my)) {
					g_mx++;
				}
				break;
			case SDLK_ESCAPE:
				//***MenuEsc;
				break;
			default:
				break;
		}
	}
}
