/*******************************************************************************
* jinyong.c                                                 fileencoding=UTF-8 *
*******************************************************************************/

#include "claim.h"

/*******************************************************************************
* Headers                                                                      *
*******************************************************************************/

#include "draw.h"
#include "game.h"

#include "cmd.h"

/*******************************************************************************
* Functions                                                                    *
*******************************************************************************/

//Event.
//事件系统
const void *CMD_FUNCS(sint16**) = {
	CmdRedraw();
};

void CallEvent(int event)
	var
	e: array of smallint;
	int   i = 0;
	int  idx = 0;
	int  grp = 0;
	int  offset = 0;
	int  length = 0;
	int p = 0;
check: boolean;
{
	byte* cmdBuffer = NULL;

	//g_curEvent=num;
	g_ex = g_sx;
	g_ey = g_sy;
	g_sStep = 0;
	
	if (event) {
		cmdBuffer = g_cmdGrpBuff + *(g_cmdIdxBuff + event - 1);
	} else {
		cmdBuffer = g_cmdGrpBuff;
	}

	sint16* cmd = cmdBuffer;
	while (*cmd >= 0 && *cmd <= sizeof(CMD_FUNCS) / sizeof (void *(sint16**))) {
		(*CMD_FUNCS[*cmd])(cmd);
	}

	event.key.keysym.sym = 0;
	event.button.button = 0;

	InitialScence;
	Redraw();
}

//事件指令含义请参阅其他相关文献
void CmdRedraw(sint16** cmd)
{
	if (cmd) (*cmd)++;
	Redraw();
}

void CmdTalk(sint16** cmd)
{
	(*cmd)++;
	int talkIndex = *((*cmd)++);
	int faceIndex = *((*cmd)++);
	int disMode = *((*cmd)++);

	switch (dismode) {
		case 0:
			headx = 40;
			heady = 80;
			diagx = 100;
			diagy = 30;
			break;
		case 1:
			headx = 546;
			heady = SCREEN_CENTER_Y * 2 - 80;
			diagx = 10;
			diagy = SCREEN_CENTER_Y * 2 - 130;
			break;
		case 2:
			headx = -1;
			heady = -1;
			diagx = 100;
			diagy = 30;
			break;
		case 5:
			headx = 40;
			heady = SCREEN_CENTER_Y * 2 - 80;
			diagx = 100;
			diagy = SCREEN_CENTER_Y * 2 - 130;
			break;
		case 4:
			headx = 546;
			heady = 80;
			diagx = 10;
			diagy = 30;
			break;
		case 3:
			headx = -1;
			heady = -1;
			diagx = 100;
			diagy = SCREEN_CENTER_Y * 2 - 130;
			break;
	}
	idx = fileopen("talk.idx", fmopenread);
	grp = fileopen("talk.grp", fmopenread);
	if (talknum == 0)
	{
		offset = 0;
		fileread(idx, len, 4);
	}
	else
	{
		fileseek(idx, (talknum - 1) * 4, 0);
		fileread(idx, offset, 4);
		fileread(idx, len, 4);
	}
	len = (len - offset);
	setlength(talkarray, len + 1);
	fileseek(grp, offset, 0);
	fileread(grp, talkarray[0], len);
	fileclose(idx);
	fileclose(grp);
	DrawRectangle(0, diagy - 10, 640, 120, 0, 40);
	if (headx > 0) DrawFacePic(headnum, headx, heady);
	//if (headnum <= MAX_HEAD_NUM)
	//{
	//name = Big5toUTF8(@rrole[headnum].Name);
	//drawshadowtext(@name[1], headx + 20 - length(name) * 10, heady + 5, COLOR(0xff), COLOR(0x0));
	//}
	for i = 0 to len - 1 do
	{
		talkarray[i] = talkarray[i] xor 0xFF;
		if ((talkarray[i] == 0x2A))
			talkarray[i] = 0;
	}
	p = 0;
	l = 0;
	for i = 0 to len do
	{
		if (talkarray[i] == 0)
		{
			drawbig5shadowtext(@talkarray[p], diagx, diagy + l * 22, COLOR(0xFF), COLOR(0x0));
			p = i + 1;
			l = l + 1;
			if ((l >= 4) && (i < len))
			{
				sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
				WaitKey;
				Redraw;
				DrawRectangle(0, diagy - 10, 640, 120, 0, 40);
				if (headx > 0) DrawFacePic(headnum, headx, heady);
				l = 0;
			}
		}
	}
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;

	*/
}

//得到物品可显示数量, 数量为负显示失去物品
void CmdItemGetLost(sint16** cmd)
{
	(*cmd)++;
	int item = *((*cmd)++);
	int num = *((*cmd)++);

	int i;
	for (i = 0; g_roleData.itmes[i].index >= 0 && i < MAX_ITEM_NUM; i++) {
		if (g_roleData.itmes[i].index == item) {
			g_roleData.items[i].num += num;
			if (g_roleData.items[i].num < 0 && num >= 0) g_roleData.items[i].num = 32767;
			if (g_roleData.items[i].num < 0 && num < 0) g_roleData.items[i].num = 0;
			break;
		}
	}

	if (g_roleData.items[i].number < 0)
	{
		g_roleData.items[i].Number = inum;
		g_roleData.items[i].num =.num;
	}

	ReArrangeItem;

	x = SCREEN_CENTER_X;
	if (g_inGame == 2) x = 190;

	DrawFrameRectangle(x - 75, 98, 145, 76, 0, COLOR(255), 30);
	if .num >= 0)
		word = " 得到物品"
	else
		word = " 失去物品";
	drawshadowtext(@word[1], x - 90, 100, COLOR(0x23), COLOR(0x21));
	drawbig5shadowtext(@RItem[inum].Name, x - 90, 125, COLOR(0x7), COLOR(0x5));
	word = " 數量";
	drawshadowtext(@word[1], x - 90, 150, COLOR(0x66), COLOR(0x64));
	word = format(" %5d", .num]);
	drawengshadowtext(@word[1], x - 5, 150, COLOR(0x66), COLOR(0x64));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);

}
//改变事件, 如在当前场景需重置场景
//在需改变贴图较多时效率较低
void instruct_3(list: array of integer)()
	var
	int   i = 0;
	int  i1 = 0;
	int i2 = 0;
{
	if (cmd) *((*cmd)++);

	if (list[0] == -2) list[0] = g_curScence;
	if (list[1] == -2) list[1] = g_curEvent;
	if (list[11] == -2) list[11] = g_scenceEventData[list[0], list[1], 9];
	if (list[12] == -2) list[12] = g_scenceEventData[list[0], list[1], 10];
	//这里应该是原本z文件的bug, 如果不处于当前场景, 在连坐标值一起修改时, 并不会同时
	//对S数据进行修改. 而<苍龙逐日>中有几条语句无意中符合了这个bug而造成正确的结果
	//if (list[0] == g_curScence)
	g_scenceData[list[0], 3, g_scenceEventData[list[0], list[1], 10], g_scenceEventData[list[0], list[1], 9]] = -1;
	for i = 0 to 10 do
	{
		if (list[2 + i] <> -2)
		{
			g_scenceEventData[list[0], list[1], i] = list[2 + i];
		}
	}
	//if (list[0] == g_curScence)
	g_scenceData[list[0], 3, g_scenceEventData[list[0], list[1], 10], g_scenceEventData[list[0], list[1], 9]] = list[1];
	//if (list[0] == g_curScence)
	//UpdateScence(list[12], list[11]);

}

//是否使用了某剧情物品

int function instruct_4(inum = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
{
	if (inum == CurItem)
		result = jump1
	else
		result = jump2;

}

//询问是否战斗

int function instruct_5(jump1 = 0;
		int jump2 = 0int ) = 0;
var
int menu = 0;
{
	setlength(menustring, 3);
	menustring[0] = " 取消";
	menustring[1] = " 戰鬥";
	menustring[2] = " 是否與之戰鬥？";
	drawtextwithrect(@menustring[2][1], SCREEN_CENTER_X - 75, SCREEN_CENTER_Y - 85, 150, COLOR(7), COLOR(5));
	menu = commonmenu2(SCREEN_CENTER_X - 49, SCREEN_CENTER_Y - 50, 98);
	if (menu == 1) result = jump1 else result = jump2;
	redraw;
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);

}

//战斗

int function instruct_6(battlenum = 0;
		int  jump1 = 0;
		int  jump2 = 0;
		int getexp = 0int ) = 0;
{
	result = jump2;
	if (Battle(battlenum, getexp))
		result = jump1;

}

//询问是否加入

void int instruct_8(musicnum = 0)()
{
	exitscencemusicnum = musicnum;
}

int function instruct_9(jump1 = 0;
		int jump2 = 0int ) = 0;
var
int menu = 0;
{
	setlength(menustring, 3);
	menustring[0] = " 取消";
	menustring[1] = " 要求";
	menustring[2] = " 是否要求加入？";
	drawtextwithrect(@menustring[2][1], SCREEN_CENTER_X - 75, SCREEN_CENTER_Y - 85, 150, COLOR(7), COLOR(5));
	menu = commonmenu2(SCREEN_CENTER_X - 49, SCREEN_CENTER_Y - 50, 98);
	if (menu == 1) result = jump1 else result = jump2;
	redraw;
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);

}

//加入队友, 同时得到其身上物品

void int instruct_10(rnum = 0)()
	var
	int   i = 0;
	int i1 = 0;
{
	for i = 0 to 5 do
	{
		if (Teamlist[i] < 0)
		{
			Teamlist[i] = rnum;
			for i1 = 0 to 3 do
			{
				if ((Rrole[rnum].TakingItem[i1] >= 0) && (Rrole[rnum].TakingItemAmount[i1] > 0))
				{
					instruct_2(Rrole[rnum].TakingItem[i1], Rrole[rnum].TakingItemAmount[i1]);
					Rrole[rnum].TakingItem[i1] = -1;
					Rrole[rnum].TakingItemAmount[i1] = 0;
				}
			}
			break;
		}
	}

}

//询问是否住宿

int function instruct_11(jump1 = 0;
		int jump2 = 0int ) = 0;
var
int menu = 0;
{
	setlength(menustring, 3);
	menustring[0] = " 否";
	menustring[1] = " 是";
	menustring[2] = " 是否需要住宿？";
	drawtextwithrect(@menustring[2][1], SCREEN_CENTER_X - 75, SCREEN_CENTER_Y - 85, 150, COLOR(7), COLOR(5));
	menu = commonmenu2(SCREEN_CENTER_X - 49, SCREEN_CENTER_Y - 50, 98);
	if (menu == 1) result = jump1 else result = jump2;
	redraw;
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);

}
#endif

//住宿
void CmdSleep(sint16** cmd) //12
{
	if (cmd) *((*cmd)++);

	int i;
	for (i = 0; i < MAX_TEAM_ROLE; i++) {
		int role = g_roleData.common.team[i];
		if (g_roleData.roles[role].wound < WOUND_SERIOUS && g_roleData.roles[role].poisioning == 0) {
			g_roleData.roles[role].life = g_roleData.roles[role].maxLife;
			g_roleData.roles[role].neili = g_roleData.roles[role].maxNeili;
			g_roleData.roles[role].phyPower = MAX_PHYSICAL_POWER;
		}
	}
}

//亮屏
void CmdScreenFadeIn(sint16** cmd) //13
{
	if (cmd) *((*cmd)++);

	int i;
	for (i = 0xff; i > 0; i -= 0x0f) {
		RedrawWithoutUpdate();
		DrawRectangle(0, 0, g_screenSurface->w, g_screenSurface->h, 0, i);
		UpdateScreen();
	}

	RedrawWithoutUpdate();
	UpdateScreen();
}

//黑屏
void CmdScreenFadeOut(sint16** cmd) //14
{
	if (cmd) *((*cmd)++);

	int i;
	for (i = 0; i < 0xff; i += 0x0f) {
		RedrawWithoutUpdate();
		DrawRectangle(0, 0, g_screenSurface->w, g_screenSurface->h, 0, i);
		UpdateScreen();
	}

	DrawRectangle(0, 0, g_screenSurface->w, g_screenSurface->h, 0, 0xff);
	UpdateScreen();
}

#if 0

//失败画面

void instruct_15()
	var
	int i = 0;
str: widestring;
{
	g_inGame = 3;
	redraw;
	str = " 勝敗乃兵家常事，但是…";
	drawshadowtext(@str[1], 50, 330, COLOR(255), COLOR(255));
	str = " 地球上又多了一失蹤人口";
	drawshadowtext(@str[1], 50, 360, COLOR(255), COLOR(255));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
}

int function instruct_16(rnum = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
var
int i = 0;
{
	result = jump2;
	for i = 0 to 5 do
	{
		if (Teamlist[i] == rnum)
		{
			result = jump1;
			break;
		}
	}
}

void instruct_17(list: array of integer)()
	var
	int   i1 = 0;
	int i2 = 0;
{
	if (list[0] == -2) list[0] = g_curScence;
	g_scenceData[list[0], list[1], list[3], list[2]] = list[4];

}

int function instruct_18(inum = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
var
int i = 0;
{
	result = jump2;
	for i = 0 to MAX_ITEM_NUM - 1 do
	{
		if (RItemList[i].Number == inum)
		{
			result = jump1;
			break;
		}
	}
}

void instruct_19(x, int y = 0)()
{
	Sx = y;
	Sy = x;
	g_ex = Sx;
	g_ey = Sy;
	Redraw;
}

//Judge the team is full || not.

int function instruct_20(jump1 = 0;
		int jump2 = 0int ) = 0;
var
int i = 0;
{
	result = jump1;
	for i = 0 to 5 do
	{
		if (TeamList[i] < 0)
		{
			result = jump2;
			break;
		}
	}
}

void int instruct_21(rnum = 0)()
	var
	int   i = 0;
	int p = 0;
newlist: array[0..5] of integer;
{
	p = 0;
	for i = 0 to 5 do
	{
		newlist[i] = -1;
		if (Teamlist[i] <> rnum)
		{
			newlist[p] = Teamlist[i];
			p = p + 1;
		}
	}
	for i = 0 to 5 do
		Teamlist[i] = newlist[i];
}

void instruct_22()
	var
	int i = 0;
{
	for i = 0 to 5 do
		RRole[Teamlist[i]].CurrentMP = 0;
}

void instruct_23(rnum, int Poision = 0)()
{
	RRole[rnum].UsePoi = Poision;
}

//Black the g_screenSurface when fail in battle.
//Note: never be used, leave it as blank.

void instruct_24()
{
}

//Note: never display the leading role.
//This will be improved when I have a better method.

void instruct_25(x1, y1, x2, int y2 = 0)()
	var
	int   i = 0;
	int s = 0;
{
	s = sign(x2 - x1);
	i = x1 + s;
	//showmessage(inttostr(ssx*100+ssy));
	if (s <> 0)
		while s * (x2 - i) >= 0 do
		{
			sdl_delay(50);
			DrawScenceWithoutRole(y1, i);
			//showmessage(inttostr(i));
			DrawRoleOnScence(y1, i);
			SDL_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
			i = i + s;
			//showmessage(inttostr(s*(x2-i)));
		}
	s = sign(y2 - y1);
	i = y1 + s;
	if (s <> 0)
		while s * (y2 - i) >= 0 do
		{
			sdl_delay(50);
			DrawScenceWithoutRole(i, x2);
			//showmessage(inttostr(i));
			DrawRoleOnScence(i, x2);
			//Redraw;
			SDL_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
			i = i + s;
		}
	g_ex = y2;
	g_ey = x2;
	//SSx=0;
	//SSy=0;
	//showmessage(inttostr(ssx*100+ssy));
}

void instruct_26(snum, enum, add1, add2, int add3 = 0)()
{
	if (snum == -2) snum = g_curScence;
	g_scenceEventData[snum, enum, 2] = g_scenceEventData[snum, enum, 2] + add1;
	g_scenceEventData[snum, enum, 3] = g_scenceEventData[snum, enum, 3] + add2;
	g_scenceEventData[snum, enum, 4] = g_scenceEventData[snum, enum, 4] + add3;

}

//Note: of course an more effective engine can take place of it.
//动画, 至今仍不完善

void instruct_27(enum, beginpic, int endpic = 0)()
	var
	int   i = 0;
	int  xpoint = 0;
	int ypoint = 0;
AboutMainRole: boolean;
{
	AboutMainRole = false;
	if (enum == -1)
	{
		enum = g_curEvent;
		if (g_curScenceData[ 3, Sx, Sy] >= 0)
			enum = g_curScenceData[ 3, Sx, Sy];
		AboutMainRole = true;
	}
	if (enum == g_curScenceData[ 3, Sx, Sy]) AboutMainRole = true;
	g_curScenceData[ 3, g_curScenceEventData[ enum, 10], g_curScenceEventData[ enum, 9]] = enum;
	for i = beginpic to endpic do
	{
		g_curScenceEventData[ enum, 5] = i;
		UpdateScence(g_curScenceEventData[ enum, 10], g_curScenceEventData[ enum, 9]);
		sdl_delay(20);
		DrawScenceWithoutRole(Sx, Sy);
		if (not (AboutMainRole))
			DrawRoleOnScence(Sx, Sy);
		//showmessage(inttostr(enum+100*g_curEvent));
		SDL_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	}
	//showmessage(inttostr(Sx+100*Sy));
	//showmessage(inttostr(g_curScenceEventData[ [enum,10]+100*g_curScenceEventData[ [enum,9]));
	g_curScenceEventData[ enum, 5] = g_curScenceEventData[ enum, 7];
	UpdateScence(g_curScenceEventData[ enum, 10], g_curScenceEventData[ enum, 9]);
}

int function instruct_28(rnum = 0;
		int  e1 = 0;
		int  e2 = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
{
	result = jump2;
	if ((rrole[rnum].Ethics >= e1) && (rrole[rnum].Ethics <= e2)) result = jump1;
}

int function instruct_29(rnum = 0;
		int  r1 = 0;
		int  r2 = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
{
	result = jump2;
	if ((rrole[rnum].Attack >= r1) && (rrole[rnum].Attack <= r2)) result = jump1;
}

void instruct_30(x1, y1, x2, int y2 = 0)()
	var
	int s = 0;
{
	s = sign(x2 - x1);
	Sy = x1 + s;
	if (s > 0) g_sFace = 1;
	if (s < 0) g_sFace = 2;
	if (s <> 0)
		while s * (x2 - Sy) >= 0 do
		{
			sdl_delay(50);
			DrawScenceWithoutRole(Sx, Sy);
			g_sStep = g_sStep + 1;
			if (g_sStep >= 8) g_sStep = 0;
			DrawRoleOnScence(Sx, Sy);
			SDL_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
			Sy = Sy + s;
		}
	s = sign(y2 - y1);
	Sx = y1 + s;
	if (s > 0) g_sFace = 3;
	if (s < 0) g_sFace = 0;
	if (s <> 0)
		while s * (y2 - Sx) >= 0 do
		{
			sdl_delay(50);
			DrawScenceWithoutRole(Sx, Sy);
			g_sStep = g_sStep + 1;
			if (g_sStep >= 8) g_sStep = 0;
			DrawRoleOnScence(Sx, Sy);
			SDL_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
			Sx = Sx + s;
		}
	Sx = y2;
	Sy = x2;
	g_sStep = 0;
	g_ex = Sx;
	g_ey = Sy;
}

int function instruct_31(moneynum = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
var
int i = 0;
{
	result = jump2;
	for i = 0 to MAX_ITEM_NUM - 1 do
	{
		if ((RItemList[i].Number == MONEY_ID) && (RItemList[i].Amount >= moneynum))
		{
			result = jump1;
			break;
		}
	}
}

void instruct_32(inum, int amount = 0)()
	var
	int i = 0;
word: widestring;
{
	i = 0;
	while (RItemList[i].Number >= 0) && (i < MAX_ITEM_NUM) do
	{
		if ((RItemList[i].Number == inum))
		{
			RItemList[i].Amount = RItemList[i].Amount + amount;
			if ((RItemList[i].Amount < 0) && (amount >= 0)) RItemList[i].Amount = 32767;
			if ((RItemList[i].Amount < 0) && (amount < 0)) RItemList[i].Amount = 0;
			break;
		}
		i = i + 1;
	}
	if (RItemList[i].Number < 0)
	{
		RItemList[i].Number = inum;
		RItemList[i].Amount = amount;
	}
	ReArrangeItem;
}

//学到武功, 如果已有武功则升级, 如果已满10个不会洗武功

void instruct_33(rnum, magicnum, int dismode = 0)()
	var
	int i = 0;
word: widestring;
{
	for i = 0 to 9 do
	{
		if ((RRole[rnum].Magic[i] <= 0) || (RRole[rnum].Magic[i] == magicnum))
		{
			if (RRole[rnum].Magic[i] > 0) RRole[rnum].Maglevel[i] = RRole[rnum].Maglevel[i] + 100;
			RRole[rnum].Magic[i] = magicnum;
			if (RRole[rnum].MagLevel[i] > 999) RRole[rnum].Maglevel[i] = 999;
			break;
		}
	}
	//if (i == 10) rrole[rnum].data[i+63] = magicnum;
	if (dismode == 0)
	{
		DrawFrameRectangle(SCREEN_CENTER_X - 75, 98, 145, 76, 0, COLOR(255), 30);
		word = " 學會";
		drawshadowtext(@word[1], SCREEN_CENTER_X - 90, 125, COLOR(0x7), COLOR(0x5));
		drawbig5shadowtext(@rrole[rnum].Name, SCREEN_CENTER_X - 90, 100, COLOR(0x23), COLOR(0x21));
		drawbig5shadowtext(@Rmagic[magicnum].Name, SCREEN_CENTER_X - 90, 150, COLOR(0x66), COLOR(0x64));
		sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
		WaitKey;
		redraw;
	}
}

void instruct_34(rnum, int iq = 0)()
	var
	word: widestring;
{
	if (RRole[rnum].Aptitude + iq <= 100)
	{
		RRole[rnum].Aptitude = RRole[rnum].Aptitude + iq;
	}
	else {
		iq = 100 - RRole[rnum].Aptitude;
		RRole[rnum].Aptitude = 100;
	}
	if (iq > 0)
	{
		DrawFrameRectangle(SCREEN_CENTER_X - 75, 98, 145, 51, 0, COLOR(255), 30);
		word = " 資質增加";
		drawshadowtext(@word[1], SCREEN_CENTER_X - 90, 125, COLOR(0x7), COLOR(0x5));
		drawbig5shadowtext(@rrole[rnum].Name, SCREEN_CENTER_X - 90, 100, COLOR(0x23), COLOR(0x21));
		word = format("%3d", [iq]);
		drawengshadowtext(@word[1], SCREEN_CENTER_X + 30, 125, COLOR(0x66), COLOR(0x64));
		sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
		WaitKey;
		redraw;
	}
}

void instruct_35(rnum, magiclistnum, magicnum, int exp = 0)()
	var
	int i = 0;
{
	if ((magiclistnum < 0) || (magiclistnum > 9))
	{
		for i = 0 to 9 do
		{
			if (RRole[rnum].Magic[i] <= 0)
			{
				RRole[rnum].Magic[i] = magicnum;
				RRole[rnum].MagLevel[i] = exp;
				break;
			}
		}
		if (i == 10)
		{
			RRole[rnum].Magic[0] = magicnum;
			RRole[rnum].MagLevel[i] = exp;
		}
	}
	else {
		RRole[rnum].Magic[magiclistnum] = magicnum;
		RRole[rnum].MagLevel[magiclistnum] = exp;
	}
}

int function instruct_36(sexual = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
{
	result = jump2;
	if (rrole[0].Sexual == sexual) result = jump1;
	if (sexual > 255)
		if (x50[0x7000] == 0) result = jump1 else result = jump2;
}

void int instruct_37(Ethics = 0)()
{
	RRole[0].Ethics = RRole[0].Ethics + ethics;
	if (RRole[0].Ethics > 100) RRole[0].Ethics = 100;
	if (RRole[0].Ethics < 0) RRole[0].Ethics = 0;
}

void instruct_38(snum, layernum, oldpic, int newpic = 0)()
	var
	int   i1 = 0;
	int i2 = 0;
{
	if (snum == -2) snum = g_curScence;
	for i1 = 0 to 63 do
		for i2 = 0 to 63 do
		{
			if (g_scenceData[snum, layernum, i1, i2] == oldpic) g_scenceData[snum, layernum, i1, i2] = newpic;
		}
}

void int instruct_39(snum = 0)()
{
	g_roleData.scences[snum].EnCondition = 0;
}

void int instruct_40(director = 0)()
{
	g_sFace = director;
}

void instruct_41(rnum, inum, int amount = 0)()
	var
	int   i = 0;
	int p = 0;
{
	p = 0;
	for i = 0 to 3 do
	{
		if (Rrole[rnum].TakingItem[i] == inum)
		{
			Rrole[rnum].TakingItemAmount[i] = Rrole[rnum].TakingItemAmount[i] + amount;
			p = 1;
			break;
		}
	}
	if (p == 0)
	{
		for i = 0 to 3 do
		{
			if (Rrole[rnum].TakingItem[i] == -1)
			{
				Rrole[rnum].TakingItem[i] = inum;
				Rrole[rnum].TakingItemAmount[i] = amount;
				break;
			}
		}
	}
	for i = 0 to 3 do
	{
		if (Rrole[rnum].TakingItemAmount[i] <= 0)
		{
			Rrole[rnum].TakingItem[i] = -1;
			Rrole[rnum].TakingItemAmount[i] = 0;
		}
	}

}

int function instruct_42(jump1 = 0;
		int jump2 = 0int ) = 0;
var
int i = 0;
{
	result = jump2;
	for i = 0 to 5 do
	{
		if (Rrole[Teamlist[i]].Sexual == 1)
		{
			result = jump1;
			break;
		}
	}
}

int function instruct_43(inum = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
var
int i = 0;
{
	result = jump2;
	for i = 0 to MAX_ITEM_NUM - 1 do
		if (RItemList[i].Number == inum)
		{
			result = jump1;
			break;
		}
}

void instruct_44(enum1, beginpic1, endpic1, enum2, beginpic2, int endpic2 = 0)()
	var
	int i = 0;
{
	g_curScenceData[ 3, g_curScenceEventData[ enum1, 10], g_curScenceEventData[ enum1, 9]] = enum1;
	g_curScenceData[ 3, g_curScenceEventData[ enum2, 10], g_curScenceEventData[ enum2, 9]] = enum2;
	for i = 0 to endpic1 - beginpic1 do
	{
		g_curScenceEventData[ enum1, 5] = beginpic1 + i;
		g_curScenceEventData[ enum2, 5] = beginpic2 + i;
		UpdateScence(g_curScenceEventData[ enum1, 10], g_curScenceEventData[ enum1, 9]);
		UpdateScence(g_curScenceEventData[ enum2, 10], g_curScenceEventData[ enum2, 9]);
		sdl_delay(20);
		DrawScenceWithoutRole(Sx, Sy);
		DrawScence;
		SDL_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	}
	//g_curScenceData[ 3, g_curScenceEventData[ [enum,10],g_curScenceEventData[ [enum,9]]=-1;
}

void instruct_45(rnum, int speed = 0)()
	var
	word: widestring;
{
	RRole[rnum].Speed = RRole[rnum].Speed + speed;
	DrawFrameRectangle(SCREEN_CENTER_X - 75, 98, 145, 51, 0, COLOR(255), 30);
	word = " 輕功增加";
	drawshadowtext(@word[1], SCREEN_CENTER_X - 90, 125, COLOR(0x7), COLOR(0x5));
	drawbig5shadowtext(@rrole[rnum].Name, SCREEN_CENTER_X - 90, 100, COLOR(0x23), COLOR(0x21));
	word = format("%4d", [speed]);
	drawengshadowtext(@word[1], SCREEN_CENTER_X + 20, 125, COLOR(0x66), COLOR(0x64));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;
}

void instruct_46(rnum, int mp = 0)()
	var
	word: widestring;
{
	RRole[rnum].MaxMP = RRole[rnum].MaxMP + mp;
	RRole[rnum].CurrentMP = RRole[rnum].MaxMP;
	DrawFrameRectangle(SCREEN_CENTER_X - 75, 98, 145, 51, 0, COLOR(255), 30);
	word = " 內力增加";
	drawshadowtext(@word[1], SCREEN_CENTER_X - 90, 125, COLOR(0x7), COLOR(0x5));
	drawbig5shadowtext(@rrole[rnum].Name, SCREEN_CENTER_X - 90, 100, COLOR(0x23), COLOR(0x21));
	word = format("%4d", [mp]);
	drawengshadowtext(@word[1], SCREEN_CENTER_X + 20, 125, COLOR(0x66), COLOR(0x64));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;
}

void instruct_47(rnum, int attack = 0)()
	var
	word: widestring;
{
	RRole[rnum].Attack = RRole[rnum].Attack + attack;
	DrawFrameRectangle(SCREEN_CENTER_X - 75, 98, 145, 51, 0, COLOR(255), 30);
	word = " 武力增加";
	drawshadowtext(@word[1], SCREEN_CENTER_X - 90, 125, COLOR(0x7), COLOR(0x5));
	drawbig5shadowtext(@rrole[rnum].Name, SCREEN_CENTER_X - 90, 100, COLOR(0x23), COLOR(0x21));
	word = format("%4d", [attack]);
	drawengshadowtext(@word[1], SCREEN_CENTER_X + 20, 125, COLOR(0x66), COLOR(0x64));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;
}

void instruct_48(rnum, int hp = 0)()
	var
	word: widestring;
{
	RRole[rnum].MaxHP = RRole[rnum].MaxHP + hp;
	RRole[rnum].CurrentHP = RRole[rnum].MaxHP;
	DrawFrameRectangle(SCREEN_CENTER_X - 75, 98, 145, 51, 0, COLOR(255), 30);
	word = " 生命增加";
	drawshadowtext(@word[1], SCREEN_CENTER_X - 90, 125, COLOR(0x7), COLOR(0x5));
	drawbig5shadowtext(@rrole[rnum].Name, SCREEN_CENTER_X - 90, 100, COLOR(0x23), COLOR(0x21));
	word = format("%4d", [hp]);
	drawengshadowtext(@word[1], SCREEN_CENTER_X + 20, 125, COLOR(0x66), COLOR(0x64));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;
}

void instruct_49(rnum, int MPpro = 0)()
{
	RRole[rnum].MPType = MPpro;
}

function instruct_50(list: array of int integer) = 0;
var
int   i = 0;
int p = 0;
//instruct_50e: function (list1: array of int integer) = 0;
{
	result = 0;
	if (list[0] <= 128)
	{
		//instruct_50e="";
		result = instruct_50e(list[0], list[1], list[2], list[3], list[4], list[5], list[6]);
	}
	else {
		result = list[6];
		p = 0;
		for i = 0 to 4 do
		{
			p = p + instruct_18(list[i], 1, 0);
		}
		if (p == 5) result = list[5];
	}
}

void instruct_51()
{
	instruct_1(SOFTSTAR_BEGIN_TALK + random(SOFTSTAR_NUM_TALK), 0x72, 0);
}

void instruct_52()
	var
	word: widestring;
{
	DrawFrameRectangle(SCREEN_CENTER_X - 110, 98, 220, 26, 0, COLOR(255), 30);
	word = " 你的品德指數為：";
	drawshadowtext(@word[1], SCREEN_CENTER_X - 125, 100, COLOR(0x7), COLOR(0x5));
	word = format("%3d", [rrole[0].Ethics]);
	drawengshadowtext(@word[1], SCREEN_CENTER_X + 65, 100, COLOR(0x66), COLOR(0x64));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;
}

void instruct_53()
	var
	word: widestring;
{
	DrawFrameRectangle(SCREEN_CENTER_X - 110, 98, 220, 26, 0, COLOR(255), 30);
	word = " 你的聲望指數為：";
	drawshadowtext(@word[1], SCREEN_CENTER_X - 125, 100, COLOR(0x7), COLOR(0x5));
	word = format("%3d", [rrole[0].Repute]);
	drawengshadowtext(@word[1], SCREEN_CENTER_X + 65, 100, COLOR(0x66), COLOR(0x64));
	sdl_updaterect(g_screenSurface, 0, 0, g_screenSurface.w, g_screenSurface.h);
	WaitKey;
	redraw;
}

//Open all scences.
//Note: in primary game, some scences are set to different entrancing condition.

void instruct_54()
	var
	int i = 0;
{
	for i = 0 to 100 do
	{
		Rscence[i].EnCondition = 0;
	}
	Rscence[2].EnCondition = 2;
	Rscence[38].EnCondition = 2;
	Rscence[75].EnCondition = 1;
	Rscence[80].EnCondition = 1;
}

//Judge the event number.

int function instruct_55(enum = 0;
		int  value = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
{
	result = jump2;
	if (g_curScenceEventData[ enum, 2] == value) result = jump1;
}

//Add repute.
//声望刚刚超过200时家里出现请帖

void int instruct_56(Repute = 0)()
{
	RRole[0].Repute = RRole[0].Repute + repute;
	if ((RRole[0].Repute > 200) && (RRole[0].Repute - repute <= 200))
	{
		//showmessage("");
		instruct_3([70, 11, 0, 11, 0x3A4, -1, -1, 0x1F20, 0x1F20, 0x1F20, 0, 18, 21]);
	}
}

{void instruct_57()
	var
		int i = 0;
	{
		for i=0 to endpic1-beginpic1 do
		{
			g_curScenceEventData[ [enum1,5]=beginpic1+i;
			g_curScenceEventData[ [enum2,5]=beginpic2+i;
			UpdateScence(g_curScenceEventData[ [enum1,10],g_curScenceEventData[ [enum1,9]);
			UpdateScence(g_curScenceEventData[ [enum2,10],g_curScenceEventData[ [enum2,9]);
			sdl_delay(20);
			DrawScenceByCenter(Sx,Sy);
			DrawScence;
			SDL_updaterect(g_screenSurface,0,0,g_screenSurface.w,g_screenSurface.h);
		}
	}}

void instruct_58()
	var
	int   i = 0;
	int p = 0;
{
	for i = 0 to 14 do
	{
		p = random(2);
		instruct_1(2854 + i * 2 + p, 0, 3);
		if (not (battle(102 + i * 2 + p, 0))) instruct_15;
		instruct_14;
		instruct_13;
		if (i mod 3 == 2)
		{
			instruct_1(2891, 0, 3);
			instruct_12;
			instruct_14;
			instruct_13;
		}
	}
	instruct_1(2884, 0, 3);
	instruct_1(2885, 0, 3);
	instruct_1(2886, 0, 3);
	instruct_1(2887, 0, 3);
	instruct_1(2888, 0, 3);
	instruct_1(2889, 0, 1);
	instruct_2(0x8F, 1);

}

//全员离队, 但未清除相关事件

void instruct_59()
	var
	int i = 0;
{
	for i = 1 to 5 do
		TeamList[i] = -1;

}

int function instruct_60(snum = 0;
		int  enum = 0;
		int  pic = 0;
		int  jump1 = 0;
		int jump2 = 0int ) = 0;
{
	result = jump2;
	if (snum == -2) snum = g_curScence;
	if (g_scenceEventData[snum, enum, 5] == pic) result = jump1;
	//showmessage(inttostr(g_scenceEventData[snum,enum,5]));
}

void instruct_62()
	var
	int i = 0;
str: widestring;
{
	g_inGame = 3;
	redraw;
	EndAmi;
	//display_img("}.png", 0, 0);
	//g_inGame = 3;
}
#endif
