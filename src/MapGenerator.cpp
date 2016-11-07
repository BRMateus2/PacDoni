#include <SFML/Graphics.hpp>
#include <fstream>
using namespace sf;
using namespace std;

int main(int argc, char** argv){
	Texture maze_texture;
	maze_texture.loadFromFile(argv[1]);
	maze_texture.setSmooth(false);

	Image img = maze_texture.copyToImage();
	unsigned int x,y;

	x = img.getSize().x;
	y = img.getSize().y;

	ofstream map_1(argv[2]);
	Color color;

	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++){
			color = img.getPixel(j, i);

			if(color.r == 0 && color.g == 0 && color.b == 0){
				map_1 << "0 ";
			}else
			if(color.r == 33 && color.g == 33 && color.b == 255){
				map_1 << "1 ";
			}else
			if(color.r == 252 && color.g == 181 && color.b == 255){
				map_1 << "2 ";
			}else
			if(color.r == 255 && color.g == 255 && color.b == 0){
				map_1 << "3 ";
			}else
			if(color.r == 0 && color.g == 255 && color.b == 0){
				map_1 << "4 ";
			}else
			if(color.r == 255 && color.g == 255 && color.b == 255){
				map_1 << "5 ";
			}else
			if(color.r == 255 && color.g == 0 && color.b == 0){
				map_1 << "6 ";
			}

		}
		map_1 << endl;
	}

	map_1.close();
	return 0;
}
