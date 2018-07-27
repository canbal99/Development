#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

const long long INFINITY = std::numeric_limits<long long>::max();

void explore(int vertex, vector<vector<int> > &adj, vector<int> &notVisited, vector<int> &visited) {
    int next;
    notVisited[vertex] = 0;
    visited[vertex] = 1;
    for (int i=0;i<adj[vertex].size();i++) {
        next = adj[vertex][i];
        if (notVisited[next]) {
            explore(next, adj, notVisited, visited);
        }
    }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
    //write your code here
    bool found = true;
    int next, c;
    int count = adj.size() - 1;
    distance[s] = 0;
    
    while (count > 0 && found) {
        found = false;
        for (int i = 0; i < adj.size(); i++) {
            if (distance[i]==INFINITY) continue;
            for (int j = 0; j < adj[i].size(); j++) {
                next = adj[i][j];
                c = cost[i][j];
                if (distance[next] > distance[i] + c) {
                    // DISTANCE
                    distance[next] = distance[i] + c;
                    found = true;
                }
            }
        }
        count--;
    }
            
    vector<int> negativeCycles;
    for (int i = 0; i < adj.size(); i++) {
        if (distance[i]==INFINITY) continue;
        // REACHABILE
        reachable[i] = 1;
        for (int j = 0; j < adj[i].size(); j++) {
            next = adj[i][j];
            c = cost[i][j];
            if (distance[next] > distance[i] + c) {
                distance[next] = distance[i] + c;
                negativeCycles.push_back(next);
            }
        }
    }
    
    while (negativeCycles.size()>0) {
         // REACHABILE & SHORTEST
        explore(negativeCycles.back(), adj, shortest, reachable);
        negativeCycles.pop_back();
    }
}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, INFINITY);
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        } else if (!shortest[i]) {
            std::cout << "-\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }
}
