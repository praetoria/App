CFLAGS = `sdl2-config --cflags` -I/usr/include/SDL2 -std=c++11 -c
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf
OBJECTS = App.o Button.o main.o UIElement.o Text.o Input.o
CC = g++
EXE = gen

$(EXE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXE)
App.o : App.h UIElement.h App.cpp Input.h Text.h
	$(CC) $(CFLAGS) App.cpp
Button.o : Button.h Button.cpp UIElement.h
	$(CC) $(CFLAGS) Button.cpp
main.o : App.h main.cpp
	$(CC) $(CFLAGS) main.cpp
UIElement.o : UIElement.h UIElement.cpp
	$(CC) $(CFLAGS) UIElement.cpp
Text.o : Text.h Text.cpp UIElement.h
	$(CC) $(CFLAGS) Text.cpp
Input.o : Input.h UIElement.h Input.cpp
	$(CC) $(CFLAGS) Input.cpp
clean:
	rm *.o
