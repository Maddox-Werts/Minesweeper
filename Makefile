# Variables
LIBS:= -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
TARGET:= minesweeper

# Instructions
build: compile link run

compile:
	g++ -c -I include source/engine/vectors.cpp -o bin/vectors.o
	g++ -c -I include source/engine/engine.cpp -o bin/engine.o
	g++ -c -I include source/game/tilemap.cpp -o bin/tilemap.o
	g++ -c -I include source/game/navbar.cpp -o bin/navbar.o
	g++ -c -I include source/game/message.cpp -o bin/message.o
	g++ -c -I include source/main.cpp -o bin/main.o

link:
	g++ bin/*.o -L lib $(LIBS) -o build/$(TARGET)

cpydat:
	cp data -r build

run:
	./build/$(TARGET)

# Complimentary
clean:
	rm build/*
	rm bin/*