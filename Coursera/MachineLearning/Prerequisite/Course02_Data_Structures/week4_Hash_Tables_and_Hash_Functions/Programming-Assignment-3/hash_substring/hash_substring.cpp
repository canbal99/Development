#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

static const size_t bucket_count = 1000000000;
static const size_t multiplier = 263;
static const size_t prime = 1000000007;
size_t hash_func(const string& s) {
    unsigned long long hash = 0;
    for (int i = 0; i < static_cast<int> (s.size()); ++i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}

std::vector<size_t> get_all_hashes(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<size_t> all_hashes;
    all_hashes.push_back(hash_func(t.substr(0, s.size())));
    long long constant = 1;
    for (int i=0;i<s.size();i++) {
        constant = (constant * multiplier) % prime;
    }
    for (size_t i = 1; i + s.size() <= t.size(); ++i) {
        long long new_hash = multiplier * all_hashes[i-1];
        new_hash += t[i-1  + s.size()];
        new_hash -= (t[i-1] * constant) % prime;
        new_hash %= prime;
        all_hashes.push_back(new_hash);
    }
    return all_hashes;
}

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    std::vector<size_t> all_hashes = get_all_hashes(input);
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    size_t pattern_hash = hash_func(s);
    for (size_t i = 0; i + s.size() <= t.size(); ++i) {
        //std::cout << i << " allhash:" << all_hashes[i] << " hash:" << hash_func(t.substr(i, s.size())) << "\n";
        if (all_hashes[i]==pattern_hash) {
           if (t.substr(i, s.size()) == s)
                ans.push_back(i);
        }
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
