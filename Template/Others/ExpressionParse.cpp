// 二元运算 左结合 
vector<char> rpn, ch, sta;
int pri(char ch) {
	if(ch == '(') return 0;
	// ...
	return -1;
}
char solve(string s) {
	rpn.clear(); ch.clear();
	rep(i, 0, sz(s)) {
		char c = s[i];
		if(c == '(') { ch.pb(c);
		} else if(c == ')') {
			while(ch.back() != '(') rpn.pb(ch.back()), ch.pop_back();
			ch.pop_back();
		} else if(pri(c) > 0) {
			while(sz(ch) && pri(ch.back()) >= pri(c)) rpn.pb(ch.back()), ch.pop_back();
			ch.pb(c);
		} else { rpn.pb(c); }
	}
	reverse(all(ch)); rpn.insert(rpn.end(), all(ch));
	sta.clear();
	rep(i, 0, sz(rpn)) {
		char u = rpn[i];
		if(pri(u) > 0) {
			char b = sta.back(); sta.pop_back();
			sta[sz(sta) - 1] = calc(u, sta.back(), b);
		} else { sta.pb(u); } 
	}
	return sta[0];
}
