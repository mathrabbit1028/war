#include <bits/stdc++.h>
#include <variant>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define c first
#define f second

ll S = 19999, s;
int Q;

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
    return solve(round((double)ha*S/s), hf, round((double)ga*S/s), gf);
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

mt19937 engine((unsigned int)time(NULL));
uniform_real_distribution<double> distribution(0, 1);
auto generator = bind(distribution, engine);

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

node* select_node(node* now) {
    if (now->l == NULL && now->r != NULL) {
        now->l = new node();
        now->l->p = now;
        now->l->ha = now->ga - now->ha;
        now->l->hf = now->gf;
        now->l->ga = now->ha;
        now->l->gf = now->hf;
        return now->l;
    }
    if (now->l != NULL && now->r == NULL) {
        now->r = new node();
        now->r->p = now;
        now->r->ha = now->ga;
        now->r->hf = now->gf - 1;
        now->r->ga = now->ha + s;
        now->r->gf = now->hf;
        return now->r;
    }
    if (now->l == NULL && now->r == NULL) {
        // select extend diraction : always l
        now->l = new node();
        now->l->p = now;
        now->l->ha = now->ga - now->ha;
        now->l->hf = now->gf;
        now->l->ga = now->ha;
        now->l->gf = now->hf;
        return now->l;
        
    }
    if (now->l != NULL && now->r != NULL) {
        // select next node, UCT
        double l_weight = (double)(now->l->lose) / now->l->tot 
            + sqrt(2 * log(now->l->tot) / now->tot);
        double r_weight = (double)(now->r->lose) / now->r->tot 
            + sqrt(2 * log(now->r->tot) / now->tot);
        if (generator() * (l_weight + r_weight) <= l_weight) return select_node(now->l);
        else return select_node(now->r);
    }
}

void backpropagate(node* sel, int res) {
    if (sel == NULL) return;
    sel->tot += 1;
    sel->win += res;
    sel->lose += 1-res;
    backpropagate(sel->p, 1-res);
}

void monte_solve(pll h, pll g) {
    node* head = new node();

    ll ha = h.c - g.f * s, ga = g.c - h.f * s;
    ll hf = h.f, gf = g.f;

    int cnt = 0;
    while (true) {
        auto temp = transition((array<ll, 4>){ha, hf, ga, gf});
        if (temp.index() == 1) {
            printf("%d\n", (get<bool>(temp)+cnt)%2);
            return;
        }
        array<ll, 4> nxt = get<array<ll, 4>>(temp);
        if (nxt == (array<ll, 4>){ha, hf, ga, gf}) break;
        ha = nxt[0];
        hf = nxt[1];
        ga = nxt[2];
        gf = nxt[3];
        cnt++;
    }

    head->ha = ha;
    head->hf = hf;
    head->ga = ga;
    head->gf = gf;

    const int rep = 9;
    for (int j = 0; j < rep; j++) {
        // repeat below process
        node* sel = select_node(head);
        int res = query(sel->ha, sel->hf, sel->ga, sel->gf);
        backpropagate(sel, res);
    }
    printf("%d\n", (cnt+(head->win > head->lose))%2);

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