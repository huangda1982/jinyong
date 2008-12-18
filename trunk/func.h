/*******************************************************************************
* func.h                                                    fileencoding=UTF-8 *
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

void Quit();
void PlayXMI(int index, int times);
void StopXMI();
void PlayWAV(int index, int times);
void PlayWAVFile(char* filename, int times);
void LoadGame(int slot);
void SaveGame(int slot);
int WaitAnyKey();
#define COLOR(c) GetPalettePixel(g_screenSurface->format, g_palette, (c), 255, 0)
#define COLORA(c, a) GetPalettePixel(g_screenSurface->format, g_palette, (c), (a), 0)
#define COLORH(c, h) GetPalettePixel(g_screenSurface->format, g_palette, (c), 255, (h))
uint32 GetPalettePixel(SDL_PixelFormat* format, T_RGB* palette, uint8 color, uint8 alpha, int highlight);
void PutPixel(SDL_Surface* surface, int x, int y, uint32 pixel);
void DrawRectangle(int x, int y, int w, int h, uint32 frmColor, uint32 insColor);
void DrawRLE8Pic(SDL_Surface* surface, int index, int x, int y, uint32* idxBuffer, byte* picBuffer, int highlight);
void DrawBigPicOnScreen(int index, byte* buffer);
void DrawPic(SDL_Surface* destSurface, int index, int x, int y, uint32* idxBuffer, byte* picBuffer, int highlight);
void DrawPicOnScreen(int index, int x, int y, uint32* idxBuffer, byte* picBuffer, int highlight);
T_Position GetPositionOnScreen(int x, int y, int cx, int cy);
void DrawTitlePic(int index, int x, int y);
void DrawScencePic(int index, int x, int y);
void InitialSPic(int index, int x, int y);
bool PicInArea(int x, int y, T_PicRect picRect, T_Rect destRect);
void DrawMapPic(int index, int x, int y);
void DrawFacePic(int index, int x, int y);
void DrawBFPic(int index, int x, int y, int highlight);
void DrawPicToBFPic(int index, int x, int y);
void DrawEffect(int index, int x, int y);
void DrawAction(int index, int x, int y);
void DrawText(char* str, int x, int y, uint32 color);
void DrawShadowText(char* str, int x, int y, uint32 color, uint32 color2);
void DrawFrameText(char* str, int x, int y, int padding, uint32 txtColor, uint32 shdColor, uint32 frmColor);
void DrawBig5Text(char* big5, int x, int y, uint32 color);
void UTF8ToBig5(char* utf8, char* big5);
void Big5ToUTF8(char* big5, char* utf8);
void DrawBig5ShadowText(char* big5, int x, int y, uint32 color, uint32 color2);
void DrawMap();
bool GoThrouht(int x, int y, bool* inBoat);
bool GoThroughScence(int x, int y);
void DrawScence(int x, int y);
void* LoadFile(char* filename, void* buffer, size_t size);
void ReadFiles();
void UpdateScreen();
void Start();
sint32 Random(sint32 a, sint32 b);
void InitialRole();
void ShowStatus(int index);
;
