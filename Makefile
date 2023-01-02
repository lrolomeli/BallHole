sfml-app: main.o game.o render.o event.o physics.o maps.o
	g++ -o sfml-app main.o game.o render.o event.o physics.o maps.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp -o main.o

main.cpp:

game.o: Game.cpp Game.h
	g++ -c include/Game.cpp -o game.o

Game.cpp:

Game.h:

render.o: RenderBH.cpp RenderBH.h event.o
	g++ -c include/RenderBH.cpp -o render.o

RenderBH.cpp:

RenderBH.h:

event.o: Event.cpp Event.h
	g++ -c include/Event.cpp -o event.o

Event.cpp:

Event.h:

physics.o: Physics.cpp Physics.h
	g++ -c include/Physics.cpp -o physics.o

Physics.cpp:

Physics.h:

maps.o: Maps.cpp Maps.h
	g++ -c include/Maps.cpp -o maps.o

Maps.cpp:

Maps.h:

