LIN_CC=gcc
WCE_CC=arm-wince-pe-gcc
CFLAG=-g -Wall

LIN_TARGET=jinyong
WCE_TARGET=jinyongCE.exe
TARGET=$(LIN_TARGET) $(WCE_TARGET)

LIB_SDL=-lSDL -lSDL_gfx -lSDL_ttf -lSDL_mixer

all: clean linux
	-cp -rf $(TARGET) ..

linux:
	$(LIN_CC) -o $(LIN_TARGET) jinyong.c $(CFLAG) $(LIB_SDL)

wince:
	$(WCE_CC) -o $(WCE_TARGET) jinyong.c $(CFLAG) $(LIB_SDL)

clean:
	-rm -f $(TARGET)
