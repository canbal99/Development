#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%m;
    }

    return current % m;
}

long long get_fibonacci_huge_fast(long long n, long long m) {
    
    vector<int> arr;
    
    if (n <= 1)
        return n;

    long long previous = 0;arr.push_back(0);
    long long current  = 1;arr.push_back(1);

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%m;
        
        arr.push_back(current);
        if (arr[arr.size()-1]==1 && arr[arr.size()-2]==0) {
            arr.erase(arr.end()-2, arr.end());
            break;
        }
    }

    return arr[n % arr.size()];
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    //std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
