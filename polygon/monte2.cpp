#include <bits/stdc++.h>
#include <variant>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define c first
#define f second

mt19937 engine((unsigned int)time(NULL));
uniform_real_distribution<double> distribution(0, 1);
auto generator = bind(distribution, engine);

ll S = 1000, s;
int Q;
double Cp = 0;

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

int query(ll ha, ll hf, ll ga, ll gf) {
    // return solve(floor((double)ha*S/s), hf, ceil((double)ga*S/s), gf)
    //     + solve(ceil((double)ha*S/s), hf, floor((double)ga*S/s), gf);
    return solve(floor((double)ha*S/s), hf, floor((double)ga*S/s), gf)
        + solve(floor((double)ha*S/s), hf, ceil((double)ga*S/s), gf)
        + solve(ceil((double)ha*S/s), hf, floor((double)ga*S/s), gf)
        + solve(ceil((double)ha*S/s), hf, ceil((double)ga*S/s), gf);
}

variant<array<ll, 4>, bool> transition(array<ll, 4> state) {
    ll ha = state[0], hf = state[1], ga = state[2], gf = state[3];
    
    if (ha + s * gf <= 0) return false;
    if (ga + s * hf <= 0) return true;

    ll t = max(ha, ga);
    if (t <= 0) {
        ll k = (-t)/s + 1;
        gf -= k; hf -= k;
        ha += k * s; ga += k * s;
    }

    if (ga >= s) return (array<ll, 4>){ga - ha, gf, ha, hf};
    if (ha >= s) return true;
    if (ha <= 0) return (array<ll, 4>){ga, gf - 1, ha + s, hf};
    if (ga <= 0) {
        if (gf == 0) {
            if (ga + (s - ha) * hf <= 0) return true;
            ll k = -ga / (s - ha);
            ga += k * (s - ha);
            hf -= k;
            return (array<ll, 4>){ga - ha, gf, ha, hf};
        }
        else return true;
    }
    if (gf == 0) return (array<ll, 4>){ga - ha, gf, ha, hf};
    if (ha + (s - ga) * gf >= s) return true;
    if (hf > 0) {
        ll needa = (s * (hf - 1) + ga) / (hf + 1);
        ll need = min(gf, (max(0LL, needa - ha) + s - ga - 1) / (s - ga));
        gf -= need;
        ha += need * (s - ga);
    }
    if (gf == 0) return (array<ll, 4>){ga - ha, gf, ha, hf};
    if (two_step(ha, hf, ga, gf)) return true;

    return state;
}

struct node {
    ll ha, hf, ga, gf;
    int tot, win, lose, turn;
    node* l;
    node* r;
    node* p;
    node() { 
        tot=0; win=0; lose=0; turn=0;
        p=NULL; l=NULL; r=NULL;
    }
};

void reset(node* now) {
    if (now->l) reset(now->l);
    if (now->r) reset(now->r);
    delete now;
}

void update_state(node* now) {
    while (true) {
        auto temp = transition((array<ll, 4>){now->ha, now->hf, now->ga, now->gf});
        if (temp.index() == 1) {
            return;
        }
        array<ll, 4> nxt = get<array<ll, 4>>(temp);
        if (nxt == (array<ll, 4>){now->ha, now->hf, now->ga, now->gf}) break;
        now->ha = nxt[0];
        now->hf = nxt[1];
        now->ga = nxt[2];
        now->gf = nxt[3];
        now->turn++;
        now->turn %= 2;
    }
}

node* select_node(node* now) {
    // if (now->ha + s * now->gf <= 0 || now->ga + s * now->hf <= 0) return NULL;

    if (now->l == NULL && now->r != NULL) {
        now->l = new node();
        now->l->p = now;
        now->l->ha = now->ga - now->ha;
        now->l->hf = now->gf;
        now->l->ga = now->ha;
        now->l->gf = now->hf;
        now->l->turn = (now->turn + 1) % 2;
        update_state(now->l);
        return now->l;
    }
    if (now->l != NULL && now->r == NULL) {
        now->r = new node();
        now->r->p = now;
        now->r->ha = now->ga;
        now->r->hf = now->gf - 1;
        now->r->ga = now->ha + s;
        now->r->gf = now->hf;
        now->r->turn = (now->turn + 1) % 2;
        update_state(now->r);
        return now->r;
    }
    if (now->l == NULL && now->r == NULL) {
        // now->tot = 0;
        // now->win = 0;
        // now->lose = 0;
        // select extend diraction : always l
        now->l = new node();
        now->l->p = now;
        now->l->ha = now->ga - now->ha;
        now->l->hf = now->gf;
        now->l->ga = now->ha;
        now->l->gf = now->hf;
        now->l->turn = (now->turn + 1) % 2;
        update_state(now->l);
        return now->l;
    }
    if (now->l != NULL && now->r != NULL) {
        // select next node, UCT
        double l_weight = (double)(now->turn == now->l->turn ? now->l->win : now->l->lose) / now->l->tot 
            + Cp*sqrt(2)*sqrt(2 * log(now->tot) / now->l->tot);
        double r_weight = (double)(now->turn == now->r->turn ? now->r->win : now->r->lose) / now->r->tot 
            + Cp*sqrt(2)*sqrt(2 * log(now->tot) / now->r->tot);
        if (generator() * (l_weight + r_weight) <= l_weight) return select_node(now->l);
        else return select_node(now->r);
    }
}

void backpropagate(node* sel, int res) {
    if (sel == NULL) return;
    sel->tot += 2; // ?
    if (sel->turn == 1) {
        sel->win += 4-res;
        sel->lose += res;
    }
    else {
        sel->win += res;
        sel->lose += 4-res;
    }
    backpropagate(sel->p, res);
}

void monte_solve(pll h, pll g) {
    node* head = new node();

    ll ha = h.c - g.f * s, ga = g.c - h.f * s;
    ll hf = h.f, gf = g.f;

    head->ha = ha;
    head->hf = hf;
    head->ga = ga;
    head->gf = gf;
    update_state(head);

    // printf("%d %d %d %d | %d\n", head->ha, head->hf, head->ga, head->gf, head->turn);

    const int rep = 999;
    for (int j = 0; j < rep; j++) {
        // repeat below process
        node* sel = select_node(head);
        // if (sel == NULL) break;
        int res = query(sel->ha, sel->hf, sel->ga, sel->gf);
        if (sel->turn == 1) res = 2 - res; // ?
        backpropagate(sel, res);
    }
    // printf("%d %d\n", head->win, head->lose);

    printf("%d\n", (head->turn + (head->win > head->lose)) % 2);

    reset(head);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> s >> Q;

    for (int i = 1; i <= Q; i++) {
        pll h, g;
        cin >> h.c >> h.f >> g.c >> g.f;
        monte_solve(h, g);
    }
    
    return 0;
}

// g++ -Wl,--stack,1000000000 --std=c++17 monte2.cpp -o monte2
// 238번 줄이랑 270번 줄 잘못 짰는데 왜 성능이 좋지???