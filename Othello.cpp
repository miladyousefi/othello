#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "Gameboard.h"
#include "AIPlayer.h"
using namespace std;

int get_board_size();
int select_player();
int select_play_mode();
void play_against(int size);
void play_ai(int size);
void play_ai_to_ai(int size);

/*
 * Main function
 *
 */
int main(int argc, char * argv[]) {
	int status;
	int size, arg = 0;
	cout << "1 - Start Game\n"<<"2 - Set bord size\n"<<"3 - Quit\n";
	cin>> status;
	if (status==1){
		size=8;
	}
	if (status==2){
		size = get_board_size();
	}
	if(status==3){
		return 0;
	}
	
	
	if(argv[1]){ arg = strtol(argv[1],NULL,10); }
	if(arg > 3 && arg % 2 == 0){
		size = arg;
	}
	printf(" Board size is: %d x %d\n", size, size);

	
	int mode = select_play_mode();
	if(mode == 2){
		int level;
		printf("1 - Simple \n2 - Smart\n");
		std::cin>>level;
		play_ai(size);
		
	}else if(mode == 3){
		play_ai_to_ai(size);
	}else{
		play_against(size);
	}

	cin.sync();
	cin.get();


	return 0;
}

int get_board_size(){
	while(true){
		printf("Input size of board: ");
		int value;
		cin >> value;
		if(cin.fail()){
			cin.clear();
			string garbage;
			std::getline(std::cin, garbage);
			printf("Invalid input: board size must be an integer.\n");
		}else if(value % 2 != 0 || value == 0){
			cin.clear();
			printf("Invalid input: board size must be even.\n");
		}else{
			return value;
		}
	}
}

int select_play_mode(){
	printf("Select play mode :\n 1 - Multiplayer\n 2 - Play with AI\n 3 - AI with AI \n ");
	while(true){
		int value;
		cin >> value;
		if(cin.fail()){
			cin.clear();
			string garbage;
			std::getline(std::cin, garbage);
			printf("Invalid input: play mode must be an integer.\n");
		}else if(value != 1 && value != 2 && value != 3){
			cin.clear();
			printf("Invalid input: play mode must be 1, 2 or 3.\n");
		}else{
			return value;
		}
	}
}

void play_against(int size){
	printf("Creating game object...\n");
	// create game object
	Othello game(size);
	printf("Game object successfully created.\n\n");
	printf("Player 1's turn:\n");
	game.print_board(1);
	while(game.get_status() != 0){
		game.get_move(1);
		game.print_board(1);
		game.print_scores();
		if(game.check_win(1) == true){ break; }
		game.get_move(2);
		game.print_board(1);
		game.print_scores();
		if(game.check_win(2) == true){ break; }
	}
	if(game.get_status() == 0){
		printf("Game over !\n");
		printf("Player 1 score: %d\n",game.get_score(1));
		printf("Player 2 score: %d\n",game.get_score(2));
		if(game.determine_winner() == 0){
			printf("Player 1 and Player 2 have TIED.\n");
		}else{
			printf("Player %d WINS!\n",game.determine_winner());
		}
	}
	
}

void play_ai(int size){
	printf("Creating game object...\n");
	// create game object
	Othello game(size);
	printf("Game object successfully created.\n");
	// create AI object
	printf("Creating AI object...\n");
	AIPlayer ai(game,2);
	printf("AI object successfully created.\n\n");
	printf("Player 1's turn:\n");
	game.print_board(2);
	while(game.get_status() != 0){
		game.get_move(1);
		game.print_board(2);
		game.print_scores();
		if(game.check_win(1) == true){ break; }
		ai.play();
		game.print_board(2);
		game.print_scores();
		if(game.check_win(2) == true){ break; }
	}
	if(game.get_status() == 0){
		printf("Game over !\n");
		printf("Player 1 score: %d\n",game.get_score(1));
		printf("Player 2 (AI) score: %d\n",game.get_score(2));
		int winner = game.determine_winner();
		if(winner == 0){
			printf("Player 1 and Player 2 have TIED.\n");
		}else{
			printf("Player %d WINS!\n",winner);
		}
	}
}

void play_ai_to_ai(int size){
	printf("Creating game object...\n");
	// create game object
	Othello game(size);
	printf("  [<<] Game object successfully created.\n");
	// create AI object
	printf("first AI object...\n");
	AIPlayer ai1(game,1,true);
	printf(" First AI object successfully created.\n\n");
	printf("Creating second AI object...\n");
	AIPlayer ai2(game,2,true);
	printf("Second AI object successfully created.\n\n");
	printf("Player 1's turn:\n");
	game.print_board(3);
	while(game.get_status() != 0){
		ai1.play();
		game.print_board(3);
		game.print_scores();
		if(game.check_win(1) == true){ break; }
		ai2.play();
		game.print_board(3);
		game.print_scores();
		if(game.check_win(2) == true){ break; }
	}
	if(game.get_status() == 0){
		game.print_board(3);
		game.print_scores();
		printf("Game over !\n");
		printf("Player 1 score: %d\n",game.get_score(1));
		printf("Player 2 score: %d\n",game.get_score(2));
		if(game.determine_winner() == 0){
			printf("Player 1 and Player 2 have TIED.\n");
		}else{
			printf("Player %d WINS by %d points!\n",game.determine_winner(),game.get_score((game.determine_winner() == 1)?1:2) - game.get_score((game.determine_winner() == 1)?2:1));
		}
	}
}
