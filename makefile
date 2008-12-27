CC=gcc
CFLAGS=-g -Wall

TARGET=jinyong

SDL_LIBS=-lSDL -lSDL_gfx -lSDL_ttf -lSDL_mixer
OBJS=game.o \
	 map.o \
	 scence.o \
	 cmd.o \
	 draw.o \
	 sound.o

all: clean $(TARGET)
	-cp -rf $(TARGET) ..

.c.o:
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS) $(SDL_LIBS)

clean:
	-rm -f $(TARGET) $(OBJS)
