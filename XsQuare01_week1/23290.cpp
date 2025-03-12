#define _CRT_SECURE_NO_WARNINGS
#define MAX 4
#define DMAX 8
#include<bits/stdc++.h>

using namespace std;

int M, S;
int original_arr[MAX][MAX][DMAX];	// [i][j][k]: {j, i}에서 k방향을 보고 있는 물고기 마릿수
int copy_arr[MAX][MAX][DMAX];
int fish_blood[MAX][MAX];
int Y, X;

// 물고기의 움직임
int fish_darr[][2] = {
	{0, -1},
	{-1, -1},
	{-1, 0},
	{-1, 1},
	{0, 1},
	{1, 1},
	{1, 0},
	{1, -1}
};

// 상어의 움직임
int shark_darr[][2] = {
	{-1, 0},
	{0, -1},
	{1, 0},
	{0, 1}
};

inline bool inBoundary(int y, int x) {
	return y >= 0 && x >= 0 && y < MAX && x < MAX;
}

pair<int, string> DFS(int y, int x, int cnt, int value, string path) {
	if (cnt == 3) {
		return { value, path };
	}

	int dir = 0;
	pair<int, string> ret = { -1, "" };
	for (auto [dy, dx] : shark_darr) {
		dir++;
		int ty = y + dy;
		int tx = x + dx;
		int tarr[DMAX];

		if (!inBoundary(ty, tx)) {
			continue;
		}

		int v = 0;
		for (int i = 0; i < DMAX; i++) {
			v += copy_arr[ty][tx][i];

			tarr[i] = copy_arr[ty][tx][i];
			copy_arr[ty][tx][i] = 0;
		}
		auto tret = DFS(ty, tx, cnt + 1, value + v, path + (char)(dir + '0'));
		if (tret.first > ret.first
			|| (tret.first == ret.first && tret.second < ret.second)) {
			ret = tret;
		}

		for (int i = 0; i < DMAX; i++) {
			copy_arr[ty][tx][i] = tarr[i];
		}
	}

	return ret;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		int x, y, d;
		cin >> y >> x >> d;
		original_arr[y - 1][x - 1][d - 1]++;
	}
	cin >> Y >> X;
	Y -= 1;
	X -= 1;

	for (int i = 0; i < S; i++) {
		// 1번 - 물고기 복제 마법
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < MAX; k++) {
				for (int l = 0; l < DMAX; l++) {
					copy_arr[j][k][l] = original_arr[j][k][l];
				}
			}
		}

		// 2번 - 물고기 돌리기
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < MAX; k++) {
				for (int l = 0; l < DMAX; l++) {
					// 물고기 없음
					if (!original_arr[j][k][l]) {
						continue;
					}

					// 물고기 방향 탐색
					for (int m = 0; m < DMAX; m++) {
						int dir = (DMAX + l - m) % DMAX;
						int ty = fish_darr[dir][0] + j;
						int tx = fish_darr[dir][1] + k;

						// 범위 밖
						if (!inBoundary(ty, tx)) {
							continue;
						}

						// 상어와 같은 위치
						if (ty == Y && tx == X) {
							continue;
						}

						// 물고기 피
						if (fish_blood[ty][tx]) {
							continue;
						}

						// 물고기 이동
						copy_arr[ty][tx][dir] += original_arr[j][k][l];
						copy_arr[j][k][l] -= original_arr[j][k][l];

						//Debug
						//cout << "Start: " << j << " " << k << " " << l << "\n";
						//cout << "End: " << ty << " " << tx << " " << dir << "\n\n";
						break;
					}
				}
			}
		}

		// 4번 - 물고기 흔적 지우기
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < MAX; k++) {
				if (!fish_blood[j][k]) {
					continue;
				}
				fish_blood[j][k] -= 1;
			}
		}

		// 3번 - 상어의 이동
		auto ret = DFS(Y, X, 0, 0, "");
		for (int j = 0; j < 3; j++) {
			int idx = ret.second[j] - '0';
			Y += shark_darr[idx - 1][0];
			X += shark_darr[idx - 1][1];

			// 상어 먹방
			int v = 0;
			for (int k = 0; k < DMAX; k++) {
				v += copy_arr[Y][X][k];

				copy_arr[Y][X][k] = 0;
			}

			// 물고기 흔적 발생
			if (v) {
				fish_blood[Y][X] = 2;
			}
		}

		// 5번 - 물고기 복제 완료
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < MAX; k++) {
				for (int l = 0; l < DMAX; l++) {
					original_arr[j][k][l] += copy_arr[j][k][l];
				}
			}
		}
	}

	int R = 0;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			for (int k = 0; k < DMAX; k++) {
				R += original_arr[i][j][k];
			}
		}
	}
	cout << R;
	return 0;
}