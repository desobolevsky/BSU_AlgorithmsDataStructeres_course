#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

/** Problem Statement: https://acm.bsu.by/solutions/381498/source/ = 403 Forbidden :( */

int m, n;

using namespace std;

void testprint(vector<vector<int>> v)
{
    for (int i = 0; i<v.size(); ++i) {
        for (int j = 0; j<v[0].size(); ++j) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

void foo(vector<int> v)
{
    for (int i = 0; i<v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int check(int ind, vector<int>& v)
{
    int count = 0;
    //X axis
    for (int i = ind; i<(ind/n+1)*n; i++) {
        if (v[i]==1) { break; }
        if (v[i]==0) {
            v[i] = 2;
            ++count;
        }
    }
    for (int i = ind; i>=(ind/n)*n; --i) {
        if (v[i]==1) { break; };
        if (v[i]==0) {
            v[i] = 2;
            ++count;
        }
    }
    //Y axis
    for (int j = ind; j<m*n; j += n) {
        if (v[j]==1) { break; }
        if (v[j]==0) {
            v[j] = 2;
            ++count;
        }
    }
    for (int j = ind; j>=0; j -= n) {
        if (v[j]==1) { break; }
        if (v[j]==0) {
            v[j] = 2;
            ++count;
        }
    }
    //XY axis
    for (int i = ind/n, j = ind%n; i<m && j<n; ++i, ++j) {
        if (v[i*n+j]==1) { break; };
        if (v[i*n+j]==0) {
            v[i*n+j] = 2;
            ++count;
        }
    }
    for (int i = ind/n, j = ind%n; i>=0 && j>=0; --i, --j) {
        if (v[i*n+j]==1) { break; };
        if (v[i*n+j]==0) {
            v[i*n+j] = 2;
            ++count;
        }
    }
    for (int i = ind/n, j = ind%n; i>=0 && j<n; --i, ++j) {
        if (v[i*n+j]==1) { break; };
        if (v[i*n+j]==0) {
            v[i*n+j] = 2;
            ++count;
        }
    }
    for (int i = ind/n, j = ind%n; i<m && j>=0; ++i, --j) {
        if (v[i*n+j]==1) { break; };
        if (v[i*n+j]==0) {
            v[i*n+j] = 2;
            ++count;
        }
    }
    return count;
}

int max_way;

vector<vector<int>> ways;

vector<int> order;

void put(int pos,
         vector<int>& v,
         int points_left,
         vector<int>& way)
{
    int count;
    vector<int> v_copy;
    for (int j = pos; j<order.size(); ++j) {
        v_copy = v;
        count = check(order[j], v_copy);
        if (count>0) {
            way.push_back(order[j]+1);
            if (points_left-count==0) {
                if (way.size()==max_way) {
                    ways.push_back(way);
                }
                else if (way.size()<max_way) {
                    max_way = way.size();
                    ways.clear();
                    ways.push_back(way);
                }
            }
            else if (way.size()!=max_way) {
                put(j+1, v_copy, points_left-count, way);
            }
            way.pop_back();
        }
    }
}


int main()
{
    int t, index_in;
    fstream fin("input.txt");
    fin >> m >> n >> t;
    vector<int> v(m*n, 0);
    for (int i = 0; i<t; ++i) {
        fin >> index_in;
        v[index_in-1] = 1;
    }
    for (int i = 0; i<m*n; ++i) {
        if (v[i]!=1) {
            order.push_back(i);
        }
    }
    vector<int> way;
    max_way = m*n-t;
    //cout << max_way << endl;

    put(0, v, m*n-t, way);
    FILE* fp_out;
    fp_out = fopen("output.txt", "w");
    for (auto& el : ways) {
        for (auto& number : el) {
            fprintf(fp_out, "%d ", number);
        }
        fprintf(fp_out, "%s", "\n");
    }
    int answer = ways.size();
    if (answer == 0){
        fprintf(fp_out, "%zu", 1);
    }
    else fprintf(fp_out, "%zu", answer);
    return 0;
}

