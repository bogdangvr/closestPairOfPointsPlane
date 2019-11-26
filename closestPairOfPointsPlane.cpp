#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector <pair <int, int> > v, vy;
pair <int, int> aux;
int n,x,y;

bool cmpX(pair <int, int> a, pair <int, int> b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	else {
		return a.first < b.first;
	}
}

bool cmpY(pair <int, int> a, pair <int, int> b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	else {
		return a.second < b.second;
	}
}

double distanta(pair <int, int> a, pair <int, int> b) {
	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

double min(double a, double b) {
	if (a < b) {
		return a;
	}
	return b;
}

double find(vector <pair <int, int> > v, vector <pair <int, int> > vy, int st, int dr) {
	if (st == dr-1) {
		return distanta(v[st],v[dr]);
	}
	if (st == dr - 2) {
		return min( min( distanta(v[st], v[dr]) , distanta(v[st], v[dr - 1]) ) , distanta(v[st+1], v[dr]) );
	}
	int mid = (dr - st) / 2 + st;

	vector <pair <int, int> > vst;
	vector <pair <int, int> > vdr;

	for (int i = st; i <= dr; i++) {
		if (vy[i-st].first <= v[mid].first) {
			vst.push_back(vy[i-st]);
		}
		else {
			vdr.push_back(vy[i-st]);
		}
	}

	double dist1, dist2, distMin;
	dist1 = find(v, vst, st, mid);
	dist2 = find(v, vdr, mid + 1, dr);
	distMin = min(dist1, dist2);
	int d = (int)distMin;
	d++;

	vector <pair <int, int> > fasie;
	for (int i = st; i <= mid - 1; i++){
		if (vy[mid-st].first - vy[i-st].first <= d)
			fasie.push_back(vy[i - st]);
	}

	for (int i = mid+1; i <= dr; i++) {
		if (vy[i - st].first - vy[mid - st].first <= d) {
			fasie.push_back(vy[i - st]);
		}
		else {
			break;
		}
	}

	for (int i = 0; i < fasie.size()-1; i++) {
		for (int j = i + 1; j < fasie.size() && j<=i+7; j++) {
			distMin = min(distMin, ((int)distanta(fasie[i], fasie[j])+1));
		}
	}
	return distMin;
}

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		aux = make_pair(x, y);
		v.push_back(aux);
		vy.push_back(aux);
	}
	
	sort(v.begin(), v.end(), cmpX);
	sort(vy.begin(), vy.end(), cmpY);
	cout << find(v, vy, 0, n-1);

	return 0;
}