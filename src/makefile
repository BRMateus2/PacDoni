all:
	g++ -std=c++11 Socket.cpp Map.cpp Player.cpp GameServer.cpp -g -o GameServer -lpthread
	g++ -std=c++11 Socket.cpp Player.cpp GameClient.cpp -g -o GameClient -lpthread -lX11 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
map:
	g++ MapGenerator.cpp -o MapGenerator -lsfml-graphics -lsfml-window -lsfml-system
