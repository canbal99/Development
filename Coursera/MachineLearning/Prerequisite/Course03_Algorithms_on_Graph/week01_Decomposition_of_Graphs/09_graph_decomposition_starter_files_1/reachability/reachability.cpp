#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector<vector<int> > &adj, vector<int> &labels, vector<bool> &visited, int label, int cell) {
    visited[cell] = true;
    labels[cell] = label;
    for (auto adjCell : adj[cell]) {
        if (!visited[adjCell]) {
            explore(adj, labels, visited, label, adjCell);
        }
    }
}

std::tuple<vector<int>,int> labelize(vector<vector<int> > &adj) {
    
    vector<bool> visited(adj.size(), false);
    vector<int> labels(adj.size(), -1);
    int label = 0;
    for (int cell=0;cell<visited.size(); cell++) {
        if (!visited[cell]) {
            explore(adj, labels, visited, label++, cell);
        }
    }
    return std::tuple<vector<int>,int>(labels,label);
}

int reach(vector<vector<int> > &adj, int x, int y) {
    //write your code here
    vector<int> label = std::get<0>(labelize(adj));
    
    /*for (int i=0;i<label.size();i++) {
        std::cout << i << ":" << label[i] << "  ";
    }
    std::cout << "\n";*/
    
    return label[x]==label[y];
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
