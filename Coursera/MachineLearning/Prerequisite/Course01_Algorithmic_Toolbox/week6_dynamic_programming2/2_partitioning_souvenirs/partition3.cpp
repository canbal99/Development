#include <iostream>
#include <vector>

using std::vector;

int partition3(vector<int> &A, int start, int sum, int totalSum, int& OKAY) {
    /*std::cout << "sum(" << totalSum << "):"<< sum << " A: ";
    for (int i=start;i<A.size();i++) {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";*/
    
    if (sum==0) return 1;
    
    int result = 0;
    for (int i=start;i<A.size();i++) {
        if (A[i]==0) continue;
        if (A[i]<=sum) {
            int temp = A[i];
            A[i] = 0;
            result = partition3(A, i+1, sum - temp, totalSum, OKAY);
            if (OKAY) return OKAY;
            if (result) {
                if (totalSum==0) {
                    //std::cout << "second okay\n";
                    return result;
                } else {
                    //std::cout << "first okay\n";
                    result = partition3(A, 0, totalSum, 0, OKAY);
                    if (result) {
                        OKAY = 1;
                        //std::cout << "all okay\n";
                        return result;
                    }
                }
            }
            A[i] = temp;
        }
    }
    
    return 0;
}

int partition3(vector<int> &A) {
  //write your code here
    int sum = 0;
    for (int i=0;i<A.size();i++) {
        sum += A[i];
    }
    if (sum%3!=0) return 0;
    int OKAY = 0;
    return partition3(A, 0 , sum/3, sum/3, OKAY);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
