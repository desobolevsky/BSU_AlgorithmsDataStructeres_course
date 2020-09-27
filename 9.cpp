#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

/** Problem Statement: https://acm.bsu.by/courses/120/problems/1336/
 Имеется n деталей и 2m станков двух типов. Деталь обрабатывается в две стадии: сначала на станке первого типа,
 затем на станке второго типа. Любая деталь характеризуется двумя параметрами: временем обработки на станке первого типа
 и временем обработки на станке второго типа. Станок обрабатывает каждую деталь сразу, станков разных типов одинаковое число.
 Необходимо определить порядок обработки деталей на станках, когда все детали будут обработаны за минимальное время.

 Input:
 В первой строке находится число n деталей (1≤n≤300000). Во второй строке — число m станков одного типа (1≤m≤300000).
 Последующие n строк содержат по два неотрицательных вещественных числа, записанных через пробел,
 — время обработки каждой детали на станке первого и второго типа.

 Output:
 В первой строке выведите минимальное время, за которое детали можно обработать, с точностью до 5 разрядов после запятой.
 В каждой последующей строке в порядке назначения на станки выведите номер детали и номер станка, на который она назначена.
 Станки первого типа имеют номера от 1 до m, второго типа — от m+1 до 2m.
 Полученное время не должно быть больше удвоенного оптимального.

 Example:

 input.txt:
 5
 3
 2 3
 1 4
 4 2
 5 1
 2 2

 output.txt:
 8.00000
 1 1
 2 2
 5 3
 2 5
 3 2
 1 4
 5 6
 4 3
 3 4
 4 4

*/

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
    vector <component> v(n);
    for (int i = 0; i < n; ++i) {
        fscanf(fp, "%lf", &v[i].a);
        fscanf(fp, "%lf", &v[i].b);
        v[i].idx = i;
    }
    fclose(fp);
    sort(v.begin(), v.end(),
         [](const component &c1, const component &c2) { return min(c1.a, c2.b) < min(c1.b, c2.a); });
    vector <component> a, b;
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
    priority_queue < pair < int, pair < int, int >>, vector < pair < int, pair < int, int>>>, decltype(compare3) >
                                                                                              ans(compare3);
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

