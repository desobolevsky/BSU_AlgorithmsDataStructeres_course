#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

/** Problem Statement: https://acm.bsu.by/courses/120/problems/1336/ */

using namespace std;

struct component {
    int idx;
    double a, b;
};

int main() {

    int m, n;
    FILE *fp;
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);
    vector<component> v(n);
    for (int i = 0; i < n; ++i) {
        fscanf(fp, "%lf", &v[i].a);
        fscanf(fp, "%lf", &v[i].b);
        v[i].idx = i;
    }
    fclose(fp);
    sort(v.begin(), v.end(),
         [](const component &c1, const component &c2) { return min(c1.a, c2.b) < min(c1.b, c2.a); });
    vector<component> a, b;
    for (int i = 0; i < n; ++i)
        (v[i].a < v[i].b ? a : b).push_back(v[i]);
    a.insert(a.end(), b.rbegin(), b.rend());

    vector<double> first(m, 0), second(m, 0);
    auto compare1 = [&first](const int &i1, const int &i2) {
        return first[i1] > first[i2];
    };

    auto compare2 = [&second](const int &i1, const int &i2) {
        return second[i1] > second[i2];
    };
    priority_queue<int, vector<int>, decltype(compare1)> q1(compare1);
    priority_queue<int, vector<int>, decltype(compare2)> q2(compare2);
    for (int i = 0; i < m; ++i) {
        q1.push(i);
        q2.push(i);
    }
    int i1, i2;
    auto compare3 = [](const pair<int, pair<int, int>> &p1, const pair<int, pair<int, int>> &p2) {
        return p1.first > p2.first;
    };
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, decltype(compare3)> ans(compare3);
    for (int i = 0; i < n; ++i) {
        i1 = q1.top(), i2 = q2.top();
        q1.pop();
        q2.pop();

        ans.push({first[i1], {a[i].idx, i1 + 1}});
        first[i1] += a[i].a;
        ans.push({max(first[i1], second[i2]), {a[i].idx, i2 + m + 1}});
        second[i2] = max(first[i1], second[i2]) + a[i].b;

        q1.push(i1);
        q2.push(i2);
    }
    while (q2.size() != 1) {
        q2.pop();
    }
    FILE *fp_out;
    fp_out = fopen("output.txt", "w");
    fprintf(fp_out, "%0.5lf\n", second[q2.top()]);
    while (!ans.empty()) {
        auto el = ans.top();
        ans.pop();
        fprintf(fp_out, "%d ", el.second.first + 1);
        fprintf(fp_out, "%d\n", el.second.second);
    }
    fclose(fp_out);
    return 0;
}

