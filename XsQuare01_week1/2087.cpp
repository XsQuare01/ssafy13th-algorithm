#define _CRT_SECURE_NO_WARNINGS
#define MAX 40
#define INF 2000000000

#include<bits/stdc++.h>

using namespace std;

long long N, K;
long long arr[MAX];
vector<pair<long long, string>> vec;

int binarySearch(long long value) {
	int st = 0;
	int ed = vec.size();
	while (st <= ed) {
		int mid = (st + ed) / 2;
		if (vec[mid].first < value) {
			st = mid + 1;
			continue;
		}
		else if (vec[mid].first > value) {
			ed = mid - 1;
			continue;
		}
		return mid;
	}

	return -1;
}

void makeVector(int cnt, long long value, string s) {
	if (cnt == N / 2) {
		vec.push_back({ value, s });
		return;
	}

	long long v = arr[cnt];
	makeVector(cnt + 1, value + v, s + '1');
	makeVector(cnt + 1, value, s + '0');
}

string findVector(int cnt, long long value, string s) {
	if (cnt == N) {
		long long v = K - value;
		int idx = binarySearch(v);

		if (idx != -1) {
			string ns = vec[idx].second;
			return ns + s;
		}

		return "-1";
	}

	long long v = arr[cnt];
	string s1 = findVector(cnt + 1, value + v, s + '1');
	if (s1 != "-1") {
		return s1;
	}
	string s2 = findVector(cnt + 1, value, s + '0');
	if (s2 != "-1") {
		return s2;
	}
	return "-1";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	cin >> K;

	makeVector(0, 0, "");
	sort(vec.begin(), vec.end());
	cout << findVector(N / 2, 0, "");

	return 0;
}