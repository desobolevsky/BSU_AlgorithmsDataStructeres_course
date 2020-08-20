#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

/** Problem Statement: https://acm.bsu.by/courses/120/problems/2110/ */

using namespace std;

const int base = 1000 * 1000 * 1000;

void to_binary(vector<int> &v, const int &n, const int &number) {
    unsigned i;
    for (int i = 1 << n - 1, j = 0; i > 0; i = i / 2, ++j)
        (number & i) ? v[j] = 1 : v[j] = 0;
}

bool isGood(vector<int> &v1, vector<int> &v2) {
    for (int i = 0; i < v1.size() - 1; ++i) {
        if ((v1[i] == 0 && v1[i + 1] == 0 && v2[i] == 0 && v2[i + 1] == 0) ||
            (v1[i] == 1 && v1[i + 1] == 1 && v2[i] == 1 && v2[i + 1] == 1)) {
            return false;
        }
    }
    return true;
}

void multiply(vector<vector<int>> &a, const vector<vector<int>> &b,
              vector<vector<int>> &tmp) {
    size_t size = a.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tmp[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                tmp[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = tmp[i][j];
        }
    }
}

vector<vector<int>> multiply_copy(const vector<vector<int>> &v1, const vector<vector<int>> &v2) {
    int size = v1.size();
    vector<vector<int>> res(size, vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                res[i][j] += (v1[i][k] * v2[k][j])%10000;
                res[i][j] = res[i][j]%10000;
            }
        }
    }
    return res;
}


void power(vector<vector<int>> &a, int n) {
    for (int i = 0; i < n - 1; ++i) {
        a = multiply_copy(a, a);
    }
}

unsigned long long int getAmount(const vector<vector<int>> &v) {
    unsigned long long int amount = 0;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size(); ++j) {
            amount += v[i][j];
        }
    }
    return amount;
}

void divide(vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v.size(); ++j) {
            v[i][j] = v[i][j] % 10000;
        }
    }
}

//vector<vector<int>> power_mod(const vector<vector<int>> &a, int n) {
//    if (n == 0) {
//        vector<vector<int>> v(a.size(), vector<int>(a.size()));
//        for (int i = 0; i < v.size(); ++i) {
//            v[i][i] = 1;
//        }
//        return v;
//    };
//    if (n % 2 == 1) {
//        vector<vector<int>> new_a = a, tmp2(a.size(), vector<int>(a.size()));
//        //multiply(new_a, power_mod(new_a, n - 1), tmp2);
//        new_a = multiply_copy(new_a, power_mod(new_a, n - 1));
//        divide(new_a);
//        return new_a;
//    }
//    vector<vector<int>> D = power_mod(a, n / 2);
//    vector<vector<int>> tmp = D, tmp2(a.size(), vector<int>(a.size()));
//    //multiply(D, tmp, tmp2);
//    D = multiply_copy(D, D);
//    divide(D);
//    return D;
//}

vector<int> myminus(const vector<int> &a, vector<int> b){
    vector<int> v = a;
    int carry = 0;
    for (size_t i=0; i<b.size() || carry; ++i) {
        v[i] -= carry + (i < b.size() ? b[i] : 0);
        carry = v[i] < 0;
        if (carry)  v[i] += base;
    }
    while (v.size() > 1 && v.back() == 0)
        v.pop_back();
    return v;
}

vector<int> mydivide(const vector<int> &a, int del){
    vector<int> ans = a;
    int carry = 0;
    for (int i=(int)ans.size()-1; i>=0; --i) {
        long long cur = ans[i] + carry * 1ll * base;
        ans[i] = int (cur / del);
        carry = int (cur % del);
    }
    while (ans.size() > 1 && ans.back() == 0)
        ans.pop_back();
    return ans;
}

void print(const vector<int> &v){
    for (int i = v.size() - 1;i>=0;--i){
        cout<<v[i];
    }
    cout<<endl;
}

vector<vector<int>> power_mod(const vector<vector<int>> &a, vector<int> n){
    print(n);
    if (n.size() == 1 && n[0] == 0) {
        vector<vector<int>> v(a.size(), vector<int>(a.size()));
        for (int i = 0; i < v.size(); ++i) {
            v[i][i] = 1;
        }
        return v;
    };
    if (n[0] % 2 == 1) {
        vector<vector<int>> new_a = a;
        new_a = multiply_copy(new_a, power_mod(new_a, myminus(n, {1})));
        divide(new_a);
        return new_a;
    }
    vector<vector<int>> D = power_mod(a, mydivide(n, 2));
    vector<vector<int>> tmp = D, tmp2(a.size(), vector<int>(a.size()));
    //multiply(D, tmp, tmp2);
    D = multiply_copy(D, D);
    divide(D);
    return D;
}

int main() {
    vector<int> a;
    int n;
    string m_str;
    ifstream fin("input.txt");
    fin >> m_str >> n;
    fin.close();
    //int m = stoi(m_str);

    for (int i = (int) m_str.length(); i > 0; i -= 9)
        if (i < 9)
            a.push_back(atoi(m_str.substr(0, i).c_str()));
        else
            a.push_back(atoi(m_str.substr(i - 9, 9).c_str()));

    vector<int> v_i(n), v_j(n);
    vector<vector<int>> A(1 << n, vector<int>(1 << n));
    for (int i = 0; i < 1 << n; ++i) {
        to_binary(v_i, n, i);
        for (int j = 0; j < 1 << n; ++j) {
            to_binary(v_j, n, j);
            if (isGood(v_i, v_j)) {
                A[i][j] = 1;
            } else A[i][j] = 0;
        }
    }
    A = power_mod(A, myminus(a, {1}));
    ofstream fout("output.txt");
    fout << getAmount(A) % 10000 << endl;
    return 0;
}

