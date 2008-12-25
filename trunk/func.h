/*******************************************************************************
* game.h                                                    fileencoding=UTF-8 *
*******************************************************************************/

#include "claim.h"

#ifndef __GAME_H__
#define __GAME_H__

sint32 Random(sint32 a, sint32 b);

void Quit();
void PlayXMI(int index, int times);
void StopXMI();
void PlayWAV(int index, int times);
void PlayWAVFile(char* filename, int times);

void LoadGame(int slot);
void SaveGame(int slot);

int WaitAnyKey();
bool PicInArea(int x, int y, T_PicRect picRect, T_Rect destRect);
T_Position GetPositionOnScreen(int x, int y, int cx, int cy);

uint32 GetRGBAPixel(uint8 color, uint8 alpha, int highlight);
uint32 GetPalettePixel(SDL_PixelFormat* format, uint8 color, uint8 alpha, int highlight);
#define COLOR(c)		GetRGBAPixel((c), 255, 0)
#define COLORA(c, a)	GetRGBAPixel((c), (a), 0)
#define COLORH(c, h)	GetRGBAPixel((c), 255, (h))
void PutPixel(SDL_Surface* surface, int x, int y, uint32 pixel);
void DrawFrameRectangle(int x, int y, int w, int h, uint8 frmColor, uint8 insColor, uint8 alpha);
void DrawRLE8Pic(SDL_Surface* surface, int index, int x, int y, uint32* idxBuffer, byte* picBuffer, int highlight);
void DrawBigPicOnScreen(int index, byte* buffer);
void DrawTitlePic(int index, int x, int y);

void DrawScencePic(int index, int x, int y);
void DrawScenceWithoutRole(int sx, int sy);
void DrawRoleOnScence(int x, int y);
void DrawScenceWithoutUpdate();


void DrawFacePic(int index, int x, int y);
void DrawBFPic(int index, int x, int y, int highlight);
void DrawPicToBFPic(int index, int x, int y);
void DrawEffect(int index, int x, int y);
void DrawAction(int index, int x, int y);

char* Utf8ToBig5(char* utf8);
char* Big5ToUtf8(char* big5);

void DrawFrameText(char* str, uint8 txtColor, uint8 frmColor);
T_Position DrawText(char* str, int x, int y, uint8 color);
T_Position DrawShadowText(char* str, int x, int y, uint8 color);
T_Position DrawBig5Text(char* big5, int x, int y, uint8 color);
T_Position DrawBig5ShadowText(char* big5, int x, int y, uint8 color);

void* LoadFile(char* filename, void* buffer, size_t size);
bool GoThroughScence(int x, int y);
void ShowScenceName(int scence);

void DrawScence();
void RedrawWithoutUpdate();

void Redraw();
void ReadFiles();
void UpdateScreen();

void Start();
void InitialRole();
void ShowStatus(int index);
bool MagicLeveup(int role, int* nextLevelExp);
void InGame(bool start);
int InScence(int scence, EmInScence inScence);

#endif //__GAME_H__
