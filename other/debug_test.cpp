#include <bits/stdc++.h>

using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

int main() {
	// Primitive data types
	bool a = true;
	debug(a);
	int b = 1;
	float c = 2.5;
	long long d = LLONG_MAX;
	char e = 'e';
	debug(a, b, c, d, e);
	
	// std::pair and std::string
	// You should only debug a pair of simple data types
	// The debug won't wark if one of pair's elements is collection type (std::vector, std::map, std::set...)
	pair<int, int> f = {1, 2};
	pair<string, bool> g = {"abcd", false};
	pair<char, float> h = {'x', 0.5};
	string i = "This is a string";
	pair<int, pair<int, int>> j = {1, {2, 3}};
	debug(f, g, h, i, j);
	
	// Collection types
	// Basically, the debug works with collections types which you can iterate by for (auto i: a)
	//So the debugger won't work with collection types like std::queue or std::stack
	vector<int> k = {1, 2, 3, 4};
	set<int> l = {1, 2, 2, 3, 3, 4, 4, 5};
	map<string, int> m;
	m["string 1"] = 1;
	m["string 2"] = 2;
	debug(k, l, m);
	
	unordered_map<string, int> n;
	n["string 3"] = 3;
	n["string 4"] = 4;
	multiset<int> o = {5, 5, 4, 3, 1, 1, 2};
	vector<vector<int>> p = {{1, 2, 3}};
	debug(n, o, p);

	// Expressions
	int q = 1;
	int r = 2;
	debug(q + r, q * r, q / r, q - r, q / (float) r, 2020, 2020 - 1);
	return 0;
}