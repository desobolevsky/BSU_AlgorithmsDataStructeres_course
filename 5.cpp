#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/** Problem Statement: https://acm.bsu.by/courses/120/problems/1572/ */

int rooms_number;

void swap(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

int find_max(const vector<int> &v) {
    int max = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

int find_set(vector<int> &v, int x) {
    if (v[x] == x) return x;
    else return v[x] = find_set(v, v[x]);
}

void make_union(vector<int> &v, vector<int> &size, int x, int y) {
    x = find_set(v, x);
    y = find_set(v, y);
    if (x != y) {
        --rooms_number;
        if (size[x] < size[y]) {
            swap(x, y);
        }
        v[y] = x;
        size[x] += size[y];
    }
}

void set_size(vector<int> &v, vector<int> &size, int x) {
    size[x] = size[v[x]];
}


int main() {
    ifstream fin("in");
    int m, n, tmp;
    fin >> m >> n;
    rooms_number = m * n;
    vector<int> v(m * n);
    for (int i = 0; i < v.size(); ++i) {
        v[i] = i;
    }
    vector<int> size(m * n, 1);
    int west, north, east, south;
    for (int i = 0; i < m * n; ++i) {
        fin >> tmp;
        west = tmp >> 0 & 1;
        north = tmp >> 1 & 1;
        east = tmp >> 2 & 1;
        south = tmp >> 3 & 1;
        if (i % n != 0 && west == 0) {
            make_union(v, size, i, i - 1);
        }
        if (i > n - 1 && north == 0) {
            make_union(v, size, i, i - n);
        }
        if (i + 1 % n != 0 && east == 0) {
            make_union(v, size, i, i + 1);
        }
        if (i < (m - 1) * n && south == 0) {
            make_union(v, size, i, i + n);
        }
    }

    for (int i = 0; i < m * n; ++i) {
        v[i] = find_set(v, i);
        set_size(v, size, i);
    }
    int p_max = 0;
    for (int i = 0; i < m * n; ++i) {
        if (i % n != 0) {
            if (find_set(v, i) != find_set(v, i - 1)) {
                p_max = max(p_max, size[i] + size[i - 1]);
            }
        }
        if (i > n - 1) {
            if (find_set(v, i) != find_set(v, i - n)) {
                p_max = max(p_max, size[i] + size[i - n]);
            }
        }
        if ((i + 1) % n != 0) {
            if (find_set(v, i) != find_set(v, i + 1)) {
                p_max = max(p_max, size[i] + size[i + 1]);
            }
        }
        if (i < (m - 1) * n) {
            if (find_set(v, i) != find_set(v, i + n)) {
                p_max = max(p_max, size[i] + size[i + n]);
            }
        }
    }
    ofstream fout("out");
    int ans = find_max(size);
    fout << rooms_number << endl << ans << endl;
    if (rooms_number == 1){
        fout<<ans<<endl;
    }
    else fout<<p_max<<endl;
    fout.close();
    return 0;
}

