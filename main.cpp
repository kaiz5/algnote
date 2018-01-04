#include<iostream>

// Guess wheter the puzzle has solution and return the steps to complete.
int guess(int n, int **puzzle, int **draw) {
	int steps = 0;
	for(int r = 1;r < n; r++)
		for (int c = 1; c < n + 1; c++)
		{
			draw[r + 1][c] = 
				(puzzle[r][c] + draw[r][c] + draw[r - 1][c] + draw[r][c - 1] + draw[r][c + 1]) % 2;
		}
	for (int c = 1; c < n + 1; c++)
	{
		if ((draw[n][c - 1] + draw[n][c] + draw[n][c + 1] + draw[n - 1][c]) % 2 != puzzle[n][c])
			return 1001;
	}

    // Calculation of steps.
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= n ; c++)
			if (draw[r][c] == 1)
				steps++;

	return steps;
}

// Enumerate on the combination of the first row of the draw array.
int enumerate(const int wallsize, int **puzzle, int **draw) {
	int minsteps = 1001;
	int steps = 0;
	int c;
	while (draw[1][wallsize + 1] < 1) {
		steps = guess(wallsize, puzzle, draw);
		if (steps < minsteps) {
			minsteps = steps;
		}
		draw[1][1]++;
		c = 1;
		while (draw[1][c] > 1) {
			draw[1][c] = 0;
			c++;
			draw[1][c]++;
		}
	}

	return minsteps;
}



int main()
{
	using namespace std;
	int n, minsteps;
	char color;
	cin >> n;

	// Creating 2 arrays for puzzles and solutions.
	int **puzzle = new int*[n + 1];
	int **draw = new int*[n + 1];

	for (int i = 0; i < n + 1; i++)
		puzzle[i] = new int[n + 2];

	for (int i = 0; i < n + 1; i++)
		draw[i] = new int[n + 2];

	//Initialize 2 arrays.
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < n + 2; j++)
		{
			puzzle[i][j] = 0;
			draw[i][j] = 0;
		}

	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++)
		{
			cin >> color;
			puzzle[i][j] = color == 'y' ? 0 : 1;
		}

	minsteps = enumerate(n, puzzle, draw);
	if (minsteps == 1001)
		cout << "inf" << endl;
	else
		cout << minsteps << endl;

	return 0;
}