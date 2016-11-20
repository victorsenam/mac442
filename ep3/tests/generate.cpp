#include <bits/stdc++.h>
using namespace std;

const int N = 2e6;
const double B = .125; // How much of free memory is used
const double S = .25; // How spread are the memory accesses

int n, // number of processes
    m, // access per process
    T, // Maximum time
    M, V, s, p; // physical and virtual memory limits, memory unit and page size
int accesses;

int available, risk;
int pt[N], at[N];
set<pair<int, int>> used;

int main(){
    uint32_t seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);

    scanf(" %d%d%d%d", &M, &V, &s, &p);
    scanf(" %d%d%d", &n, &m, &T);

    normal_distribution<double> normal(0,1);
    uniform_int_distribution<int> proc_time(0, T-1);

    for(int i=0;i<N;i++) pt[i] = proc_time(gen);

    printf("%d %d %d %d\n", M, V, s, p);
    sort(pt, pt+n);

    available = risk = V;
    for(int i=0;i<n;i++){
        while(!used.empty() && used.begin()->first < pt[i]){
            available += used.begin()->second;
            used.erase(used.begin());
        }

        int b   = B*fabs(normal(gen))*available;
        int tf  = pt[i] + (.9 + .1*normal(gen))*b;

        printf("%d p%05d %d %d", pt[i], i, tf, b);
        available -= b;
        used.insert(make_pair(tf, b));
        risk = min(risk, available);

        int _m = min(m, 1 + tf - pt[i]);
        assert(0 < _m);

        for(int j=0;j <= tf - pt[i];j++) at[j] = pt[i] + j;
        shuffle(at, at+tf-pt[i], gen);
        sort(at, at+_m);

        uniform_int_distribution<int> fst_access(0, b-1);
        int a = fst_access(gen);

        accesses += _m;
        printf(" %d %d", a, at[0]);
        for(int j=1;j<_m;j++){
            int da = max(0, min(int(.5*p + S*p*normal(gen)), p-1)),
                na = a - .5*p + da;
            assert(0 <= da && da < p);
            if     (na <  0) a = da;
            else if(b <= na) a = b - p + da; 
            else             a = na;
            a = max(0, min(a, b-1));
            assert(0 <= a && a < b);
            assert(pt[i] <= at[j] && at[j] <= tf);
            printf(" %d %d", a, at[j]);
        }
        puts("");
    }
    printf("[risk %d; accesses %d]\n", risk, accesses);
}
