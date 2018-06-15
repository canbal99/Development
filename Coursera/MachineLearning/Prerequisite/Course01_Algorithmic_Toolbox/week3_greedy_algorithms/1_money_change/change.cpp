#include <iostream>
#include <vector>

using std::vector;
using std::cout;

int get_change(int money, int change, vector<int> changes) {
    if (changes.size()<=change) return 0;
    return money / changes[change] + get_change(money % changes[change], change+1, changes);
}

int get_change(int m) {
    //write your code here
    vector<int> changes = {10,5,1};
    return get_change(m, 0 , changes);
}

int get_change_old(int m) {
    //write your code here
    return m/10 + (m%10)/5 + m%5;
}

bool compare(int m) {
    int oldResult = get_change_old(m);
    int newResult = get_change(m);
    return oldResult == newResult;
}

void test_solution() {
    for (int i=0;i<100000;i++) {
        int money = rand();
        if (!compare(money)) {
            cout << "Failed for: " << money;
            return;
        }
    }
    cout << "Test successful";
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
  //test_solution();
}
