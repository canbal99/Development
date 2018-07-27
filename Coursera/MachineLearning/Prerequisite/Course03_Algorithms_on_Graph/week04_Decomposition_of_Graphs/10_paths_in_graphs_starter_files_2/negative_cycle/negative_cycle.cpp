#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    //write your code here
    vector<int> distance(adj.size(),0);
    int next,c;
    bool found = true;
    
    int count = adj.size();
    while (count > 0 && found) {
        found = false;
        for (int i = 0; i < adj.size(); i++) {
            for (int j = 0; j < adj[i].size(); j++) {
                next = adj[i][j];
                c = cost[i][j];
                if (distance[next] > distance[i] + c) {
                    distance[next] = distance[i] + c;
                    found = true;
                }
            }
        }
        count--;
    }
    
    //std::for_each(distance.begin(),distance.end(),[](int& elem){std::cout<<elem<<" ";});
    //std::cout<<"\n";
    return found;
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
    std::cout << negative_cycle(adj, cost);
}
