#include <iostream>
#include <string>
#include <stack>

using namespace std;

string str;
int cursor;
stack<int> numbers;
stack<char> acts;

void deleteSpace(){
	string newStr = "";
	int cur = 0;

	while (cur != str.size()) {
		if (str[cur] != ' ')
			newStr += str[cur++];
		else
			cur++;
	}
	str = newStr;
}

int getNum() {
	int num = 0;
	while (str[cursor] >= '0' && str[cursor] <= '9') {
		num = num * 10 + str[cursor++] - 48;
	}
	return num;
}

void DoAct() {
	char act;
	int num1, num2, result = 0;

	num1 = numbers.top();
	numbers.pop();
	num2 = numbers.top();
	numbers.pop();
	act = acts.top();
	acts.pop();

	if (act == '+')
		result = num1 + num2;
	else if (act == '-')
		result = num2 - num1;
	else if (act == '*')
		result = num1 * num2;

	numbers.push(result);
}

void DoIfBePriorityAct() {
	if (!acts.empty() && acts.top() == '*') {
		DoAct();
	}
}

int main()
{
	cursor = 0;
	getline(cin, str);
	deleteSpace();
	
	while (cursor < str.size()) {
		if (str[cursor] >= '0' && str[cursor] <= '9') {
			numbers.push(getNum());
			DoIfBePriorityAct();
		}
		else {
			if (str[cursor] == ')') {
				while (!acts.empty() && acts.top() != '(')
					DoAct();

				acts.pop();
				cursor++;
				DoIfBePriorityAct();
			}else
				acts.push(str[cursor++]);
		}
	}
	
	while (!acts.empty()) {
		DoAct();
	}

	cout << numbers.top();
	
	system("pause");


}