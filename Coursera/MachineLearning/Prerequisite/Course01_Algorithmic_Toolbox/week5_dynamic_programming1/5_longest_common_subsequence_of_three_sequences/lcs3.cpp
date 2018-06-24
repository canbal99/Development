#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

#define MIN2(a,b)   (a<b?a:b)
#define MIN3(a,b,c) (MIN2(MIN2(a,b),c))

const int xMinus=0;
const int yMinus=1;
const int zMinus=2;
const int xyMinus=3;
const int yzMinus=4;
const int xzMinus=5;
const int xyzMinus=6;
struct step {
    int dist;
    int oper;
};

int lcs3(vector<int> &aaa, vector<int> &bbb, vector<int> &ccc) {
    //write your code here
    
    vector< vector< vector<step> > > editDistance(aaa.size()+1);
    for (int i=0;i<=aaa.size();i++) {
        editDistance[i] = vector < vector<step> >(bbb.size()+1);
        for (int j=0;j<=bbb.size();j++) {
            editDistance[i][j] = vector<step>(ccc.size()+1);
        }
    }
    
    for (int z=0;z<=aaa.size();z++) {
        for (int y=0;y<=bbb.size();y++) {
            editDistance[z][y][0].dist = y+z;
        }
    }
    
    for (int y=0;y<=bbb.size();y++) {
        for (int x=0;x<=ccc.size();x++) {
            editDistance[0][y][x].dist = y+x;
        }
    }
    
    for (int z=0;z<=aaa.size();z++) {
        for (int x=0;x<=ccc.size();x++) {
            editDistance[z][0][x].dist = x+z;
        }
    }
    
    for (int z=1;z<=aaa.size();z++) {
        for (int y=1;y<=bbb.size();y++) {
            for (int x=1;x<=ccc.size();x++) {
                step s;
                s.dist = editDistance[z-1][y-1][x-1].dist + 3;
                if (aaa[z-1]==bbb[y-1] && aaa[z-1]==ccc[x-1]) s.dist -= 3;
                s.oper = xyzMinus;
                if (editDistance[z][y-1][x-1].dist+2 < s.dist) {
                    s.dist = editDistance[z][y-1][x-1].dist+2;
                    s.oper = xyMinus;
                }
                if (editDistance[z-1][y-1][x].dist+2 < s.dist) {
                    s.dist = editDistance[z-1][y-1][x].dist+2;
                    s.oper = yzMinus;
                }
                if (editDistance[z-1][y][x-1].dist+2 < s.dist) {
                    s.dist = editDistance[z-1][y][x-1].dist+2;
                    s.oper = xzMinus;
                }
                if (editDistance[z][y][x-1].dist+1 < s.dist) {
                    s.dist = editDistance[z][y][x-1].dist+1;
                    s.oper = xMinus;
                }
                if (editDistance[z][y-1][x].dist+1 < s.dist) {
                    s.dist = editDistance[z][y-1][x].dist+1;
                    s.oper = yMinus;
                }
                if (editDistance[z-1][y][x].dist+1 < s.dist) {
                    s.dist = editDistance[z-1][y][x].dist+1;
                    s.oper = zMinus;
                }
                editDistance[z][y][x] = s;
            }
        }
    }
    
    int lcs = 0;
    int x = ccc.size();
    int y = bbb.size();
    int z = aaa.size();
    while (x>0 && y>0 && z>0) {
        bool equals = aaa[z-1]==bbb[y-1]&&aaa[z-1]==ccc[x-1];
        //std::cout << "x:" << x << " y:" << y << " z:" << z << " equals:" << equals << " oper:" << editDistance[z][y][x].oper << "\n";
        if (equals) lcs++;
        switch (editDistance[z][y][x].oper) {
            case xMinus: x--; break;
            case yMinus: y--; break;
            case zMinus: z--; break;
            case xyMinus: x--; y--; break;
            case xzMinus: x--; z--; break;
            case yzMinus: y--; z--; break;
            case xyzMinus: x--; y--; z--; break;
        }
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

int lcs3_naive(vector<int> &aaa, vector<int> &bbb, vector<int> &ccc) {
    
    //std::sort(aaa.begin(), aaa.end());
    //std::sort(bbb.begin(), bbb.end());
    //std::sort(bbb.begin(), ccc.end());
    int probA = pow(2,aaa.size());
    int probB = pow(2,bbb.size());
    int probC = pow(2,ccc.size());
    
    int max_lcs = 0;
    for (int i=0;i<probA;i++) {
        for (int j=0;j<probB;j++) {
            for (int k=0;k<probC;k++) {
                vector<int> aaaSubArray = getSubArray(i,aaa);
                vector<int> bbbSubArray = getSubArray(j,bbb);
                vector<int> cccSubArray = getSubArray(k,ccc);
                if (compareArray(aaaSubArray, bbbSubArray) && compareArray(aaaSubArray, cccSubArray)) {
                    if (aaaSubArray.size()>max_lcs) {
                        max_lcs = aaaSubArray.size();
                    }
                }
            }
        }
    }
    
    return max_lcs;
}



bool compare(vector<int> x, vector<int> y, vector<int> z) {
    clock_t begin_time, end_time;
    begin_time = clock();
    int fast = lcs3(x,y,z);
    end_time = clock();
    std::cout << "fast: " << fast << " in " << (end_time-begin_time)/1000 << "ms\n";
    begin_time = clock();
    int naive = lcs3_naive(x,y,z);
    end_time = clock();
    std::cout << "naive: " << naive << " in " << (end_time-begin_time)/1000 << "ms\n";
    return fast == naive;
}

#define RANDOMSIZE()   2+(rand()%5)//2+(rand()%100)
#define RANDOMITEM()   ((rand()%4)-2)//((rand()%2000000000)-1000000000)
void test_solution() {
    const int TEST_COUNT = 100;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = RANDOMSIZE();
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> x(size);
        vector<int> y(size);
        vector<int> z(size);
        for (int j=0;j<size;j++) {
            x[j] = RANDOMITEM();
            y[j] = RANDOMITEM();
            z[j] = RANDOMITEM();
        }
        if (!compare(x, y, z)) {
            std::cout << "error!!!\n";
            return;
        }
    }
    std::cout << "Test succeeded !!!\n";
}

int main() {
    
    //test_solution();
    //return 0;
    
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
