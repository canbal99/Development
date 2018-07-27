#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
    //write your code here
    queue<int>  discovered;
    vector<int> distance(adj.size(),-1);
    distance[s] = 0;
    discovered.push(s);

    while(discovered.size()>0) {
        int process = discovered.front();discovered.pop();
        for (int i=0;i<adj[process].size();i++) {
            int discover = adj[process][i];
            if (distance[discover]<0) {
                distance[discover] = distance[process] + 1;
                discovered.push(discover);
            }
        }
    }
    
    return distance[t];
}

int main() {
  int n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
