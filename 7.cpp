#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/** Problem Statement: https://acm.bsu.by/courses/120/problems/3177/ */

using namespace std;

struct edge
{
    int to_ind;
    int price;
};

const int INF = 10e4;

int main()
{
    ifstream fin("walk.in");
    int n, m, s, t;
    fin >> m >> n;
    vector<char> v(m * n);
    for (int i = 0; i < m * n; ++i) {
        fin >> v[i];
        if (v[i] == 'M') {
            v[i] = '.';
            s = i;
        }
        if (v[i] == 'G') {
            v[i] = '.';
            t = i;
        }
    }
    vector<vector<edge>> g(m * n); //0 up 1 right 2 down 3 right
    for (int i = 0; i < m * n; ++i) {
        if (v[i] != '*') {
            if (i % n != 0 && v[i - 1] == '.') {
                g[i].push_back({i - 1, 1});
            }
            if (i > (n - 1) && v[i - n] == '.') {
                g[i].push_back({i - n, 1});
            }
            if ((i + 1) % n && v[i + 1] == '.') {
                g[i].push_back({i + 1, 1});
            }
            if (i < (m - 1) * n && v[i + n] == '.') {
                g[i].push_back({i + n, 1});
            }
        }
    }


    int sum = 0;
    //I
    vector<int> p(m * n, -1);
    vector<int> weight(m * n, INF);
    weight[s] = 0;
    for (;;) {
        bool any = false;
        for (int j = 0; j < m * n; ++j) {
            for (int k = 0; k < g[j].size(); ++k) {
                if (weight[g[j][k].to_ind] > weight[j] + 1) {
                    weight[g[j][k].to_ind] = weight[j] + 1;
                    p[g[j][k].to_ind] = j;
                    any = true;
                }
            }
        }
        if (!any) break;
    }
    vector<int> path;
    for (int cur = t; cur != -1; cur = p[cur])
        path.push_back(cur);
    for (int i = 0; i < path.size() - 1; ++i) {
        for (int j = 0; j < g[path[i]].size(); ++j) {
            if (g[path[i]][j].to_ind == path[i + 1]) {
                g[path[i]][j].price = -1;
            }
        }
    }
    reverse(path.begin(), path.end());

//    cout << "Path: ";
//    for (size_t i = 0; i < path.size(); ++i)
//        cout << path[i] << ' ';
//    cout<<endl;

    for (int i = 0; i < path.size() - 1; ++i) {
        for (int j = 0; j < g[path[i]].size(); ++j) {
            if (g[path[i]][j].to_ind == path[i + 1]) {
                sum += g[path[i]][j].price;
                g[path[i]][j].price = INF;
            }
        }
    }
//    for (int i = 0; i < m * n; ++i) {
//        for (auto el : g[i]) {
//            cout << i << " " << el.to_ind << " " << el.price << endl;
//        }
//    }

    //II
    std::fill(p.begin(), p.end(), -1);
    std::fill(weight.begin(), weight.end(), INF);
    weight[s] = 0;
    for (;;) {
        bool any = false;
        for (int j = 0; j < m * n; ++j) {
            for (int k = 0; k < g[j].size(); ++k) {
                if (weight[g[j][k].to_ind] > weight[j] + g[j][k].price) {
                    weight[g[j][k].to_ind] = weight[j] + g[j][k].price;
                    p[g[j][k].to_ind] = j;
                    any = true;
                }
            }
        }
        if (!any) break;
    }

    path.clear();
    for (int cur = t; cur != -1; cur = p[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size() - 1; ++i) {
        for (int j = 0; j < g[path[i]].size(); ++j) {
            if (g[path[i]][j].to_ind == path[i + 1]) {
                sum += g[path[i]][j].price;
            }
        }
    }
    ofstream fout("walk.out");
    if (weight[t] == INF){
        fout<<-1<<endl;
    }
    else{
        fout<<sum<<endl;
    }
//    cout << "Path: ";
//    for (size_t i = 0; i < path.size(); ++i)
//        cout << path[i] << ' ';
//    cout<<endl;

    return 0;
}

