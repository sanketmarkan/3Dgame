all: sample3D

sample3D: game.cpp glad.c controls.cpp initgame.cpp initobjects.cpp important.cpp
	g++ -o sample3D game.cpp glad.c -lGL -lglfw -ldl -L/usr/local/lib
clean:
	rm sample3D
