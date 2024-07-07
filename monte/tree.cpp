#include <bits/stdc++.h>
#include "default.hpp"
using namespace std;
#define c first
#define f second

ll s;
int Q;

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

void solve(pll h, pll g) {
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

    const int rep = 999;
    for (int j = 0; j < rep; j++) {
        // repeat below process
        node* sel = select_node(head);
        int res = query(sel->ha, sel->hf, sel->ga, sel->gf);
        backpropagate(sel, res);
    }
    printf("%lld\n", (cnt+(head->win > head->lose))%2);

    reset(head);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("C:/Users/geon4/Documents/WAR/19999/in.txt", "r", stdin);

    cin >> s >> Q;

    init(s);

    for (int i = 1; i <= Q; i++) {
        pll h, g;
        cin >> h.c >> h.f >> g.c >> g.f;
        solve(h, g);
    }
    
    return 0;
}

// g++ -std=c++17 tree.cpp default.cpp -o tree