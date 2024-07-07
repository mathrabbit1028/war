#include <bits/stdc++.h>
#include <variant>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define c first
#define f second

ll S;

int getdp(ll hf, ll ga, ll gf);

bool two_step(ll ha, ll hf, ll ga, ll gf) {
    ll x = gf / 2;
    ha += (S - ga) * x;
    gf -= x;
    ll temp[4] = {ga - ha, gf, ha, hf};
    ha = temp[0]; hf = temp[1]; ga = temp[2]; gf = temp[3];

    ha += (S - ga) * gf;
    gf = 0;
    ll temp2[4] = {ga - ha, gf, ha, hf};
    ha = temp2[0]; hf = temp2[1]; ga = temp2[2]; gf = temp2[3];

    return ha + (S - ga) * gf >= S;
}

bool solve(ll ha, ll hf, ll ga, ll gf) {

    if (ha + S * gf <= 0) return false;
    if (ga + S * hf <= 0) return true;

    ll t = max(ha, ga);
    if (t <= 0) {
        ll k = (-t)/S + 1;
        gf -= k; hf -= k;
        ha += k * S; ga += k * S;
    }

    if (ga >= S) return !solve(ga - ha, gf, ha, hf);
    if (ha >= S) return true;
    if (ha <= 0) return !solve(ga, gf - 1, ha + S, hf);
    if (ga <= 0) {
        if (gf == 0) {
            if (ga + (S - ha) * hf <= 0) return true;
            ll k = -ga / (S - ha);
            ga += k * (S - ha);
            hf -= k;
            return !solve(ga - ha, gf, ha, hf);
        }
        else return true;
    }
    if (gf == 0) return !solve(ga - ha, gf, ha, hf);
    if (ha + (S - ga) * gf >= S) return true;
    if (hf > 0) {
        ll needa = (S * (hf - 1) + ga) / (hf + 1);
        ll need = min(gf, (max(0LL, needa - ha) + S - ga - 1) / (S - ga));
        gf -= need;
        ha += need * (S - ga);
    }
    if (gf == 0) return !solve(ga - ha, gf, ha, hf);
    if (two_step(ha, hf, ga, gf)) return true;

    return ha >= getdp(hf, ga, gf);
}

bool safe(ll ha, ll hf, ll ga, ll gf) {
    if (ha + S * gf <= 0) return false;
    if (ga + S * hf <= 0) return true;
    if (ha <= 0) return !solve(ga, gf - 1, ha + S, hf);

    bool att = false, hac = false;
    att = !safe(ga - ha, gf, ha, hf);
    if (gf > 0) hac = !solve(ga, gf - 1, ha + S, hf);
    return (att | hac);
}

map< pair<ll, pll>, ll > dp;
int getdp(ll hf, ll ga, ll gf) {
    if (dp.find({hf, {ga, gf}}) != dp.end()) return dp[{hf, {ga, gf}}];
    ll st = 1, ed = S;
    while (st < ed) {
        ll ha = (st + ed) / 2;
        bool att = false, hac = false;
        att = !safe(ga - ha, gf, ha, hf);
        if (gf > 0) hac = !solve(ga, gf - 1, ha + S, hf);
        if (att | hac) ed = ha;
        else st = ha + 1;
    }
    dp[{hf, {ga, gf}}] = st;
    return st;
}

bool query(ll ha, ll hf, ll ga, ll gf) {
    return solve(ha, hf, ga, gf);
}

void init(ll s) {
    S = s;
    return;
}

variant<array<ll, 4>, bool> transition(array<ll, 4> state) {
    ll ha = state[0], hf = state[1], ga = state[2], gf = state[3];
    
    if (ha + S * gf <= 0) return false;
    if (ga + S * hf <= 0) return true;

    ll t = max(ha, ga);
    if (t <= 0) {
        ll k = (-t)/S + 1;
        gf -= k; hf -= k;
        ha += k * S; ga += k * S;
    }

    if (ga >= S) return (array<ll, 4>){ga - ha, gf, ha, hf};
    if (ha >= S) return true;
    if (ha <= 0) return (array<ll, 4>){ga, gf - 1, ha + S, hf};
    if (ga <= 0) {
        if (gf == 0) {
            if (ga + (S - ha) * hf <= 0) return true;
            ll k = -ga / (S - ha);
            ga += k * (S - ha);
            hf -= k;
            return (array<ll, 4>){ga - ha, gf, ha, hf};
        }
        else return true;
    }
    if (gf == 0) return (array<ll, 4>){ga - ha, gf, ha, hf};
    if (ha + (S - ga) * gf >= S) return true;
    if (hf > 0) {
        ll needa = (S * (hf - 1) + ga) / (hf + 1);
        ll need = min(gf, (max(0LL, needa - ha) + S - ga - 1) / (S - ga));
        gf -= need;
        ha += need * (S - ga);
    }
    if (gf == 0) return (array<ll, 4>){ga - ha, gf, ha, hf};
    if (two_step(ha, hf, ga, gf)) return true;

    return state;
}