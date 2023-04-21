# Variables
LIBS:= -lSDL2main -lSDL2
TARGET:= minesweeper

# Instructions
build: clrscr compile link run

clrscr:
	clear

compile:
	g++ -c -I include source/engine/engine.cpp -o bin/engine.o
	g++ -c -I include source/game/tilemap.cpp -o bin/tilemap.o
	g++ -c -I include source/main.cpp -o bin/main.o

link:
	g++ -L lib $(LIBS) bin/*.o -o build/$(TARGET)

cpydat:
	cp data -r build

run:
	./build/$(TARGET)

# Complimentary
clean:
	rm build/*
	rm bin/*