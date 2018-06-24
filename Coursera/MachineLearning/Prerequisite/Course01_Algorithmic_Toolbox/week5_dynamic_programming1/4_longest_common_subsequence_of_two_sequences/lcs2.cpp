#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

#define MIN2(a,b)   (a<b?a:b)
#define MIN3(a,b,c) (MIN2(MIN2(a,b),c))

const int yMinus=0;
const int xMinus=1;
const int xyMinus=2;
struct step {
    int dist;
    int oper;
};

int lcs2(vector<int> &aaa, vector<int> &bbb) {
    //write your code here
    
    vector< vector<step> > editDistance(aaa.size()+1);
    for (int i=0;i<editDistance.size();i++) {
        editDistance[i] = vector<step>(bbb.size()+1);
    }
    
    for (int y=0;y<=aaa.size();y++) {
        editDistance[y][0].dist = y;
    }
    
    for (int x=0;x<=bbb.size();x++) {
        editDistance[0][x].dist = x;
    }
    
    for (int y=1;y<=aaa.size();y++) {
        for (int x=1;x<=bbb.size();x++) {
            step s = editDistance[y-1][x-1];
            if (aaa[y-1]==bbb[x-1]) s.dist -= 1;
            else s.dist += 1;
            s.oper = xyMinus;
            if (editDistance[y][x-1].dist < s.dist) {
                s.dist = editDistance[y][x-1].dist;
                s.oper = xMinus;
            }
            if (editDistance[y-1][x].dist < s.dist) {
                s.dist = editDistance[y-1][x].dist;
                s.oper = yMinus;
            }
            s.dist += 1;
            editDistance[y][x] = s;
        }
    }
    /*
    for (int y=0;y<=aaa.size();y++) {
        for (int x=0;x<=bbb.size();x++) {
            std::cout << editDistance[y][x].dist << " ";
        }
        std::cout << "\n";
    }
    for (int x=0;x<=bbb.size();x++) {
        std::cout << "**";
    }
    std::cout << "\n";
    
    for (int y=0;y<=aaa.size();y++) {
        for (int x=0;x<=bbb.size();x++) {
            std::cout << editDistance[y][x].oper << " ";
        }
        std::cout << "\n";
    }
    */
    int lcs = 0;
    int x = bbb.size();
    int y = aaa.size();
    while (x>0 && y>0) {
        //std::cout << "x:" << x << " y:" << y << " equals:" << (aaa[y-1]==bbb[x-1]?1:0) << " oper:" << editDistance[y][x].oper << "\n";
        if (aaa[y-1]==bbb[x-1]) lcs++;
        if (editDistance[y][x].oper==xMinus) x--;
        else if (editDistance[y][x].oper==yMinus) y--;
        else if (editDistance[y][x].oper==xyMinus) {x--;y--;}
    }
    
    return lcs;
    //return editDistance[aaa.size()][bbb.size()].dist;
}

bool compareArray(vector<int> &aaa, vector<int> &bbb) {
    if (aaa.size()!=bbb.size()) return false;
    for (int i=0;i<aaa.size();i++) {
        if (aaa[i]!=bbb[i]) return false;
    }
    return true;
}

vector<int> getSubArray(int subArray, vector<int> &array) {
    vector<int> result;
    int index = array.size()-1;
    while (subArray>0) {
        if (subArray%2 == 1)  {
            result.push_back(array[index]);
        }
        subArray = subArray / 2;
        index--;
    }
    return result;
}

int lcs2_naive(vector<int> &aaa, vector<int> &bbb) {
    
    //std::sort(aaa.begin(), aaa.end());
    //std::sort(bbb.begin(), bbb.end());
    int probA = pow(2,aaa.size());
    int probB = pow(2,bbb.size());
    
    int max_lcs = 0;
    for (int i=0;i<probA;i++) {
        for (int j=0;j<probB;j++) {
            vector<int> aaaSubArray = getSubArray(i,aaa);
            vector<int> bbbSubArray = getSubArray(j,bbb);
            if (compareArray(aaaSubArray, bbbSubArray)) {
                if (aaaSubArray.size()>max_lcs) {
                    max_lcs = aaaSubArray.size();
                }
            }
        }
    }
    
    return max_lcs;
}



bool compare(vector<int> x, vector<int> y) {
    clock_t begin_time, end_time;
    begin_time = clock();
    int fast = lcs2(x,y);
    end_time = clock();
    std::cout << "fast: " << fast << " in " << (end_time-begin_time)/1000 << "ms\n";
    begin_time = clock();
    int naive = lcs2_naive(x,y);
    end_time = clock();
    std::cout << "naive: " << naive << " in " << (end_time-begin_time)/1000 << "ms\n";
    return fast == naive;
}

#define RANDOMSIZE()   2+(rand()%8)//2+(rand()%100)
#define RANDOMITEM()   ((rand()%10)-5)//((rand()%2000000000)-1000000000)
void test_solution() {
    const int TEST_COUNT = 100;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = RANDOMSIZE();
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> x(size);
        vector<int> y(size);
        for (int j=0;j<size;j++) {
            x[j] = RANDOMITEM();
            y[j] = RANDOMITEM();
        }
        if (!compare(x, y)) {
            std::cout << "error!!!\n";
            return;
        }
    }
    std::cout << "Test succeeded !!!\n";
}

int main() {
    
    //test_solution();
    //return 0;
            
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
