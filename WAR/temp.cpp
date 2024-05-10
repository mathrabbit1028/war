#include <bits/stdc++.h>
using namespace std;

int arr[9] = {6, 5, 8, 4, 3, 1, 2, 9, 7};
int cnt;

int main() {
    int a[9];

    for (int i = 0; i < 9; i++) a[i] = arr[i];
    cnt = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 1; j < 9-i; j++) {
            if (a[j-1] > a[j]) {
                cnt++;
                swap(a[j-1], a[j]);
            }
        }
    }
    for (int i = 0; i < 9; i++) cout << a[i] << " ";
    cout << cnt << "\n";

    for (int i = 0; i < 9; i++) a[i] = arr[i];
    cnt = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 9; j++) {
            if (a[j-1] > a[j]) {
                cnt++;
                swap(a[j-1], a[j]);
            }
        }
    }
    for (int i = 0; i < 9; i++) cout << a[i] << " ";
    cout << cnt << "\n";

    for (int i = 0; i < 9; i++) a[i] = arr[i];
    cnt = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i-1; j >= 1; j--) {
            if (a[j-1] > a[j]) {
                cnt++;
                swap(a[j-1], a[j]);
            }
        }
    }
    cout << cnt << "\n";

    for (int i = 0; i < 9; i++) a[i] = arr[i];
    cnt = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 8; j > i; j--) {
            if (a[j-1] > a[j]) {
                cnt++;
                swap(a[j-1], a[j]);
            }
        }
    }
    cout << cnt << "\n";

}