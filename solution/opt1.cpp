#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define c first
#define f second

int q;
ll s;
const int X = 2000;

int dp[8080][8080];
bool trans(ll ha, ll hf, ll ga, ll gf) {
    if (ha + s * gf <= 0) return false;
    if (ga + s * hf <= 0) return true;

	ll t = max(ha, ga);
    if (t < 0) {
        ll k = (-t)/s;
        gf -= k; hf -= k;
        ha += k * s; ga += k * s;
    }

    if (ga >= s) return !trans(ga - ha, gf, ha, hf);
    if (ha >= s) return true;
    if (ha <= 0) return !trans(ga, gf - 1, ha + s, hf);
    if (ga <= 0) {
        if (gf == 0) {
            if (ga + (s - ha) * hf <= 0) return true;
            ll k = -ga / (s - ha);
            ga += k * (s - ha);
            hf -= k;
            return !trans(ga - ha, gf, ha, hf);
        }
        else return true;
    }
	if (gf == 0) return !trans(ga - ha, gf, ha, hf);

    if (dp[ha + hf * s][ga + gf * s] != -1) return dp[ha + hf * s][ga + gf * s];

    bool att = false, hac = false;
    att = !trans(ga - ha, gf, ha, hf);
    if (gf > 0) hac = !trans(ga, gf - 1, ha + s, hf);
    return dp[ha + hf * s][ga + gf * s] = (int)(att | hac);
}

void init() {
    for (int i = 0; i <= 2*X; i++) {
        for (int j = 0; j <= 2*X; j++) {
            dp[i][j] = -1;
        }
    }

    return;
}

bool solve(ll ha, ll hf, ll ga, ll gf) {
    if (ha + s * gf <= 0) return false;
    if (ga + s * hf <= 0) return true;

    ll t = max(ha, ga);
    if (t < 0) {
        ll k = (-t)/s;
        gf -= k; hf -= k;
        ha += k * s; ga += k * s;
    }

    if (ga >= s) return !solve(ga - ha, gf, ha, hf);
    if (ha >= s) return true;
    if (ha <= 0) return !solve(ga, gf - 1, ha + s, hf);
    if (ga <= 0) {
        if (gf == 0) {
            if (ga + (s - ha) * hf <= 0) return true;
            ll k = -ga / (s - ha);
            ga += k * (s - ha);
            hf -= k;
            return !solve(ga - ha, gf, ha, hf);
        }
        else return true;
    }
	if (gf == 0) return !solve(ga - ha, gf, ha, hf);

    return trans(ha, hf, ga, gf);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> s >> q;

    init();

    while (q--) {
        pll g, h;
        cin >> h.c >> h.f >> g.c >> g.f;
        ll ha = h.c - g.f * s, ga = g.c - h.f * s;
        if (solve(ha, h.f, ga, g.f)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}