CC=gcc
CP=cp -rf
RM=rm -rf

CFLAGS=-g

SDL_LIBS=-lSDL -lSDL_gfx -lSDL_ttf -lSDL_mixer
OBJS= \
	game.o \
	map.o \
	scence.o \
	cmd.o \
	draw.o \
	sound.o

WIN32=$(shell gcc -v 2>&1 | grep 'win32')
ifneq ($(WIN32),)
LIBS= \
	$(SDL_LIBS) \
	-liconv
TARGET=jy.exe
else
LIBS=$(SDL_LIBS)
TARGET=jy
endif

all: clean $(TARGET)
	$(CP)  $(TARGET) ..
	$(CP)  font ..

.c.o:
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS) $(LIBS)

clean:
	$(RM) $(TARGET) $(OBJS)
