#include <bits/stdc++.h>
using namespace std;

const int K = 15;
const int N = 1<<K;
const double B = .125; // How much of free memory is used
const double L = .125; // How local are the processes

int n, // number of processes
    m, // access per process
    T, // Maximum time
    M, V, s, p; // physical and virtual memory limits, memory unit and page size

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

    for(int i=0;i<N;i++) {
        pt[i] = proc_time(gen);
        at[i] = i%V;
    }

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
        int wnd = min(.5*p + .25*p*normal(gen), b-1.);

        printf("%d p%05d %d %d", pt[i], i, tf, b);
        available -= b;
        used.insert(make_pair(tf, b));
        risk = min(risk, available);


        shuffle(at, at+N, gen);
        sort(at, at+m);

        uniform_int_distribution<int> fst_time(0, b-1);
        int t = fst_time(gen);

        printf(" %d %d", t, at[0]);
        for(int j=1;j<m;j++){
            int np = max(0, min(int(.5*wnd + .25*normal(gen)), wnd-1));
            if     (t + wnd/2 >= b) t = b - wnd/2 + np;
            else if(t - wnd/2 <  0) t = np;
            else                    t = t - wnd/2 + np;
            printf(" %d %d", t, at[i]);
        }
        puts("");
    }
}
