/*
 * Outputs random token.
 *
 * Token contains latin letters and digits and have length 
 * between 1 and 1000 characters, inclusive.
 *
 * To generate different values, call "sgen.exe" with different parameters.
 * 
 * It is typical behaviour of testlib generator to setup randseed by command line.
 */

#include "testlib.h"
#include <iostream>

const int GENS = 30;
const double MIN_DUR = 0.1;

using namespace std;

struct spec {
    int weight;
    double delay_mean, delay_mult;
    double duration_mean, duration_mult;
    double deadline_mean, deadline_mult;
};

vector<spec> v;
int n, m;
int sum_weight;
spec aux;

double generate (double mean, double mult) {
    double sum = 0.;

    for (int i = 0; i < GENS; i++)
        sum += rnd.next(1.);
    sum /= (double) GENS;
    sum *= mult;

    return sum + mean;
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);

    cin >> n >> m;

    sum_weight = 0;

    for (int i = 0; i < m; i++) {
        cin >> aux.weight;
        cin >> aux.delay_mean >> aux.delay_mult;
        cin >> aux.duration_mean >> aux.duration_mult;
        cin >> aux.deadline_mean >> aux.deadline_mult;
        v.push_back(aux);
        sum_weight += aux.weight;
    }

    double t = 0.;

    for (int i = 0; i < n; i++) {
        int ty = rnd.next(0, sum_weight);
        int curr = 0;
        
        while (ty > v[curr].weight) {
            ty -= v[curr].weight;
            curr++;
        }

        t += generate(v[curr].delay_mean, v[curr].delay_mult);
        t = max(t, 0.);

        cout << t << " ";
        cout << rnd.next("[a-zA-Z0-9]{1,80}") << " ";

        double dr = max(generate(v[curr].duration_mean, v[curr].duration_mult), MIN_DUR);
        cout << dr << " ";
        t += dr;

        double de = max(generate(v[curr].deadline_mean, v[curr].deadline_mult), 0.);
        cout << de + t << endl; 
    }


    return 0;
}
