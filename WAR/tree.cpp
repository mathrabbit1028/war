#include <bits/stdc++.h>
#include "default.hpp"
using namespace std;
#define c first
#define f second

mt19937 engine((unsigned int)time(NULL));
uniform_int_distribution<ll> distribution(0LL, 10);
auto generator = bind(distribution, engine);

struct node {
    pll h, g;
    int tot, win, lose, turn;
    node* l;
    node* r;
    node* p;
    node() { 
        tot=0; win=0; lose=0; turn=0; 
        p=NULL; l=NULL; r=NULL;
    }
};

node* head = new node();

node* select_node(node* now) {
    if (now->l == NULL && now->r != NULL) {
        now->l = new node();
        now->l->p = now;
        return now->l;
    }
    if (now->l != NULL && now->r == NULL) {
        now->r = new node();
        now->r->p = now;
        return now->r;
    }
    if (now->l == NULL && now->r != NULL) {
        // select extend diraction
    }
    if (now->l != NULL && now->r != NULL) {
        // select next node, UCT
    }
}

void backpropagate(node* sel, int res) {
    if (sel == NULL) return;
    sel->tot += 1;
    sel->win += res;
    sel->lose += 1-res;
    backpropagate(sel->p, 1-res);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init(30000);

    pll h = {generator(), 0}, g = {generator(), 0};
    printf("%d %d %d %d\n", h.c, h.f, g.c, g.f);

    int cnt = 0;
    while (true) {
        auto temp = transition((array<ll, 4>){h.c, h.f, g.c, g.f});
        if (temp.index() == 1) {
            printf("Ans: %d\n", get<bool>(temp));
            return 0;
        }
        array<ll, 4> nxt = get<array<ll, 4>>(temp);
        if (nxt == (array<ll, 4>){h.c, h.f, g.c, g.f}) break;
        h = {nxt[0], nxt[1]};
        g = {nxt[2], nxt[3]};
        cnt++;
    }

    // repeat below process
    node* sel = select_node(head);
    int res = query(sel->h, sel->g);
    backpropagate(sel, res);
    
    return 0;
}