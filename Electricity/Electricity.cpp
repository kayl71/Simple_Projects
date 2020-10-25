#include <iostream>
#include <vector>
#include <Windows.h>
#include <ctime>

using namespace std;

const int HEIGHT = 7;
const int WIDTH = 7;
const int TIME_SLEEP = 500;
const int MAX_COUNT = 100;

int map[HEIGHT][WIDTH];

enum {
	EMPTY = 0,
	WIRE,
	ELECTRICITY_START,
	ELECTRICITY_FINISH,
};

char charMap[] = {' ', '*', '#', ':'};

int dx[] = {1, 0, -1, 0};
int dy[] = { 0, 1, 0, -1};

void clear() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			map[i][q] = EMPTY;
		}
	}
}

void setcur(const int& x, const int& y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void update() {
	int tempMap[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			if (map[i][q] == ELECTRICITY_START) {
				tempMap[i][q] = ELECTRICITY_FINISH;
				for (int z = 0; z < 4; z++) {
					int newX = q + dx[z], newY = i + dy[z];
					if (newX > -1 && newY > -1 && newX < WIDTH && newY < HEIGHT) {
						if (map[newY][newX] == WIRE) {
							tempMap[newY][newX] = ELECTRICITY_START;
						}
					}
				}
			}
			else if (map[i][q] == ELECTRICITY_FINISH) 
				tempMap[i][q] = WIRE;
			else {
				if(tempMap[i][q] != ELECTRICITY_START)
					tempMap[i][q] = map[i][q];
			}
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			map[i][q] = tempMap[i][q];
		}
	}
}

void render() {
	setcur(0, 0);
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			cout << charMap[map[i][q]];
		}
		cout << '\n';
	}
}

int main()
{
	clear();

	// Example:
	map[0][0] = WIRE;
	map[0][1] = WIRE;
	map[0][2] = WIRE;
	map[1][2] = WIRE;
	map[2][2] = WIRE;
	map[2][0] = WIRE;
	map[2][1] = WIRE;
	map[1][0] = WIRE;
	map[2][3] = WIRE;
	map[2][4] = WIRE;
	map[2][5] = WIRE;
	map[1][5] = WIRE;
	map[0][4] = WIRE;
	map[0][5] = WIRE;
	map[0][3] = WIRE;
	map[0][0] = ELECTRICITY_START;
	map[0][1] = ELECTRICITY_FINISH;

	int count = MAX_COUNT;
	while (count > 0) {
		render();
		update();
		Sleep(TIME_SLEEP);
		count--;
	}
}