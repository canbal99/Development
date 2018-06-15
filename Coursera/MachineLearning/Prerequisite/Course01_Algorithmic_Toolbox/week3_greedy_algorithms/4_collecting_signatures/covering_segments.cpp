#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <map>

using std::vector;
using std::map;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  map<int,int> segmentMap;
  
  for (int i=0;i<segments.size();i++) {
      segmentMap.insert(std::pair<int,int>(segments[i].start, segments[i].end));
  }
  
  int min = segmentMap.begin()->first;
  int max = segmentMap.begin()->second;
  int point = max;
  for (auto segment : segmentMap) {
      point = max;
      min = std::max<int>(min,segment.first);
      max = std::min<int>(max,segment.second);
      if (max<min) {
          min = segment.first;
          max = segment.second;
          points.push_back(point);
      }
  }
  points.push_back(max);
  
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
