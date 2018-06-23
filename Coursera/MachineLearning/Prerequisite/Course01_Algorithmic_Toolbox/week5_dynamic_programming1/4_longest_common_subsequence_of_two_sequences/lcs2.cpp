#include <iostream>
#include <vector>

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
    }*/
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

int main() {
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
