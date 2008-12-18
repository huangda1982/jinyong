all: clean linux
	cp -rf jinyong font ..

linux:
	gcc -o jinyong jinyong.c -g -Wall -lSDL -lSDL_gfx -lSDL_ttf -lSDL_mixer

wince:
	arm-wince-pe-gcc -o jinyongCE.exe jinyong.c -g -Wall -lSDL -lSDL_gfx -lSDL_ttf -lSDL_mixer

clean:
	rm -f jinyong
