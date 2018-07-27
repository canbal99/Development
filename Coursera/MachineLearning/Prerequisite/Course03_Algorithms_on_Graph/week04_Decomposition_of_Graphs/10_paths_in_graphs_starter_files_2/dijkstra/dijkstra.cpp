#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::cout;
using std::endl;

class Comparison {
    vector<int> &distance;
public:
    Comparison(vector<int> &distance) : distance(distance) {}
    bool operator()(const int& lhsIndex, const int& rhsIndex) const {
        return distance[lhsIndex] > distance[rhsIndex];
    }
};


int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
    //write your code her
    vector<int> distance(adj.size(),0x7FFFFFFF);
    vector<int> prev(adj.size(),-1);
    vector<bool> dequeued(adj.size(),false);
    auto compare = [&distance](const int& lhs, const int& rhs) { return distance[lhs]>distance[rhs]; };
    priority_queue< int, vector<int>, decltype( compare ) > minDistQueue(compare);
    //Comparison compare(distance);
    //priority_queue< int, vector<int>, Comparison > minDistQueue(compare);
    
    distance[s] = 0;
    minDistQueue.push(s);
    while (!minDistQueue.empty()) {
        int minDist = minDistQueue.top();minDistQueue.pop();
        if (dequeued[minDist]) continue;dequeued[minDist] = true;
        //cout << "minDist:" << minDist+1 << " -> ";
        //std::for_each(adj[minDist].begin(),adj[minDist].end(),[](int& elem){cout << elem+1 << " ";});
        //cout << endl;
        for (int i=0;i<adj[minDist].size();i++) {
            int next = adj[minDist][i];
            //cout << "Starting:" << next+1 << " dist:" << distance[next] << " cost:" << cost[minDist][i] << endl;
            if (distance[next] > distance[minDist] + cost[minDist][i]) {
                distance[next] = distance[minDist] + cost[minDist][i];
                prev[next] = minDist;
                minDistQueue.push(next);
            }
        }
        //std::for_each(distance.begin(),distance.end(),[](int& elem){cout << elem << " ";});
        //cout << endl;
    }
    
    return distance[t]==0x7FFFFFFF ? -1 : distance[t];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
