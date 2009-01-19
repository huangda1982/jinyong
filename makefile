CC=gcc -mconsole
CFLAGS=-g

CP=cp -rf
RM=rm -rf

TARGET=jy

SDL_LIBS=-lSDL -lSDL_gfx -lSDL_ttf -lSDL_mixer
LIBS=$(SDL_LIBS) \
	-liconv
OBJS=game.o \
	 map.o \
	 scence.o \
	 cmd.o \
	 draw.o \
	 sound.o

all: clean $(TARGET)
	-$(CP)  $(TARGET) ..
	-$(CP)  font ..

.c.o:
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS) $(LIBS)

clean:
	-$(RM) $(TARGET) $(OBJS)
