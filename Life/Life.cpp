#include <iostream>
#include <vector>
#include <Windows.h>
#include <ctime>

using namespace std;

const int WIDTH = 60;
const int HEIGHT = 45;
const int MAX_COUNT_LIVE = 1000;
const int TIME_SLEEP = 1;

bool map[HEIGHT][WIDTH];

// {move_Y, move_X}
vector<pair<int, int>> access_move;

void setup() {
	access_move.push_back({ -1, -1 });
	access_move.push_back({ -1, 0 });
	access_move.push_back({ -1, 1 });
	access_move.push_back({ 0, -1 });
	access_move.push_back({ 0, 1 });
	access_move.push_back({ 1, -1 });
	access_move.push_back({ 1, 0 });
	access_move.push_back({ 1, 1 });
}

void setcur(const int& x, const int& y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

inline int getNumber(const int& x, const int& y){
	int all = 0;
	
	for (int i = 0; i < access_move.size(); i++) {
		int newY = access_move[i].first + y, newX = access_move[i].second + x;
		if (newX > -1 && newY > -1 && newX < WIDTH && newY < HEIGHT)
			all += map[newY][newX];
	}
	return all;
}

inline bool conditionLive(const int& value) {
	return value == 2 || value == 3;
}

inline bool conditionCome(const int& value) {
	return value == 3;
}

void clear() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			map[i][q] = false;
		}
	}
}

void render() {
	setcur(0, 0);
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			
			if (map[i][q])
				cout << '#';
			else
				cout << ' ';
		}
		cout << endl;
	}
}

void update() {
	int tempMap[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			tempMap[i][q] = getNumber(q, i);
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			if(map[i][q])
				map[i][q] = conditionLive(tempMap[i][q]);
			else
				map[i][q] = conditionCome(tempMap[i][q]);

		}
	}
}

void startLive() {
	srand(time(0));
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			map[i][q] = rand()%2;
		}
	}
}

bool check() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int q = 0; q < WIDTH; q++) {
			if (map[i][q])
				return true;
		}
	}
	return false;
}

int main() {
	int n = 0;
	setup();
	clear();
	int count = MAX_COUNT_LIVE;
	startLive();
	render();
	while (check() && count > 0) {
		update();
		Sleep(TIME_SLEEP);
		count--;
		render();

	}
	system("pause");
}