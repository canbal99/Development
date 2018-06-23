#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::pair;
using std::abs;
using std::min;
using std::max;
using std::cout;

//#define min(a,b) (a<b ? a:b)
//#define max(a,b) (a>b ? a:b)

#define RANDOM()   ((rand()%2000000000)-1000000000)  
//#define RANDOM()   ((rand()%20)-10)  

struct Point {
    int x;
    int y;
    Point() {x=0;y=0;}
    Point(int x, int y) { this->x=x; this->y=y; };
};

bool xSort (Point i,Point j) { return (i.x<j.x); }
bool ySort (Point i,Point j) { return (i.y<j.y); }

double distance(Point point1, Point point2) {
    return sqrt(powl(point1.x-point2.x, 2.0) + powl(point1.y-point2.y, 2.0));
}

double minimal_distance(vector<Point> &points, int start, int end, vector<Point> &ySorted, vector<Point> &middle) {
    
    if (end-start < 1) return MAXFLOAT;
    if (end-start == 1) return distance(points[start],points[end]);
    
    int avg = start + (end-start)/2;
    double left = minimal_distance(points,start,avg,ySorted,middle);
    double right = minimal_distance(points,avg+1,end,ySorted,middle);
    
    double d = min(left,right);
    double xCenter = (points[avg].x + points[avg+1].x) / 2.0;
    double dist = 0.0;
    
    /*
    middle.clear();
    for (int i=0;i<ySorted.size();i++) {
        if (abs(ySorted[i].x-xCenter)<d) {
            middle.push_back(ySorted[i]);
        }
    }
    */
    middle.clear();
    for (int i=start;i<=end;i++) {
        if (abs(points[i].x-xCenter)<d) {
            middle.push_back(points[i]);
        }
    }
    std::sort(middle.begin(),middle.end(),ySort);
    
    for (int i=0;i<middle.size();i++) {
        for (int j=max(0,i-3);j<i;j++) {
            dist = distance(middle[i],middle[j]);
            if (dist<d) d = dist;
        }
        int minmin = min<int>(i+3,middle.size()-1);
        for (int j=minmin; j>i; j--) {
            dist = distance(middle[i],middle[j]);
            if (dist<d) d = dist;
        }
    }
    
    return d;
}

double minimal_distance(vector<int> x, vector<int> y) {
    
    vector<Point> xSorted(x.size());
    vector<Point> ySorted(x.size());
    vector<Point> middle(x.size());
    
    for (int i=0;i<x.size();i++) {
        xSorted[i].x = x[i];
        xSorted[i].y = y[i];
        ySorted[i].x = x[i];
        ySorted[i].y = y[i];
    }
    
    std::sort(xSorted.begin(),xSorted.end(),xSort);
    std::sort(ySorted.begin(),ySorted.end(),ySort);
    
    return minimal_distance(xSorted, 0, xSorted.size()-1, ySorted, middle);
}

double minimal_distance_naive(vector<int> x, vector<int> y) {
    
    double d = MAXFLOAT;
    for (int i=0;i<x.size();i++) {
        for (int j=0;j<x.size();j++) {
            if (i==j) continue;
            double dist = distance(Point(x[i],y[i]), Point(x[j],y[j]));
            if (dist < d) {
                d = dist;
            }
        }
    }
    return d;
}

bool compare(vector<int> x, vector<int> y) {
    clock_t begin_time, end_time;
    begin_time = clock();
    int fast = minimal_distance(x,y);
    end_time = clock();
    std::cout << "fast: " << fast << " in " << (end_time-begin_time)/1000 << "ms\n";
    begin_time = clock();
    int naive = minimal_distance_naive(x,y);
    end_time = clock();
    std::cout << "naive: " << naive << " in " << (end_time-begin_time)/1000 << "ms\n";
    return fast == naive;
}

void test_solution() {
    const int TEST_COUNT = 10000;
    std::cout << "Test started !!!\n";
    for (int i=0;i<TEST_COUNT;i++) {
        int size = 2+(rand()%1000/*10000*/);
        //int size = pow(10,i);
        std::cout << "Test for " << i << ":" << size << "\n";
        vector<int> x(size);
        vector<int> y(size);
        for (int j=0;j<size;j++) {
            x[j] = RANDOM();
            y[j] = RANDOM();
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
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
