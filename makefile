CC=gcc
CFLAGS=-g -Wall -O3

TARGET=jy

SDL_LIBS=-lSDL -lSDL_gfx -lSDL_ttf -lSDL_mixer
OBJS=game.o \
	 map.o \
	 scence.o \
	 cmd.o \
	 draw.o \
	 sound.o

all: clean $(TARGET)
	-cp -rf $(TARGET) ..
	-cp -rf font ..

.c.o:
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS) $(SDL_LIBS)

clean:
	-rm -f $(TARGET) $(OBJS)
