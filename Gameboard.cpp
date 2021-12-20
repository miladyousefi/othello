#include <cstdio>
#include <iostream>
#include "Gameboard.h"

Othello::Othello(int size){
	if(size < 4 || size >24) return;

	this->size = size;
	this->score[0] = 0;
	this->score[1] = 0;
	this->score[2] = 0;
	this->status = 1;
	this->gameboard = new int*[size];
	for(int z = 0; z <= size; z++){
		this->gameboard[z] = new int[size];
	}

	for(int x = 0; x <= this->size; x++){ // loop for all rows
		for(int y = 0; y <= this->size; y++){ //loop for all columns
			this->set_slot(x,y,0); // set the slot to 0
		}
	}

	this->set_slot(size/2 - 1, size/2 - 1, 1);
	this->set_slot(size/2, size/2, 1);
	this->set_slot(size/2 - 1, size/2, 2);
	this->set_slot(size/2, size/2 - 1, 2);
}


int Othello::get_slot_status(int x, int y) const{
	if(x >= this->size || y >= this->size || x < 0 || y < 0){ return 0; }
	return this->gameboard[x][y];
}

int Othello::get_size() const{
	return this->size;
}


bool Othello::is_valid_move(int x, int y, int player) const{
	if(x >= this->size || y >= this->size || x < 0 || y < 0){ return 0; }
	if(get_slot_status(x,y) != 0){ return false; }
	return (this->flip_count(x,y,player) > 0)?true:false;
}

void Othello::set_slot(int x, int y, int player){
	if(x >= this->size || y >= this->size || x < 0 || y < 0){ return; }
	this->gameboard[x][y] = player;
	this->change_score(1,player);
}

int Othello::flip_count(int x, int y, int player) const{
	if(x >= this->size || y >= this->size || x < 0 || y < 0){ return 0; }
	int dir_x, dir_y, dist = 1, cur_x = x, cur_y = y, flip_count = 0;

	for(dir_x = -1; dir_x < 2; dir_x++){
		for(dir_y = -1; dir_y < 2; dir_y++){
			
			dist = 1;
			while(true){
				cur_x = x + (dist * dir_x);
				cur_y = y + (dist * dir_y);
			
				if(cur_x < 0 || cur_y < 0 || cur_x >= this->size || cur_y >= this->size){
					break;
				}
				
				if(gameboard[cur_x][cur_y] == 0){ break; }
				
				if(gameboard[cur_x][cur_y] == player){ flip_count += dist - 1; break; }
				
				if(dir_x == 0 && dir_y == 0){ break; }
				dist++;
			}
		}
	}
	return flip_count;
}

int Othello::flip_slots(int x, int y, int player){
	if(x >= this->size || y >= this->size || x < 0 || y < 0){ return 0; }
	
	int dir_x, dir_y, dist = 1, cur_x = x, cur_y = y, flip_count = 0;
	for(dir_x = -1; dir_x < 2; dir_x++){
		for(dir_y = -1; dir_y < 2; dir_y++){
			dist = 1;
			while(true){
				cur_x = x + (dist * dir_x);
				cur_y = y + (dist * dir_y);
				if(cur_x < 0 || cur_y < 0 || cur_x >= this->size || cur_y >= this->size){
					break;
				}
				if(gameboard[cur_x][cur_y] == 0){ break; }
				if(gameboard[cur_x][cur_y] == player){
					
					for(dist--; dist > 0; dist--){
						cur_x = x + (dist * dir_x);
						cur_y = y + (dist * dir_y);
						this->set_slot(cur_x, cur_y, player); 
						this->change_score(-1,(player == 1)?2:1);
					}
					break;
				}
				
				if(dir_x == 0 && dir_y == 0){ break; }
				dist++;
			}
		}
	}
	return flip_count;
}

bool Othello::make_move(int x, int y, int player){
	if(x >= this->size || y >= this->size || x < 0 || y < 0){ return false; }
	if(this->is_valid_move(x,y,player) == true){
		this->set_slot(x,y,player);
		this->flip_slots(x,y,player);
		return true;
	}else{
		return false;
	}
}


bool Othello::moves_exist(int player) const{
	int x,y;
	for(x = 0; x < this->size; x++){
		for(y = 0; y < this->size; y++){
			if(get_slot_status(x,y) != 0){ continue; }
			else if(this->flip_count(x,y,player) > 0){
				return true;
			}
		}
	}
	return false;
}

bool Othello::get_move(int player){
	int x, y;
	while(true){
		
		printf("\nPlayer %d's turn: \n",player);
		printf("Input x y: ");

		std::cin >> x >> y;
		std::cout << "("<<x<<","<<y<<")";
		if(std::cin.fail()){
			std::cin.clear();
			std::string garbage;
			std::getline(std::cin, garbage);
			printf("Invalid input: x value must be an integer.\n");
		}else if((x > this->size || x < 1) || (y > this->size || y < 1)){
			std::cin.clear();
			printf("Invalid input: x value but be between 0 and %d.\n",this->size-1);
		}else{
			
				bool move = this->make_move(x-1,y-1,player);
				if(move == false){
					printf("Invalid move, try again.\n");
					continue;
				}else{
					return true;
				}
		}
	
	}
}


int Othello::get_score(int player) const{
	return this->score[player];
}

bool Othello::get_status() const{
	return this->status;
}


void Othello::change_status(void){
	this->status = (this->status == 0)?1:0;
}


int Othello::count_free_slots() const{
	int x,y, count = 0;
	for(x = 0; x < this->size; x++){
		for(y = 0; y < this->size; y++){
			count += ((get_slot_status(x,y) == 0)?1:0);
		}
	}
	return count;
}


int Othello::count_player_slots(int player) const{
	int x, y, count = 0;
	for(x = 0; x < this->size; x++){
		for(y = 0; y < this->size; y++){
			count += ((get_slot_status(x,y) == player)?1:0);
		}
	}
	return count;
}

bool Othello::check_win(int player){
	if(this->count_free_slots() == 0){
		this->change_status();
		return true;
	}else if(this->moves_exist((player == 1)?2:1) == 0){
		this->change_status();
		return true;
	}else{
		return false;
	}
}


int Othello::determine_winner() const{
	int p1 = 0, p2 = 0;
	p1 = count_player_slots(1);
	p2 = count_player_slots(2);
	if(p1 == p2){ return 0; }
	else if(p1 > p2){ return 1; }
	else{ return 2; }
}


void Othello::change_score(int change, int player){
	this->score[player] += change;
}

void Othello::print_board(int player) const{
	printf("Current board:\n");
	printf("\n\t");
	for(int z = 0; z < this->size; z++){
		printf("%d  ",z);
	}
	printf("\n\n");
	for(int y = 0; y < this->size; y++){
		printf("   %d\t",y);
		for(int x = 0; x < this->size; x++){
			printf("%d  ",get_slot_status(x,y));
		}
		printf("\n");
	}

	printf("Valid move :");
	for(int i = 0; i < this->size; i++){
		for(int j = 0; j < this->size; j++){
			if(is_valid_move(i,j,player)==true){
					printf("(%d,%d)",i,j);
			}
		}
			
	}
	
	
	printf("\n");
	printf("%d  Free slots",count_free_slots());
	printf("\n");
}


void Othello::print_scores() const{
	printf("Current stats:\n");
	printf("Player 1 score: %d\n",get_score(1));
	printf("Player 2 score: %d\n\n",get_score(2));
}

Othello::~Othello() {
    delete [] this->gameboard;
}
