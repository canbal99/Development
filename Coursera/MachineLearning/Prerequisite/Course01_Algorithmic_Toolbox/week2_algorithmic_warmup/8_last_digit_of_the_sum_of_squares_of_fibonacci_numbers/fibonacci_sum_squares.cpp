#include <iostream>
#include <vector>
using std::vector;

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

int fibonacci_sum_squares_fast(long long n) {
    
    vector<int> arr;
    
    if (n <= 1)
        return n;

    long long previous = 0;arr.push_back(0);
    long long current  = 1;arr.push_back(1);

    std::cout << "start\n";
    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;
        
        arr.push_back((current * current + arr[arr.size()-1])%10);
        if (arr[arr.size()-1]==1 && arr[arr.size()-2]==0) {
            arr.erase(arr.end()-2, arr.end());
            break;
        }
        std::cout << arr[i] << ' ';
    }
    std::cout << "\nend\n";
    return arr[n % arr.size()];
}

int main() {
    long long n = 0;
    std::cin >> n;
    //std::cout << fibonacci_sum_squares_naive(n) << '\n';
    std::cout << fibonacci_sum_squares_fast(n);
}
