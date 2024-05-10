#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define c first
#define f second

int q;
ll s;

int getdp(ll hf, ll ga, ll gf);

bool two_step(ll ha, ll hf, ll ga, ll gf) {
    ll x = gf / 2;
    ha += (s - ga) * x;
    gf -= x;
    ll temp[4] = {ga - ha, gf, ha, hf};
    ha = temp[0]; hf = temp[1]; ga = temp[2]; gf = temp[3];

    ha += (s - ga) * gf;
    gf = 0;
    ll temp2[4] = {ga - ha, gf, ha, hf};
    ha = temp2[0]; hf = temp2[1]; ga = temp2[2]; gf = temp2[3];

    return ha + (s - ga) * gf >= s;
}

bool solve(ll ha, ll hf, ll ga, ll gf) {

    if (ha + s * gf <= 0) return false;
    if (ga + s * hf <= 0) return true;

    ll t = max(ha, ga);
    if (t <= 0) {
        ll k = (-t)/s + 1;
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
    if (ha + (s - ga) * gf >= s) return true;
    if (hf > 0) {
        ll needa = (s * (hf - 1) + ga) / (hf + 1);
        ll need = min(gf, (max(0LL, needa - ha) + s - ga - 1) / (s - ga));
        gf -= need;
        ha += need * (s - ga);
    }
    if (gf == 0) return !solve(ga - ha, gf, ha, hf);
    if (two_step(ha, hf, ga, gf)) return true;

    return ha >= getdp(hf, ga, gf);
}

bool safe(ll ha, ll hf, ll ga, ll gf) {
    if (ha + s * gf <= 0) return false;
    if (ga + s * hf <= 0) return true;
    if (ha <= 0) return !solve(ga, gf - 1, ha + s, hf);

    bool att = false, hac = false;
    att = !safe(ga - ha, gf, ha, hf);
    if (gf > 0) hac = !solve(ga, gf - 1, ha + s, hf);
    return (att | hac);
}

map< pair<ll, pll>, ll > dp;
int getdp(ll hf, ll ga, ll gf) {
    if (dp.find({hf, {ga, gf}}) != dp.end()) return dp[{hf, {ga, gf}}];
    ll st = 1, ed = s;
    while (st < ed) {
        ll ha = (st + ed) / 2;
        bool att = false, hac = false;
        att = !safe(ga - ha, gf, ha, hf);
        if (gf > 0) hac = !solve(ga, gf - 1, ha + s, hf);
        if (att | hac) ed = ha;
        else st = ha + 1;
    }
    dp[{hf, {ga, gf}}] = st;
    return st;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> s >> q;

    while (q--) {
        pll g, h;
        cin >> h.c >> h.f >> g.c >> g.f;
        ll ha = h.c - g.f * s, ga = g.c - h.f * s;
        if (solve(ha, h.f, ga, g.f)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
