#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

int fibonacci_sum_fast(long long n) {
    
    vector<int> arr;
    
    if (n <= 1)
        return n;

    long long previous = 0;arr.push_back(0);
    long long current  = 1;arr.push_back(1);

    //std::cout << "start\n";
    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;
        
        arr.push_back((current + arr[arr.size()-1])%10);
        if (arr[arr.size()-1]==1 && arr[arr.size()-2]==0) {
            arr.erase(arr.end()-2, arr.end());
            break;
        }
        //std::cout << arr[i] << ' ';
    }
    //std::cout << "\nend\n";
    return arr[n % arr.size()];
}

long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    
    return (fibonacci_sum_fast(to) - fibonacci_sum_fast(from-1) + 10) % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    //std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
