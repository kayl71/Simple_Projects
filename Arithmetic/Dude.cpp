#include <iostream>
#include <string>
#include <stack>

using namespace std;

string str;
int cursor;

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

int main()
{
	cursor = 0;
	getline(cin, str);
	deleteSpace();
	
	stack<int> numbers;
	stack<char> acts;
	while (cursor < str.size()) {
		if (str[cursor] >= '0' && str[cursor] <= '9') {
			numbers.push(getNum());
			if (!acts.empty() && acts.top() == '*') {
				int num1, num2;

				num1 = numbers.top();
				numbers.pop();
				num2 = numbers.top();
				numbers.pop();
				acts.pop();

				numbers.push(num1 * num2);
			}
		}
		else {
			if (str[cursor] == ')') {
				while (!acts.empty() && acts.top() != '(') {
					int num1, num2;

					num1 = numbers.top();
					numbers.pop();
					num2 = numbers.top();
					numbers.pop();
					if (acts.top() == '+')
						numbers.push(num1 + num2);
					else if (acts.top() == '-')
						numbers.push(num1 - num2);
					acts.pop();
				}
				cursor++;
			}else
				acts.push(str[cursor++]);
		}
	}

	while (!acts.empty()) {
		int num1, num2;

		num1 = numbers.top();
		numbers.pop();
		num2 = numbers.top();
		numbers.pop();
		if (acts.top() == '+')
			numbers.push(num1 + num2);
		else if(acts.top() == '-')
			numbers.push(num1 - num2);
		acts.pop();
	}

	cout << numbers.top();
	
	system("pause");


}