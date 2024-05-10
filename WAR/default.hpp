#include <bits/stdc++.h>
#include <variant>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

bool query(pll h, pll g);

void init(ll S);

variant<array<ll, 4>, bool> transition(array<ll, 4> state);