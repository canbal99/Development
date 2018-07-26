#include <iostream>
#include <vector>
using namespace std;
using std::vector;

int sum_of_two_digits(int first_digit, int second_digit) {
    return first_digit + second_digit;
}

int main_() {
    int a = 0;
    int b = 0;
    cin >> a;
    std::cin >> b;
    std::cout << sum_of_two_digits(a, b) << endl;
    return 0;
}