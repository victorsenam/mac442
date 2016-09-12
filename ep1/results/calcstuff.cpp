#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 40;

double sa, sb;
double da, db;
double a[N], b[N];
int n;

inline double sq (double a) {
    return a*a;
}

int main (int argc, char * argv[]) {
    while (scanf("%lf %lf", &a[n], &b[n]) != EOF) {
        sa += a[n];
        sb += b[n];
        n++;
    }

    sa /= n;
    sb /= n;

    for (int i = 0; i < n; i++) {
        da += sq(sa - a[i]);
        db += sq(sb - b[i]);
    }

    da /= n;
    db /= n;

    da = sqrt(da);
    db = sqrt(db);
    
    double mul = 1.96 / sqrt(30);

    if (argc < 2) {
        printf("Mudanças de Contexto    : %4.5f %4.5f %4.5f\n", sa, da, mul*da);
        printf("Deadlines não cumpridos : %4.5f %4.5f %4.5f\n", sb, db, mul*db);
    } else if (argv[1][0] == '0') 
        printf("%f,%f\n", sa, mul*da);
    else if (argv[1][0] == '1')
        printf("%f,%f\n", sb, mul*db);
}
