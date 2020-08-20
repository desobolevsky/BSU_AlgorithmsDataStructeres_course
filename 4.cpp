#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/** Problem Statement: https://acm.bsu.by/courses/120/problems/3471/ */

using namespace std;

int find_set(vector<int> &v, int x){
    if (v[x] == x) return x;
    else return v[x] = find_set(v, v[x]);
}

void make_union(vector<int> &v, vector<int> &size, int x, int y){
    x = find_set(v, x);
    y = find_set(v, y);
    if (size[x] < size[y]){
        v[x] = y;
    }
    else{
        v[y] = x;
        if (size[x]==size[y]){
            ++size[x];
        }
    }
}

int main()
{
    ifstream fin("equal-not-equal.in");
    int n, m;
    fin >> n >> m;
    string t1, op, t2, ans = "Yes";
    vector<int> v(n+1);
    vector<int> size(n+1);
    for (int i = 0;i<v.size();++i){
        v[i] = i;
        size[i] = 1;
    }
    for (int i = 0; i<m; ++i) {
        fin >> t1 >> op >> t2;
        int index1 = stoi(t1.substr(1, t1.size()-1)), index2 = stoi(t2.substr(1, t2.size()-1));
        if (op == "=="){
            make_union(v, size, index1, index2);
        }
    }
    fin.clear();
    fin.seekg(0, ios::beg);
    fin >> n >> m;
    for (int i = 0; i<m; ++i) {
        fin >> t1 >> op >> t2;
        int index1 = stoi(t1.substr(1, t1.size()-1)), index2 = stoi(t2.substr(1, t2.size()-1));
        if (op == "!="){
            if (find_set(v, index1) == find_set(v, index2)){
                ans = "No";
                break;
            }
        }
    }
    fin.close();
    ofstream fout("equal-not-equal.out");
    fout << ans << endl;
    fout.close();
    return 0;
}

