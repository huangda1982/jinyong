/*******************************************************************************
* const.h                                                   fileencoding=UTF-8 *
*******************************************************************************/

#include "claim.h"

#ifndef __CONST_H__
#define __CONST_H__

/*******************************************************************************
* Graphic                                                                      *
*******************************************************************************/

#define HAN_FONT	"font/bkai00mp.ttf"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define CELL_WIDTH		36
#define CELL_HEIGHT		(CELL_WIDTH / 2)

#define BIG_PIC_WIDTH	320
#define BIG_PIC_HEIGHT	200
#define BIG_PIC_SIZE	(BIG_PIC_WIDTH * BIG_PIC_HEIGHT)

#define SCENCE_PIC_WIDTH	((SCENCE_HEIGHT + SCENCE_WIDTH) * CELL_WIDTH / 2)
#define SCENCE_PIC_HEIGHT	((SCENCE_WIDTH + SCENCE_HEIGHT) * CELL_HEIGHT / 2)

#define MAP_PIC_WIDTH	((MAP_HEIGHT + MAP_WIDTH) * CELL_WIDTH / 2)
#define MAP_PIC_HEIGHT	((MAP_WIDTH + MAP_HEIGHT) * CELL_HEIGHT / 2)

#define RECTANGLE_D	5
#define RECTANGLE_N	8

#define STATUS_FRAME_X	40
#define STATUS_FRAME_Y	40
#define STATUS_FRAME_W	560
#define STATUS_FRAME_H	400

#define STATUS_TEXT_TOP_X	80
#define STATUS_TEXT_LEFT_Y	65

#define STATUS_TEXT_W	80
#define STATUS_TEXT_H	25

#define STATUS_TEXT_X(x)	(STATUS_TEXT_TOP_X + STATUS_TEXT_W * (x))
#define STATUS_TEXT_Y(y)	(STATUS_TEXT_LEFT_Y + STATUS_TEXT_H * (y))

#define STATUS_NUM_FORMAT_1	"%7d"
#define STATUS_NUM_FORMAT_2	"%3d"
#define STATUS_NUM_FORMAT_3	"/%3d"
#define STATUS_NUM_FORMAT_4	"%3d/%3d"

#define STATUS_FACE_X	100
#define STATUS_FACE_Y	80 + FACE_PIC_H

#define STATUS_NAME_X	STATUS_FACE_X
#define STATUS_NAME_Y	STATUS_FACE_Y + 10

#define FACE_PIC_W	56
#define FACE_PIC_H	58

#define TEXT_COLOR			0x23
#define TEXT_NORMAL_COLOR	0x07
#define TEXT_FATAL_COLOR	0x16
#define TEXT_SERIOUS_COLOR	0x10
#define TEXT_YIN_COLOR		0x50
#define TEXT_YANG_COLOR		TEXT_NORMAL_COLOR
#define TEXT_UNIFIED_COLOR	0x66

#define FRAME_TEXT_ALPHA		0x4f
#define FRAME_TEXT_PADDING		5

/*******************************************************************************
* Input                                                                        *
*******************************************************************************/

#define KEY_REPEAT_DELAY	200
#define KEY_REPEAT			30

#define KEYUP	-1

/*******************************************************************************
* In Game                                                                      *
*******************************************************************************/

#define TEXT_BIG5_LEN	1024
#define TEXT_UTF8_LEN	(TEXT_BIG5_LEN * 4)

#define NAME_LEN		20
#define NAME_UTF8_LEN	(NAME_LEN * 4)

#define ITEM_BEGIN_PIC			3501	//物品起始图片
#define SOFTSTAR_BEGIN_TALK		2547	//软体娃娃对话的开始编号
#define SOFTSTAR_NUM_TALK		18		//软体娃娃的对话数量
#define MAX_PHYSICAL_POWER		100		//最大体力
#define MONEY_ID				174		//银两的物品代码
#define COMPASS_ID				182		//罗盘的物品代码
#define BEGIN_LEAVE_EVENT		950		//起始离队事件
#define BEGIN_BATTLE_ROLE_PIC	2553	//人物起始战斗贴图
#define MAX_LEVEL				30		//最大等级
#define MAX_WEAPON_MATCH		7		//"武功与武器配合"的组合数量
#define MIN_KNOWLEDGE			80		//最低有效武学常识

#define ITEM_NUM	200		//最大物品数量
#define ROLE_NUM	320
#define SCENCE_NUM	84
#define MAGIC_NUM	93
#define SHOP_NUM	5

#define MAX_TEAM_ROLE	6

#define SCENCE_WIDTH			64
#define SCENCE_HEIGHT			SCENCE_WIDTH

#define SCENCE_EVENT_NUM		200

#define MAP_WIDTH				480
#define MAP_HEIGHT				MAP_WIDTH

#define MAX_HP					999		//最大生命
#define MAX_MP					999		//最大内功
#define LIFE_HURT				10		//伤害值比例
#define THE_BOOKS_OFFSET		144		//天书起始编码
#define MAX_HEAD_NUM			189		//有专有头像的最大人物编号, 仅用于对话指令

#define WALK_PIC_OFFSET	2501	//起始的行走贴图
#define WALK_PIC_NUM	7

#define REST_PIC_OFFSET	2529	//起始的休息贴图
#define REST_PIC_NUM	6

#define SHIP_PIC_OFFSET	3715	//起始的行船贴图
#define SHIP_PIC_NUM	4

#define MAX_PRO_LIST_OFFSET	43

#define WOUND_SERIOUS	33
#define WOUND_FATAL		66

#define MAGIC_MAX_NUM	10
#define MAGIC_MAX_LEVEL	10

#define MAGIC_NEXT_EXP_NA		-1
#define MAGIC_NEXT_EXP_NOTHING	0

#define EVENT_NOTHING		-1
#define EVENT_GAME_START	691		//初始事件

#define SCENCE_HOME			70		//初始场景
#define SCENCE_EXIT			-1

#define GAME_START_SX	20		//初始坐标(程序中的x, y与游戏中是相反的, 这是早期的遗留问题)
#define GAME_START_SY	19		//初始坐标

#endif //__CONST_H__
