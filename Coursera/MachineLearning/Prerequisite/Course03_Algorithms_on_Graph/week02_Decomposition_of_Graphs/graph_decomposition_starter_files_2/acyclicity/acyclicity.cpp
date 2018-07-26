#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool removeSink(int vertex, vector<vector<int> > &adj, vector<bool> &visited) {
    if (visited[vertex] && adj[vertex].size()>0)
        return false;
    visited[vertex] = true;
    while (adj[vertex].size()>0) {
        int next = adj[vertex].back();
        if (!removeSink(next, adj, visited))
            return false;
        adj[vertex].pop_back();
    }
    return true;
}

int acyclic(vector<vector<int> > &adj) {
    //write your code here
    vector<bool> visited(adj.size(),false);
    for (int i=0; i<adj.size();i++) {
        if (adj[i].size()>0) {
            if (!removeSink(i, adj, visited)) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
