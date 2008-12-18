/*******************************************************************************
* const.h                                                   fileencoding=UTF-8 *
*******************************************************************************/

/*******************************************************************************
* 原作者的话：                                                                 *
*                                                                              *
* All Heros in Kam Yung's Stories - The Replicated Edition                     *
*                                                                              *
* Created by S.weyl in 2008 May.                                               *
* No Copyright (C) reserved.                                                   *
*                                                                              *
* You can build it by Delphi with JEDI-SDL support.                            *
*                                                                              *
* This resouce code file which is not perfect so far,                          *
* can be modified and rebuilt freely,                                          *
* or translate it to another programming language.                             *
* But please keep this section when you want to spread a new vision. Thanks.   *
* Note: it must not be a good idea to use this as a pascal paradigm.           *
*                                                                              *
* 任何人获得这份代码之后，均可以自由增删功能，重新编译，或译为其他语言。       *
* 但请保留本段文字。                                                           *
*                                                                              *
* ---------------------------------------------------------------------------- *
*                                                                              *
* 我的话：不保留一切权力，不承担一切责任。不署名。                             *
*******************************************************************************/

/*******************************************************************************
* Graphic                                                                      *
*******************************************************************************/

//#define HAN_FONT	"font/kaiu.ttf"
#define HAN_FONT	"font/ukai.ttf"
#define ENG_FONT	"font/consola.ttf"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define CELL_WIDTH		36
#define CELL_HEIGHT		(CELL_WIDTH / 2)

#define BIG_PIC_WIDTH	320
#define BIG_PIC_HEIGHT	200
#define BIG_PIC_SIZE	(BIG_PIC_WIDTH * BIG_PIC_HEIGHT)

#define SCENCE_PIC_WIDTH	(SCENCE_WIDTH * CELL_WIDTH)
#define SCENCE_PIC_HEIGHT	(SCENCE_HEIGHT * CELL_HEIGHT)

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

#define FACE_PIC_W	56
#define FACE_PIC_H	58
#define NAME_OFFSET	10

#define TEXT_COLOR			0x23
#define TEXT_NORMAL_COLOR	0x07
#define TEXT_FATAL_COLOR	0x16
#define TEXT_SERIOUS_COLOR	0x10
#define TEXT_YIN_COLOR		0x50
#define TEXT_YANG_COLOR		TEXT_NORMAL_COLOR
#define TEXT_UNIFIED_COLOR	0x66

/*******************************************************************************
* In Game                                                                      *
*******************************************************************************/

#define TEXT_BIG5_LEN	1024
#define TEXT_UTF8_LEN	(TEXT_BIG5_LEN * 4)

#define NAME_LEN		20
#define NAME_UTF8_LEN	(NAME_LEN * 4)

#define ITEM_BEGIN_PIC			3501	//物品起始图片
#define BEGIN_EVENT				691		//初始事件
#define BEGIN_SCENCE			70		//初始场景
#define BEGIN_SX				20		//初始坐标(程序中的x, y与游戏中是相反的, 这是早期的遗留问题)
#define BEGIN_SY				19		//初始坐标
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

#define MAX_ITEM_NUM			200		//最大物品数量
#define MAX_ROLE_NUM			320
#define SCENCE_NUM				84
#define MAX_MAGIC_NUM			93
#define MAX_SHOP_NUM			5

#define SCENCE_WIDTH			64
#define SCENCE_HEIGHT			SCENCE_WIDTH

#define SCENCE_EVENT_NUM		200

#define MAP_WIDTH				480
#define MAP_HEIGHT				MAP_WIDTH

#define MAX_HP					999		//最大生命
#define MAX_MP					999		//最大内功
#define LIFE_HURT				10		//伤害值比例
#define NOVEL_BOOK				144		//天书起始编码
#define MAX_HEAD_NUM			189		//有专有头像的最大人物编号, 仅用于对话指令
#define BEGIN_WALKPIC			2500	//起始的行走贴图

#define FRAME_TEXT_ALPHA		30

#define MAX_PRO_LIST_OFFSET		43

#define WOUND_SERIOUS	33
#define WOUND_FATAL		66
