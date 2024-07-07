#include <bits/stdc++.h>
#include <variant>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

bool query(ll ha, ll hf, ll ga, ll gf);

void init(ll s);

variant<array<ll, 4>, bool> transition(array<ll, 4> state);