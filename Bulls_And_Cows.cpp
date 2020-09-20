#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_NUM_LEN = 4;

struct ans {
	int bulls, cows;
};

int CreateNumber() {
	vector<int> numMassive(10);
	for (int i = 0; i < 10; i++)
		numMassive[i] = i;
	for (int i = 0; i < numMassive.size(); i++) {
		swap(numMassive[i], numMassive[rand() % numMassive.size()]);
	}
	int num, numFirst;
	numFirst = numMassive.back();
	numMassive.pop_back();
	if (numFirst == 0) {
		num = numMassive.back();
		numMassive.pop_back();
		numMassive.push_back(0);
	}
	else
		num = numFirst;

	for (int i = 1; i < MAX_NUM_LEN; i++) {
		num = num * 10 + numMassive.back();
		numMassive.pop_back();
	}
	return num;
}

ans PlayerAns(int guessNum, int playerAns) {
	ans compAns = {0, 0};
	vector<int> compNums(MAX_NUM_LEN);
	vector<int> playerNums(MAX_NUM_LEN);
	for (int i = 0; i < MAX_NUM_LEN; i++) {
		compNums[i] = guessNum % 10;
		playerNums[i] = playerAns % 10;
		guessNum /= 10;
		playerAns /= 10;
		compAns.bulls += (compNums[i] == playerNums[i]);
	}
	for (int i = 0; i < MAX_NUM_LEN; i++) {
		bool checkTrue = false;
		for (int s = 0; s < MAX_NUM_LEN; s++) {
			if (compNums[i] == playerNums[s]) {
				checkTrue = true;
				break;
			}
		}
		compAns.cows += checkTrue;
	}
	compAns.cows -= compAns.bulls;
	return compAns;
}

int main()
{
	srand(time(0));
	int guessNum = CreateNumber();
	int playerAns = -1;
	int attempt = 0;
	while (playerAns != guessNum) {
		cout << "Write your guess number\n->";
		cin >> playerAns;
		ans compAns = PlayerAns(guessNum, playerAns);
		cout << "<" << compAns.cows << "> cows and <" << compAns.bulls<<"> bulls\n";
		attempt++;
	}
	cout << "You are win! Number = " << guessNum<<".\n"<<"Count attempts = "<<attempt<<"\n";
	system("pause");
}
