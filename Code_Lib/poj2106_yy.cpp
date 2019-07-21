#include<cstdio>
#include<vector>
#include<iostream>
#include<string>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;

vector<char> rpn, ch, sta;

int pri(char ch) {
	if(ch == '(') return 0;
	if(ch == '|') return 1;
	if(ch == '&') return 2;
	if(ch == '!') return 3;
	return -1;
}

int calc(char o, char a, char b = 'V') {
	if(o == '!') return "FV"[a != 'V'];
	if(o == '|') return "FV"[a == 'V' || b == 'V'];
	return "FV"[a == 'V' && b == 'V'];
}
bool isunary(char ch) {
	return ch == '!';
}
char solve(string s) {
	rpn.clear(); ch.clear();
	rep(i, 0, sz(s)) {
		char c = s[i];
		if(c == '(') {
			ch.pb(c);
		} else if(c == ')') {
			while(ch.back() != '(') rpn.pb(ch.back()), ch.pop_back();
			ch.pop_back();
		} else if(pri(c) > 0) {
			while(sz(ch) && pri(ch.back()) >= pri(c) && !isunary(c)) rpn.pb(ch.back()), ch.pop_back();
			ch.pb(c);
		} else if(c == ' ') {
		} else {
			rpn.pb(c);
		}
	}
	reverse(all(ch));
	rpn.insert(rpn.end(), all(ch));
	sta.clear();
	rep(i, 0, sz(rpn)) {
		char u = rpn[i];
		if(pri(u) > 0) {
			if(isunary(u)) {
				sta[sz(sta) - 1] = calc(u, sta.back());
			} else {
				char b = sta.back(); sta.pop_back();
				sta[sz(sta) - 1] = calc(u, sta.back(), b);
			}
		} else {
			sta.pb(u);
		} 
	}
	return sta[0];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int ca = 0;
	string s;
	while(getline(cin, s)) {
		cout << "Expression " << ++ca << ": " << solve(s) << endl;
	}
	return 0;
}
