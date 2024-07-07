#include <bits/stdc++.h>
#include "default.hpp"
using namespace std;
#define c first
#define f second

int S, Q;

void find(int i) {

    pll h, g;

    cin >> h.c >> h.f >> g.c >> g.f;

    h.c -= S * h.f;
    g.c -= S * g.f;

    int cnt = 0;
    while (true) {
        auto temp = transition((array<ll, 4>){h.c, h.f, g.c, g.f});
        if (temp.index() == 1) {
            // printf("Ans: %d\n", (get<bool>(temp)+cnt)%2);
            return;
        }
        array<ll, 4> nxt = get<array<ll, 4>>(temp);
        if (nxt == (array<ll, 4>){h.c, h.f, g.c, g.f}) break;
        h = {nxt[0], nxt[1]};
        g = {nxt[2], nxt[3]};
        cnt++;
    }

    printf("%d: %d %d %d %d\n", i, h.c, h.f, g.c, g.f);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("C:/Users/geon4/Documents/WAR/19999/in.txt", "r", stdin);

    cin >> S >> Q;

    init(S);

    for (int i = 1; i <= Q; i++) {
        find(i);
    }
    
    return 0;
}

// g++ -std=c++17 tree.cpp default.cpp -o tree