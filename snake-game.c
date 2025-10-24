#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>

//GAME CHARACTERS
#define SNAKE_BODY "O"
#define FOOD "@"
#define BORDER "#"


//BORDER LIMITS
#define X_MIN_BORDER 0
#define X_MAX_BORDER 41
#define Y_MIN_BORDER 0
#define Y_MAX_BORDER 41

void draw_border(int x_max, int x_min, int y_max, int y_min);
void update_snake(int *all_x_axis, int *all_y_axis, int snake_size);
void draw_snake(int *all_x_axis, int *all_y_axis, int snake_size);
void score(int y_pos, int x_pos, int score);
bool is_invalid_position(int *all_x_axis, int *all_y_axis, int snake_size);
void gen_valid_rand_food(int *foodX, int *foodY, int *all_x_axis, int *all_y_axis, int snake_size);



void main(){

	srand(time(NULL));

	int posX[(X_MAX_BORDER - X_MIN_BORDER - 1) * (Y_MAX_BORDER - Y_MIN_BORDER - 1)] = {0};
	int posY[(X_MAX_BORDER - X_MIN_BORDER - 1) * (Y_MAX_BORDER - Y_MIN_BORDER - 1)] = {0};
	int foodX = X_MIN_BORDER + 1 + (rand() % (X_MAX_BORDER - X_MIN_BORDER - 1));
	int foodY = Y_MIN_BORDER + 1 + (rand() % (Y_MAX_BORDER - Y_MIN_BORDER - 1));
	int dirX = 1;
	int dirY = 0;
	int snake_size = 1;
	bool game_over = false;

	//initial position
	posX[0] = X_MIN_BORDER + 1;
	posY[0] = Y_MIN_BORDER + 1;

	WINDOW* win = initscr();
	keypad(win, true);
	nodelay(win, true);

	while(!game_over){
		draw_border(X_MAX_BORDER, X_MIN_BORDER, Y_MAX_BORDER, Y_MIN_BORDER);
		int pressed = wgetch(win);

		if(pressed == KEY_LEFT){
			dirX = -1;
			dirY = 0;
		}

		if(pressed == KEY_RIGHT){
			dirX = 1;
			dirY = 0;
		}

		if(pressed == KEY_DOWN){
			dirX = 0;
			dirY = 1;
		}

		if(pressed == KEY_UP){
			dirX = 0;
			dirY = -1;
		}
		update_snake(posX, posY, snake_size);
		posX[0] += dirX;
		posY[0] += dirY;
		erase();
		draw_snake(posX, posY, snake_size);
		mvaddstr(foodY, foodX, FOOD);
		score(Y_MAX_BORDER + 3, X_MIN_BORDER, snake_size - 1);


		if(is_invalid_position(posX, posY, snake_size)) game_over = true;

		if(foodX == posX[0] && foodY == posY[0]){
			snake_size++;
			gen_valid_rand_food(&foodX, &foodY, posX, posY, snake_size);
		}

  		usleep(100000);
	}


	endwin();
}

void gen_valid_rand_food(int *foodX, int *foodY, int *all_x_axis, int *all_y_axis, int snake_size){
	bool invalid_rand_food = true;
	int flag;
	while(invalid_rand_food){
		flag = 1; // if '1', it's means that the generated value is a valid position for food
		*foodX = X_MIN_BORDER + 1 + (rand() % (X_MAX_BORDER - X_MIN_BORDER - 1));
		*foodY = Y_MIN_BORDER + 1 + (rand() % (Y_MAX_BORDER - Y_MIN_BORDER - 1));
		
		for(int i = 0; i < snake_size; i++) if(*foodX == all_x_axis[i] && *foodY == all_y_axis[i]) flag = 0;

		if(flag & 1) invalid_rand_food = false;
	}
}

void update_snake(int *all_x_axis, int *all_y_axis, int snake_size){
	int prevX = all_x_axis[0], prevY = all_y_axis[0];
	int tempX, tempY;
	for(int i = 1; i < snake_size; i++){
		
		//Updating X-axis values
		tempX = all_x_axis[i];
		all_x_axis[i] = prevX;
		prevX = tempX;

		//Updating Y-axis values
		tempY = all_y_axis[i];
		all_y_axis[i] = prevY;
		prevY = tempY;
	}
}

void draw_snake(int *all_x_axis, int *all_y_axis, int snake_size){
	for(int i = 0; i < snake_size; i++) mvaddstr(all_y_axis[i], all_x_axis[i], SNAKE_BODY);
}

bool is_invalid_position(int *all_x_axis, int *all_y_axis, int snake_size){
	int x_head = all_x_axis[0], y_head = all_y_axis[0];
	if(x_head == X_MIN_BORDER || x_head == X_MAX_BORDER || y_head == Y_MIN_BORDER || y_head == Y_MAX_BORDER) return true;

	for(int i = 1; i < snake_size; i++) if(all_x_axis[i] == x_head && all_y_axis[i] == y_head) return true;

	return false;
}

void score(int y_pos, int x_pos, int score){
	char buffer[256];
	sprintf(buffer, "SCORE: %d", score);
	mvaddstr(y_pos, x_pos, buffer);
}

void draw_border(int x_max, int x_min, int y_max, int y_min){
	//draw the X-axis borders
	for(int i = x_min; i < x_max; i++){
		mvaddstr(y_min, i, BORDER);
		mvaddstr(y_max, i, BORDER);
	}

	//draw the Y-axis borders
	for(int i = y_min; i < y_max; i++){
		mvaddstr(i, x_min, BORDER);
		mvaddstr(i, x_max, BORDER);
	}
}
