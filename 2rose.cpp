#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Square.h"
#include "LShape.h"
#include "LRShape.h"
#include "TShape.h"
#include "Line.h"
#include "Lightening.h"
#include "LighteningR.h"
using namespace std;

#define WIDTH 13
#define HEIGHT 25
#define SLEEP_TIME 300

enum DIRECTION{
	UP=1,LEFT=2,DOWN=3,RIGHT=4
};

DIRECTION direction = UP;
int rotate = 0;
Point cursor(0,0);
Shape *shape;
unsigned char **map;
bool generate_flag = true;
int sleep_time = SLEEP_TIME;

void gotoXY(int x,int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle,coord);
}

void init(){
	srand(time(0));
	map = new unsigned char*[HEIGHT+1];
	for(int i=0;i<=HEIGHT;i++){
		map[i] = new unsigned char[WIDTH+1];
		for(int j=0;j<=WIDTH;j++){
			if(i==0 || i == HEIGHT || j==0 || j == WIDTH) map[i][j] = '+';
			else map[i][j] = ' ';
		}
	}
}

void refresh(){
	gotoXY(0,0);
	for(int i=0;i<=HEIGHT;i++){
		for(int j=0;j<=WIDTH;j++){
			cout<<map[i][j];
		}
		cout<<endl;
	}
}

void control_mapping(char ch){
	switch(ch){
		case 'i':
		case 'I':
			direction = UP;
			sleep_time = SLEEP_TIME;
			rotate = 0;
			break;
		case 'j':
		case 'J':
			direction = LEFT;
			sleep_time = SLEEP_TIME;
			rotate = 0;
			break;
		case 'k':
		case 'K':
			direction = DOWN;
			sleep_time = 10;
			rotate = 0;
			break;
		case 'l':
		case 'L':
			direction = RIGHT;
			sleep_time = SLEEP_TIME;
			rotate = 0;
			break;
		case 'z':
		case 'Z':
			rotate = 1;
			break;
		case 'x':
		case 'X':
			rotate = 2;
			break;
			
	}
}

void check(){
	for(int i=HEIGHT-1;i>1;i--){
		bool flag = true;
		for(int j=1;j<WIDTH;j++){
			if(map[i][j]!='O')
				flag = false;
		}
		if(flag){
			for(int k=i-1;k>1;k--){
				for(int j=1;j<WIDTH;j++){
					map[k+1][j] = map[k][j];
				}	
			}
			i = i+1;
		}
		
	}	
}

void moving(){
	int next_x = cursor.getX();
	int next_y = cursor.getY();
	next_y++;
	if(!shape->touch(&map,next_x,next_y)){
		if(direction == LEFT){
			next_x--;
		}
		else if(direction == RIGHT){
			next_x++;
		}
		if(!shape->touch(&map,next_x,next_y)){
			cursor.setX(next_x);
			cursor.setY(next_y);
		}
		else{
			cursor.setY(next_y);
		}
		shape->updateCurrentShape(cursor.getX(),cursor.getY());
		shape->draw(&map);
	}
	else{
		shape->draw(&map);
		check();
		generate_flag = true;
		sleep_time = SLEEP_TIME;
	}
	direction = UP;
}

void rotateShape(){
	if(rotate == 1){
		shape->rotate(true);
	}
	else if(rotate == 2){
		shape->rotate(false);
	}
	rotate = 0;
}

void controller(){
	if(kbhit()) control_mapping(getch());
	
	shape->erase(&map);
	rotateShape();
	moving();
}

void generateShape(){
	if(generate_flag){
		cursor.setX(WIDTH/2);
		cursor.setY(1);
		delete(shape);
//		int rand_num = rand()%7;
		int rand_num = 0;
		if(rand_num == 0){
			shape = new Square(cursor.getX(),cursor.getY());
		}
		else if(rand_num == 1){
			shape = new LShape(cursor.getX(),cursor.getY());
		}
		else if(rand_num == 2){
			shape = new LRShape(cursor.getX(),cursor.getY());
		}
		else if(rand_num == 3){
			shape = new TShape(cursor.getX(),cursor.getY());
		}
		else if(rand_num == 4){
			shape = new Line(cursor.getX(),cursor.getY());
		}
		else if(rand_num == 5){
			shape = new Lightening(cursor.getX(),cursor.getY());
		}
		else if(rand_num == 6){
			shape = new LighteningR(cursor.getX(),cursor.getY());
		}
		shape->draw(&map);
		generate_flag = false;
	}
}

int main(){
	init();
	int count = 0;
	while(1){
		generateShape();
		controller();
		refresh();
		Sleep(sleep_time);
	}
	
	return 0;
}
