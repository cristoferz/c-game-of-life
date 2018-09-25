run: build
	./game-of-life.bin
build:
	g++ game-of-life.cpp -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -o game-of-life.bin
