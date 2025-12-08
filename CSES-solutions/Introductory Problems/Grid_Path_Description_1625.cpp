/* problem statement text */
/*
CSES - Grid Path Description

Time limit: 1.00 s
Memory limit: 512 MB

There are 884188841888418 paths in a 7×77 \times 77×7 grid from the upper-left square to the lower-left square. Each path corresponds to a 484848-character description consisting of characters D (down), U (up), L (left) and R (right).
For example, the path

corresponds to the description DRURRRRRDDDLUULDDDLDRRURDDLLLLLURULURRUULDLLDDDD.
You are given a description of a path which may also contain characters ? (any direction). Your task is to calculate the number of paths that match the description.
Input
The only input line has a 484848-character string of characters ?, D, U, L and R.
Output
Print one integer: the total number of paths.
Example
Input:
??????R??????U??????????????????????????LD????D?

Output:
201
*/
#include <iostream>
using namespace std;
 
const int DIR_LEN = 4;
int dr[DIR_LEN] = {-1, 0, 1, 0};
int dc[DIR_LEN] = {0, 1, 0, -1};
const int PATH_LEN = 48;  // length of all possible paths
int p[PATH_LEN];
const int GRID_SIZE = 9;
// added border to all four sides so a 7x7 becomes a 9x9
bool onPath[GRID_SIZE][GRID_SIZE];
 
int tryPath(int pathIdx, int curR, int curC) {
	// Optimization 3
	if ((onPath[curR][curC - 1] && onPath[curR][curC + 1]) &&
	    (!onPath[curR - 1][curC] && !onPath[curR + 1][curC]))
		return 0;
	if ((onPath[curR - 1][curC] && onPath[curR + 1][curC]) &&
	    (!onPath[curR][curC - 1] && !onPath[curR][curC + 1]))
		return 0;
 
	if (curR == 7 && curC == 1) {  // reached endpoint before visiting all
		if (pathIdx == PATH_LEN) return 1;
		return 0;
	}
 
	if (pathIdx == PATH_LEN) return 0;
 
	int ret = 0;
	onPath[curR][curC] = true;
 
	// turn already determined:
	if (p[pathIdx] < 4) {
		int nxtR = curR + dr[p[pathIdx]];
		int nxtC = curC + dc[p[pathIdx]];
		if (!onPath[nxtR][nxtC]) ret += tryPath(pathIdx + 1, nxtR, nxtC);
	}
	// see Java solution for optimization 4 implementation
	else {  // iterate through all four possible turns
		for (int i = 0; i < DIR_LEN; i++) {
			int nxtR = curR + dr[i];
			int nxtC = curC + dc[i];
			if (onPath[nxtR][nxtC]) continue;
			ret += tryPath(pathIdx + 1, nxtR, nxtC);
		}
	}
	// reset and return
	onPath[curR][curC] = false;
	return ret;
}
 
int main() {
	string line;
	getline(cin, line);
 
	// convert path to ints
	for (int i = 0; i < PATH_LEN; i++) {
		char cur = line[i];
 
		if (cur == 'U') p[i] = 0;
		else if (cur == 'R') p[i] = 1;
		else if (cur == 'D') p[i] = 2;
		else if (cur == 'L') p[i] = 3;
		else p[i] = 4;  // cur == '?'
	}
 
	// set borders of grid
	for (int i = 0; i < GRID_SIZE; i++) {
		onPath[0][i] = true;
		onPath[8][i] = true;
		onPath[i][0] = true;
		onPath[i][8] = true;
	}
	// initialize the inside of the grid to be completely empty
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) { onPath[i][j] = false; }
	}
 
	int startIdx = 0;
	int startR = 1;
	int startC = 1;  // always start path at (1, 1)
	int ans = tryPath(startIdx, startR, startC);
	cout << ans << endl;
}