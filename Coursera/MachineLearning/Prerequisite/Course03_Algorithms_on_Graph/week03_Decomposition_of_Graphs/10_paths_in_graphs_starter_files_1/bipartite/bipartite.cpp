#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
    //write your code here
    bool bipartite = true;
    
    queue<int>  discovered;
    vector<int> distance(adj.size(),-1);
    
    for (int vertexIndex=0; vertexIndex<adj.size(); vertexIndex++)
    {
        if (distance[vertexIndex]>=0) continue;
        
        distance[vertexIndex] = 0;
        discovered.push(vertexIndex);

        while(discovered.size()>0) {
            int process = discovered.front();discovered.pop();
            for (int adjVertexIndex=0; adjVertexIndex<adj[process].size(); adjVertexIndex++) {
                int discover = adj[process][adjVertexIndex];
                if (distance[discover]<0) {
                    distance[discover] = distance[process] + 1;
                    discovered.push(discover);
                } else {
                    bipartite = (abs(distance[process] - distance[discover]) % 2)==1;
                    if (!bipartite) return false;
                }
            }
        }
    }
    
    return true;
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
  std::cout << bipartite(adj);
}
