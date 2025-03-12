#define _CRT_SECURE_NO_WARNINGS
#define MAX 100001
#define INF 2100000000

#include<bits/stdc++.h>

using namespace std;
int N;
string sarr[MAX];
int arr[10][6];
int prefix[MAX][6][10];		// [i][j][k]: i+1 ~ N까지의 j자리 수 k의 개수
int dprefix[MAX][6];			// [i][j]: i+1 ~ N까지의 j자리 수에서 sarr[i][j]보다 작은 숫자의 개수

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> sarr[i];
		for (int j = 0; j < 6; j++) {
			int t = sarr[i][j] - '0';
			arr[t][j]++;
		}
	}

	for (int i = N - 1; i >= 1; i--) {
		for (int j = 0; j < 6; j++) {
			int t1 = sarr[i + 1][j] - '0';	// i+1번째 포함
			prefix[i][j][t1] = 1;

			for (int k = 0; k < 10; k++) {
				prefix[i][j][k] += prefix[i + 1][j][k];
			}

			int t2 = sarr[i][j] - '0';
			// t2보다 작은 수
			for (int k = 0; k < t2; k++) {
				dprefix[i][j] += prefix[i][j][k];
			}
		}
	}

	long long res = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 6; j++) {
			res += dprefix[i][j];
		}
	}

	long long tres = res;
	for (int i = 1; i <= N; i++) {

		for (int j = 0; j < 6; j++) {
			int t = sarr[i][j] - '0';

			for (int k = 0; k < t; k++) {
				tres -= arr[k][j];
			}

			for (int k = t + 1; k < 10; k++) {
				tres += arr[k][j];
			}
		}

		res = min(res, tres);
	}

	cout << res;
	return 0;
}