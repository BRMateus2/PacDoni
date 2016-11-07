#include "Player.hpp"
#include "Map.hpp"

bool collide(Player& player, Map& g_map, int direction, bool last_try){

	p_g = false;
	p_p = false;
	p_b = false;
	p_s = false;
	p_i = false;
	p_w = false;

	switch(direction){
		case 0:
			for(j = 0; j < 16; j++){
				v = g_map.get_map_at(player.get_i() + 16, player.get_j() + j);

				if(v == '1'){
					p_w = true;
				}else
				if(v == '3'){
					p_p = true;
				}else
				if(v == '4'){
					p_g = true;
				}else
				if(v == '5'){
					p_b = true;
					b_pos.push_back(make_pair(_player.get_i() + 16, player.get_j() + j));
				}else
				if(v == '6'){
					p_s = true;
					b_pos.push_back(make_pair(_player.get_i() + 16, player.get_j() + j));
				}else
				if(v == '7'){
					p_i = true;
					b_pos.push_back(make_pair(_player.get_i() + 16, player.get_j() + j));
				}
			}

			if(!p_w && !p_p){
				if(p_g){
					//KILL PAC-MAN
					//verifica se esta super
					//Define sprite
					//seta número de lifes
				}else
				if(p_b){ // Colisão com biscoito
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map.get_biscuits()->find(b_pos[0]);
					g_map.get_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(1);
					}else
					if(player.get_sprites_num() == 1){
						player.set_sprites_num(2);
					}else
					if(player.get_sprites_num() == 2){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);

				}else
				if(p_s){ //Colisão com super biscoito
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map.get_s_biscuits()->find(b_pos[0]);
					g_map.get_s_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

					//Move pac-man [Baixo: +1 i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.fill_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(1);
					}else
					if(player.get_sprites_num() == 1){
						player.set_sprites_num(2);
					}else
					if(player.get_sprites_num() == 2){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(player.get_desired_direction());

				}else
				if(p_i){
					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(1);
					}else
					if(player.get_sprites_num() == 1){
						player.set_sprites_num(2);
					}else
					if(player.get_sprites_num() == 2){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//Pega o item
					player.set_item(7);

					//muda direção
					player.set_direction(direction);
				}else{
					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(1);
					}else
					if(player.get_sprites_num() == 1){
						player.set_sprites_num(2);
					}else
					if(player.get_sprites_num() == 2){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);
				}

				return true;

			}else{
				if(last_try){
					//Define sprite
					player.set_sprites_num(2);
					//Verifica super
					player.decrease_super_force();
				}

				return false;
			}
		break;

		case 1:
			for(j = 0; j < 16; j++){
				v = g_map.get_map_at(player.get_i() - 1, player.get_j() + j);

				if(v == '1'){
					p_w = true;
				}else
				if(v == '3'){
					p_p = true;
				}else
				if(v == '4'){
					p_g = true;
				}else
				if(v == '5'){
					p_b = true;
					b_pos.push_back(make_pair(_player.get_i() - 1, player.get_j() + j));
				}else
				if(v == '6'){
					p_s = true;
					b_pos.push_back(make_pair(_player.get_i() - 1, player.get_j() + j));
				}else
				if(v == '7'){
					p_i = true;
					b_pos.push_back(make_pair(_player.get_i() - 1, player.get_j() + j));
				}
			}

			if(!p_w && !p_p){
				if(p_g){
					//KILL PAC-MAN
					//verifica se esta super
					//Define sprite
					//seta número de lifes
				}else
				if(p_b){ // Colisão com biscoito
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map.get_biscuits()->find(b_pos[0]);
					g_map.get_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() - 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(3);
					}else
					if(player.get_sprites_num() == 3){
						player.set_sprites_num(4);
					}else
					if(player.get_sprites_num() == 4){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);

				}else
				if(p_s){ //Colisão com super biscoito
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map.get_s_biscuits()->find(b_pos[0]);
					g_map.get_s_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

					//Move pac-man [Baixo: +1 i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() - 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.fill_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(3);
					}else
					if(player.get_sprites_num() == 3){
						player.set_sprites_num(4);
					}else
					if(player.get_sprites_num() == 4){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);

				}else
				if(p_i){
					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() - 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(3);
					}else
					if(player.get_sprites_num() == 3){
						player.set_sprites_num(4);
					}else
					if(player.get_sprites_num() == 4){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//Pega o item
					player.set_item(7);

					//muda direção
					player.set_direction(direction);
				}else{
					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_i(player.get_i() - 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(3);
					}else
					if(player.get_sprites_num() == 3){
						player.set_sprites_num(4);
					}else
					if(player.get_sprites_num() == 4){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);
				}

				return true;

			}else{
				if(last_try){
					//Define sprite
					player.set_sprites_num(4);
					//Verifica super
					player.decrease_super_force();
				}

				return false;
			}
		break;

		case 2:
			for(j = 0; j < 16; j++){
				v = g_map.get_map_at(player.get_i() + j, player.get_j() + 16);

				if(v == '1'){
					p_w = true;
				}else
				if(v == '3'){
					p_p = true;
				}else
				if(v == '4'){
					p_g = true;
				}else
				if(v == '5'){
					p_b = true;
					b_pos.push_back(make_pair(_player.get_i() + j, player.get_j() + 16));
				}else
				if(v == '6'){
					p_s = true;
					b_pos.push_back(make_pair(_player.get_i() + j, player.get_j() + 16));
				}else
				if(v == '7'){
					p_i = true;
					b_pos.push_back(make_pair(_player.get_i() + j, player.get_j() + 16));
				}
			}

			if(!p_w && !p_p){
				if(p_g){
					//KILL PAC-MAN
					//verifica se esta super
					//Define sprite
					//seta número de lifes
				}else
				if(p_b){ // Colisão com biscoito
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map.get_biscuits()->find(b_pos[0]);
					g_map.get_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_j(player.get_j() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(5);
					}else
					if(player.get_sprites_num() == 5){
						player.set_sprites_num(6);
					}else
					if(player.get_sprites_num() == 6){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);

				}else
				if(p_s){ //Colisão com super biscoito
					//Remove Biscuit
					map<pair<int, int>, char>::iterator it;
					it = g_map.get_s_biscuits()->find(b_pos[0]);
					g_map.get_s_biscuits()->erase(it);

					//Aumenta número biscoitos jogador
					player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

					//Move pac-man [Baixo: +1 i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_j(player.get_j() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.fill_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(5);
					}else
					if(player.get_sprites_num() == 5){
						player.set_sprites_num(6);
					}else
					if(player.get_sprites_num() == 6){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);

				}else
				if(p_i){
					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_j(player.get_j() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(5);
					}else
					if(player.get_sprites_num() == 5){
						player.set_sprites_num(6);
					}else
					if(player.get_sprites_num() == 6){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//Pega o item
					player.set_item(7);

					//muda direção
					player.set_direction(direction);
				}else{
					//Move pac-man [Baixo: +1i]
					g_map.set_map_at(player.get_i(), player.get_j(), '0');
					player.set_j(player.get_j() + 1);
					g_map.set_map_at(player.get_i(), player.get_j(), '3');

					//verifica super
					player.decrease_super_force();

					//Define sprite
					if(player.get_sprites_num() == 0){
						player.set_sprites_num(5);
					}else
					if(player.get_sprites_num() == 5){
						player.set_sprites_num(6);
					}else
					if(player.get_sprites_num() == 6){
						player.set_sprites_num(0);
					}else{
						player.set_sprites_num(0);
					}

					//muda direção
					player.set_direction(direction);
				}

				return true;

			}else{
				if(last_try){
					//Define sprite
					player.set_sprites_num(6);
					//Verifica super
					player.decrease_super_force();
				}

				return false;
			}
		break;

		case 3:
		for(j = 0; j < 16; j++){
			v = g_map.get_map_at(player.get_i() + j, player.get_j() - 1);

			if(v == '1'){
				p_w = true;
			}else
			if(v == '3'){
				p_p = true;
			}else
			if(v == '4'){
				p_g = true;
			}else
			if(v == '5'){
				p_b = true;
				b_pos.push_back(make_pair(_player.get_i() + j, player.get_j() - 1));
			}else
			if(v == '6'){
				p_s = true;
				b_pos.push_back(make_pair(_player.get_i() + j, player.get_j() - 1));
			}else
			if(v == '7'){
				p_i = true;
				b_pos.push_back(make_pair(_player.get_i() + j, player.get_j() - 1));
			}
		}

		if(!p_w && !p_p){
			if(p_g){
				//KILL PAC-MAN
				//verifica se esta super
				//Define sprite
				//seta número de lifes
			}else
			if(p_b){ // Colisão com biscoito
				//Remove Biscuit
				map<pair<int, int>, char>::iterator it;
				it = g_map.get_biscuits()->find(b_pos[0]);
				g_map.get_biscuits()->erase(it);

				//Aumenta número biscoitos jogador
				player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

				//Move pac-man [Baixo: +1i]
				g_map.set_map_at(player.get_i(), player.get_j(), '0');
				player.set_j(player.get_j() - 1);
				g_map.set_map_at(player.get_i(), player.get_j(), '3');

				//verifica super
				player.decrease_super_force();

				//Define sprite
				if(player.get_sprites_num() == 0){
					player.set_sprites_num(7);
				}else
				if(player.get_sprites_num() == 7){
					player.set_sprites_num(8);
				}else
				if(player.get_sprites_num() == 8){
					player.set_sprites_num(0);
				}else{
					player.set_sprites_num(0);
				}

				//muda direção
				player.set_direction(direction);

			}else
			if(p_s){ //Colisão com super biscoito
				//Remove Biscuit
				map<pair<int, int>, char>::iterator it;
				it = g_map.get_s_biscuits()->find(b_pos[0]);
				g_map.get_s_biscuits()->erase(it);

				//Aumenta número biscoitos jogador
				player.set_eaten_biscuits(player.get_eaten_biscuits() + 1);

				//Move pac-man [Baixo: +1 i]
				g_map.set_map_at(player.get_i(), player.get_j(), '0');
				player.set_j(player.get_j() - 1);
				g_map.set_map_at(player.get_i(), player.get_j(), '3');

				//verifica super
				player.fill_super_force();

				//Define sprite
				if(player.get_sprites_num() == 0){
					player.set_sprites_num(7);
				}else
				if(player.get_sprites_num() == 7){
					player.set_sprites_num(8);
				}else
				if(player.get_sprites_num() == 8){
					player.set_sprites_num(0);
				}else{
					player.set_sprites_num(0);
				}

				//muda direção
				player.set_direction(direction);

			}else
			if(p_i){
				//Move pac-man [Baixo: +1i]
				g_map.set_map_at(player.get_i(), player.get_j(), '0');
				player.set_j(player.get_j() - 1);
				g_map.set_map_at(player.get_i(), player.get_j(), '3');

				//verifica super
				player.decrease_super_force();

				//Define sprite
				if(player.get_sprites_num() == 0){
					player.set_sprites_num(7);
				}else
				if(player.get_sprites_num() == 7){
					player.set_sprites_num(8);
				}else
				if(player.get_sprites_num() == 8){
					player.set_sprites_num(0);
				}else{
					player.set_sprites_num(0);
				}

				//Pega o item
				player.set_item(7);

				//muda direção
				player.set_direction(direction);
			}else{
				//Move pac-man [Baixo: +1i]
				g_map.set_map_at(player.get_i(), player.get_j(), '0');
				player.set_j(player.get_j() - 1);
				g_map.set_map_at(player.get_i(), player.get_j(), '3');

				//verifica super
				player.decrease_super_force();

				//Define sprite
				if(player.get_sprites_num() == 0){
					player.set_sprites_num(7);
				}else
				if(player.get_sprites_num() == 7){
					player.set_sprites_num(8);
				}else
				if(player.get_sprites_num() == 8){
					player.set_sprites_num(0);
				}else{
					player.set_sprites_num(0);
				}

				//muda direção
				player.set_direction(direction);
			}

			return true;

		}else{
			if(last_try){
				//Define sprite
				player.set_sprites_num(8);
				//Verifica super
				player.decrease_super_force();
			}

			return false;
		}
		break;
	}
}
