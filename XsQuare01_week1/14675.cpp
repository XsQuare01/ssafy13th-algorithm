#define _CRT_SECURE_NO_WARNINGS
#define MAX 100001
#include<bits/stdc++.h>

using namespace std;

int N, Q;
vector<int> edge[MAX];

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int t, k;
		cin >> t >> k;
		// 단절점 - leaf node인가?
		if (t == 1) {
			if (edge[k].size() == 1) {
				cout << "no\n";
			}
			else {
				cout << "yes\n";
			}
		}
		// 단절선 - 트리는 싸이클이 없으므로 항상 맞다
		else if (t == 2) {
			cout << "yes\n";
		}
	}

	return 0;
}