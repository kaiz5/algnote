#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int clocks[10] = { 0 }, adjusted_clocks[10] = { 0 };
vector<int> perfect_adjust;

// Store minimum steps for each move
int op[10] = { 0 };

int move_counts[10] = { 0 };

const int operations[10][10] =
{
	{ 0 },
	//  A  B  C  D  E  F  G  H  I
{ 0, 1, 1, 0, 1, 1, 0, 0, 0, 0 },  //op1: ABDE
{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },  //op2: ABC
{ 0, 0, 1, 1, 0, 1, 1, 0, 0, 0 },  //op3: BCEF
{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },  //op4: ADG
{ 0, 0, 1, 0, 1, 1, 1, 0, 1, 0 },  //op5: BDEFH
{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 1 },  //op6: CFI
{ 0, 0, 0, 0, 1, 1, 0, 1, 1, 0 },  //op7: DEGH
{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },  //op8: GHI
{ 0, 0, 0, 0, 0, 1, 1, 0, 1, 1 }  //op9: EFHI
};

void operate(int op_num, int op_counts) {
	for (int k = 1; k = 9; k++) {
		adjusted_clocks[k] += operations[op_num][k] * op_counts;
		adjusted_clocks[k] %= 4;
	}
}

int guess() {
	op[4] = (4 - adjusted_clocks[1]) % 4;
	operate(4, op[4]);
	op[5] = (4 - adjusted_clocks[2]) % 4;
	operate(5, op[5]);
	op[6] = (4 - adjusted_clocks[3]) % 4;
	operate(6, op[6]);
	op[7] = (4 - adjusted_clocks[4]) % 4;
	operate(7, op[7]);
	op[9] = (4 - adjusted_clocks[6]) % 4;
	operate(9, op[9]);
	if (adjusted_clocks[5] == 0 && adjusted_clocks[7] == adjusted_clocks[8] &&
		adjusted_clocks[8] == adjusted_clocks[9])
	{
		op[8] = (4 - adjusted_clocks[7]) % 4;
		int steps = 0;
		for (int k = 1; k <= 9; k++) {
			steps += op[k];
		}
		return steps;
	}
	return 101;
}

int enumerate() {
	int c = 0;
	int minsteps = 101;
	int steps = 0;
	while (c < 64) {
		// Enumerate
		op[3] = c / 16;
		op[2] = c % 16 / 4;
		op[1] = c % 4;
		memcpy(adjusted_clocks, clocks, sizeof(clocks));

		//operate on clocks
		operate(3, op[3]);
		operate(2, op[2]);
		operate(1, op[1]);
		steps = guess();
		if (steps < minsteps) {
			minsteps = steps;
			perfect_adjust.clear();
			for (int k = 1; k <= 9; k++) {
				while (op[k]--) {
					perfect_adjust.push_back(k);
				}
			}
		}
		c++;
	}
	return minsteps;
}



int main() {
	for (int k = 1; k < 10; k++) {
		cin >> clocks[k];
	}
	if (enumerate() < 101) {
		for (int k = 0; k < perfect_adjust.size(); k++) {
			cout << perfect_adjust.at(k) << ' ';
		}
	}
	return 0;

}

