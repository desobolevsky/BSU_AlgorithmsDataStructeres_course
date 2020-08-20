#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <float.h>
#include <iomanip>

/** Problem Statement: https://acm.bsu.by/courses/120/problems/772/ */

using namespace std;

auto compare = [](const pair<vector<int>, long double> &p1, const pair<vector<int>, long double> &p2) {
    return p1.second > p2.second;
};

int main() {
    int n, m;
    FILE *fp;
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);
    vector<vector<pair<int, double>>> v(2 * n);
    int v1, v2, type;
    double w;
    for (int i = 0; i < m; ++i) {
        fscanf(fp, "%d", &v1);
        fscanf(fp, "%d", &v2);
        fscanf(fp, "%d", &type);
        fscanf(fp, "%lf", &w);
        v[(v1 - 1) * 2 + type].push_back({(v2 - 1) * 2 + type, w});
        v[(v2 - 1) * 2 + type].push_back({(v1 - 1) * 2 + type, w});
    }
    int i_st, i_end;
    fscanf(fp, "%d", &i_st);
    fscanf(fp, "%d", &i_end);
    fclose(fp);
    vector<long double> weight(2 * n, LDBL_MAX);
    vector<bool> used(2 * n, false);
    weight[(i_st - 1) * 2] = 0;
    weight[(i_st - 1) * 2 + 1] = 0;

    priority_queue<pair<vector<int>, long double>, vector<pair<vector<int>, long double>>, decltype(compare)> q(
            compare);
    for (int i = 0; i < v[(i_st - 1) * 2].size(); ++i) {
        int v_new = v[(i_st - 1) * 2][i].first;
        long double dist_new = v[(i_st - 1) * 2][i].second;
        if (!used[v_new] && dist_new < weight[v_new]) {
            weight[v_new] = dist_new * 1.1;
            q.push({{(i_st - 1) * 2, i, v_new}, dist_new * 1.1});
        }
    }
    for (int i = 0; i < v[(i_st - 1) * 2 + 1].size(); ++i) {
        int v_new = v[(i_st - 1) * 2 + 1][i].first;
        long double dist_new = v[(i_st - 1) * 2 + 1][i].second + 0;
        if (!used[v_new] && dist_new < weight[v_new]) {
            weight[v_new] = dist_new * 1.1;
            q.push({{(i_st - 1) * 2 + 1, i, v_new}, dist_new * 1.1});
        }
    }
    weight[(i_st - 1) * 2] = LDBL_MAX;
    weight[(i_st - 1) * 2 + 1] = LDBL_MAX;

    int v_cur, v_2_cur;
    long double dist_cur;
    pair<vector<int>, long double> p;
    while (!q.empty()) {
        p = q.top();
        q.pop();

        v_cur = p.first[2];
        dist_cur = p.second;

        used[v_cur] = true;

        if (weight[v_cur] < p.second) {
            continue;
        }

        for (int i = 0; i < v[v_cur].size(); ++i) {
            int v_new = v[v_cur][i].first;
            long double dist_new = v[v_cur][i].second + dist_cur;
            if (!used[v_new] && dist_new < weight[v_new]) {
                weight[v_new] = dist_new;
                q.push({{v_cur, i, v_new}, dist_new});
            }
        }
        if (v_cur % 2 == 1) {
            v_2_cur = v_cur - 1;
        } else v_2_cur = v_cur + 1;
        for (int i = 0; i < v[v_2_cur].size(); ++i) {
            int v_new = v[v_2_cur][i].first;
            long double dist_new = v[v_2_cur][i].second * 1.1 + dist_cur;
            if (!used[v_new] && dist_new < weight[v_new]) {
                weight[v_new] = dist_new;
                q.push({{v_2_cur, i, v_new}, dist_new});
            }
        }
    }
    
    FILE *fp_out;
    fp_out = fopen("output.txt", "w");
    if (min(weight[(i_end - 1) * 2], weight[(i_end - 1) * 2 + 1]) != LDBL_MAX) {
        fprintf(fp_out, "%s", "Yes\n");
        fprintf(fp_out, "%0.2Lf", min(weight[(i_end - 1) * 2], weight[(i_end - 1) * 2 + 1]));
    } else fprintf(fp_out, "%s", "No\n");
    fclose(fp_out);
    return 0;
}

