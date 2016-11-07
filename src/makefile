all:
	g++ -std=c++11 Socket.cpp Map.cpp Player.cpp GameServer.cpp -g -o GameServer -lpthread
	g++ -std=c++11 Socket.cpp Player.cpp GameClient.cpp -g -o GameClient -lpthread -lX11 -lsfml-graphics -lsfml-window -lsfml-system
gui:
	g++ Sfml.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
