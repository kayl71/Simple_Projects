#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using u16 = uint16_t;
using u32 = uint32_t;

struct Big;
bool operator>(const Big& b1, const Big& b2);
int count_need_zeros(int x);

struct Big {
	static const int MAX = 1000000000;

	bool positive;
	std::vector<int> data;

	Big() {
		data = std::vector<int>(1, 0);
		positive = true;
	}

	Big(int size) {
		data = std::vector<int>(size, 0);
		positive = true;
	}

	Big(const Big& x) {
		data = x.data;
		positive = x.positive;
	}

	void _rebuild() {
		int size = data.size();
		for (int i = 0; i < size-1; i++) {
			if (data[i] >= MAX) {
				data[i] = data[i] - MAX;
				data[i + 1]++;
			}
			else if (data[i] < 0) {
				data[i] = MAX + data[i]; // MAX - abs(data[i])
				data[i + 1]--;
			}
		}
		if (data[size - 1] >= MAX) {
			data.push_back(1);
			data[size - 1] = data[size - 1] - MAX;
		}
		else if (data[size - 1] == 0) {
			data.pop_back();
		}
	}

	int size() const{
		return data.size();
	}

	Big operator+(const Big& x) {
		int max_size = std::max(x.size(), size());
		Big temp;
		int k = 2*(this->positive == x.positive) - 1;

		if (*this > x) {
			temp = *this;
			for (int i = 0; i < x.size(); i++)
				temp.data[i] += k*x.data[i];
		}
		else {
			temp = x;
			for (int i = 0; i < this->size(); i++)
				temp.data[i] += k*this->data[i];
		}

		temp._rebuild();
		return temp;
	}
	
	Big operator-(const Big& x) {
		Big tx = x;
		tx.positive = !x.positive;
		return *this + tx;
			
	}
	Big operator=(const Big& x) {
		this->data = x.data;
		this->positive = x.positive;
		return *this;
	}
	Big operator+=(const int& x) {
		if (x >= MAX) {
			int k = x / MAX;
			if (size() == 1)
				data.push_back(k);
			else
				data[1] += k;
		}
		data[0] += x % MAX;
		_rebuild();
		return *this;
	}
	Big operator+(const int& x) {
		Big temp(*this);
		temp += x;
		temp._rebuild();
		return temp;
	}
	
};

void Print(Big x) {
	if (!x.positive)
		std::cout << '-';
	std::cout << x.data[x.size() - 1];
	if (x.size() == 1) {
		std::cout << '\n';
		return;
	}
	for(int i = x.size()-2; i>=0; i--){
		for (int j = 0; j < count_need_zeros(x.data[i]); j++)
			std::cout << '0';
		std::cout << x.data[i];
	}
	std::cout << '\n';
}

int count_need_zeros(int x) {
	int k = 8;
	if(x == 0)
		return 9;
	while (x / 10 > 0) {
		k--;
		x /= 10;
	}
	return k;
}

bool operator>(const Big& b1, const Big& b2) {
	if (b1.size() != b2.size())
		return b1.size() > b2.size();

	for (int i = b1.size() - 1; i >= 0; i--) {
		if (b1.data[i] != b2.data[i])
			return b1.data[i] > b2.data[i];
	}
	return false;
}

int main() {
	Big x, y;
	for(int i = 0; i<1000000; i++)
		x += INT32_MAX;

	y += 1;
	Big c = y - x;
	Print(x);
	Print(y);
	Print(c);
	std::cout << c.positive;
}
