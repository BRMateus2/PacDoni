#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

int main(){
    RenderWindow window(VideoMode(400, 300), "SFML works!");

	/*Texture ghost_texture;
	ghost_texture.loadFromFile("../res/sprites/ghost_red_r_1.png");
	ghost_texture.setSmooth(false);

	Sprite ghost;
	ghost.setTexture(ghost_texture);
	ghost.setScale(Vector2f(2.f, 2.f));
	ghost.setPosition(Vector2f(84, 84));*/

	Texture maze_texture;
	maze_texture.loadFromFile("../res/sprites/map_1.png");
	maze_texture.setSmooth(false);

	Texture game_s_texture;
	game_s_texture.loadFromFile("../res/sprites/game_screen.png");
	game_s_texture.setSmooth(false);

	Texture biscuit_texture;
	biscuit_texture.loadFromFile("../res/sprites/biscuit.png");
	biscuit_texture.setSmooth(false);

	Texture s_biscuit_texture;
	s_biscuit_texture.loadFromFile("../res/sprites/super_biscuit.png");
	s_biscuit_texture.setSmooth(false);

	Sprite maze;
	maze.setTexture(maze_texture);
	//maze.setScale(Vector2f(2.f, 2.f));
	maze.setPosition(Vector2f(150, 26));

	Sprite game_s;
	game_s.setTexture(game_s_texture);
	//game_s.setScale(Vector2f(2.f, 2.f));

	Sprite biscuit;
	biscuit.setTexture(biscuit_texture);

	Sprite s_biscuit;
	s_biscuit.setTexture(s_biscuit_texture);

	ifstream loader("map_1.txt");
	char** map = new char*[248];
	for(int i = 0; i < 248; i++){
		map[i] = new char[224];
	}

	for(int i = 0; i < 248; i++){
		for(int j = 0; j < 224; j++){
			loader >> map[i][j];
		}
	}
	loader.close();


	ofstream out("MAPAPAPA.txt");
	for(int i = 0; i < 248; i++){
		for(int j = 0; j < 224; j++){
			out << map[i][j] << " ";
		}
		out << endl;
	}

	cout << "passou daqui\n";

	int	cont;

    while (window.isOpen()){
        Event event;
		cont = 0;

        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
				window.close();
			}
        }

        window.clear();

		//Drawn here

		window.draw(game_s);
        window.draw(maze);

		for(int i = 0; i < 248; i++){
			for(int j = 0; j < 224; j++){
				if(map[i][j] == 'b'){
					biscuit.setPosition(Vector2f(j + 150, i + 26));
					window.draw(biscuit);
					cont++;
				}else
				if(map[i][j] == 's'){
					s_biscuit.setPosition(Vector2f(j + 150, i + 26));
					window.draw(s_biscuit);
					cont++;
				}
			}
		}
		cout << "cont " << cont << endl;
        window.display();
    }

    return 0;
}
