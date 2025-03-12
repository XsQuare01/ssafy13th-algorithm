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
		// ������ - leaf node�ΰ�?
		if (t == 1) {
			if (edge[k].size() == 1) {
				cout << "no\n";
			}
			else {
				cout << "yes\n";
			}
		}
		// ������ - Ʈ���� ����Ŭ�� �����Ƿ� �׻� �´�
		else if (t == 2) {
			cout << "yes\n";
		}
	}

	return 0;
}