#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <map>
#include <unordered_map>

/** Problem statement: https://acm.bsu.by/courses/120/problems/2693/ */

using namespace std;

const char alphabet[36] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
     'M',
     'N', 'O', 'P', 'Q', 'R',
     'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

//const char alphabet[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
//                           'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
//                           's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const char numbers[36] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '2', '2', '2', '3', '3', '3', '4', '4', '1', '1', '5', '5',
     '6',
     '6', '0', '7', '0', '7',
     '7', '8', '8', '8', '9', '9', '9', '0'};

string translate(const string &givenWord)
{
    string outputNumber(givenWord.length(), '0');
    for (int i = 0; i < givenWord.length(); ++i) {
        outputNumber[i] = numbers[givenWord[i] - '0' < 10 ? givenWord[i] - '0' : givenWord[i] - 'A' + 10];
    }
    return outputNumber;
}

//long long get_hash(const string &str, const vector<long long> &pows) {
//    long long ans = 0;
//    for (int i = 0; i < str.size(); ++i) {
//        ans += (str[i] - '0' + 1) * pows[i];
//    }
//    return ans;
//}

long long get_hash(const string &str, const vector<long long> &pows)
{
    long long ans = 0;
    for (int i = str.size() - 1; i >= 0; --i) {
        ans += (str[i] - '0' + 1) * pows[str.size() - 1 - i];
    }
    return ans;
}

int main()
{

    ifstream fin("input.txt");
    string number;
    int wordsAmount;
    fin >> number;
    fin >> wordsAmount;
    vector<string> words(wordsAmount);

    long long p_pow = 1;
    vector<long long> pows(100);
    for (int i = 0; i < 100; ++i) {
        pows[i] = p_pow;
        p_pow *= 11;
    }

    unordered_map<long long, int> m;

    string temp;
    for (int i = 0; i < wordsAmount; ++i) {
        fin >> temp;
        words[i] = temp;
        m.insert({get_hash(translate(temp), pows), i});
    }
    fin.close();
    long long hash_tmp;
    int k = 0;
    vector<int> alreadyAmount(number.size(), 1e9);
    vector<int> optimalWord(number.size());
    for (int i = 1; i < number.size() + 1; ++i) {
        hash_tmp = 0;
        k = 0;
        for (int j = i - 1; j >= 0 && i - j <= 100; j--) {
            hash_tmp += (number[j] - '0' + 1) * pows[k];
            ++k;
            if (j == 0 || alreadyAmount[j - 1] + 1 < alreadyAmount[i - 1]) {
                auto ans = m.find(hash_tmp);
                if (ans != m.end()) {
                    int index = ans->second;
                    if (index != -1) {
                        if (j == 0) {
                            alreadyAmount[i - 1] = 1;
                            optimalWord[i - 1] = index;
                        }
                        else {
                            alreadyAmount[i - 1] = alreadyAmount[j - 1] + 1;
                            optimalWord[i - 1] = index;
                        }
                    }
                }
            }
        }
    }
    ofstream fout("output.txt");
    vector<int> indices(number.size());
    if (alreadyAmount.back() == 1e9) {
        fout << "No solution" << endl;
    }
    else {
        int newAmount = alreadyAmount.back();
        int i = number.size() - 1;
        while (newAmount != 0) {
            indices[newAmount - 1] = optimalWord[i];
            i -= words[optimalWord[i]].size();
            --newAmount;
        }
        fout << alreadyAmount.back() << endl;
        for (int i = 0; i < alreadyAmount.back(); ++i) {
            fout << words[indices[i]] << " ";
        }
    }
    return 0;
}

