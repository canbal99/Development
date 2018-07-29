#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <iostream>
#include <unordered_set>

using namespace std;
using std::cout;

const int F = 0;
const int R = 1;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>, vector<pair<Len, int>>, greater<pair<Len, int>>>> Queue;

const Len INFINITY_ = numeric_limits<Len>::max() / 4;

class Bidijkstra {
    // Number of nodes
    int n_;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len>> distance_;
    // Stores all the nodes visited either by forward or backward search.
    unordered_set<int> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    //vector<bool> visited_;
    vector<unordered_set<int>> processedset_;

public:

    Bidijkstra(int n, Adj adj, Adj cost)
    : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY_)), processedset_(2,unordered_set<int>(n)) {
    }

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.

    void clear() {
        for (int v : workset_) {
            distance_[0][v] = distance_[1][v] = INFINITY_;
        }
        workset_.clear();
        processedset_[F].clear();
        processedset_[R].clear();
    }

    // Processes visit of either forward or backward search 
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.

    void visit(Queue& q, int side, int v, Len dist) {
        // Implement this method yourself
        workset_.insert(v);
        distance_[side][v] = dist;
        q[side].push(make_pair(dist, v));
        //cout << "(visited:" << distance_[side][v] << ")";
    }
    
    void process(Queue& q, int side, int v) {
        // Implement this method yourself
        int adj,newDist;
        processedset_[side].insert(v);
        Len dist = distance_[side][v];
        //cout << "\nProcessing(" << (side?"R":"F") << "):" << v+1 << "(dist:" << dist << ") => Checking:";
        for (int i=adj_[side][v].size()-1; i>=0; i--) {
            adj = adj_[side][v][i];
            newDist = dist + cost_[side][v][i];
            //cout << " " << adj+1 << "(dist:" << (distance_[side][adj]==INFINITY_?"INF":to_string(distance_[side][adj])) << "-cost:" << cost << ")";
            if (distance_[side][adj] > newDist) {
                visit(q, side, adj, newDist);
            }
        }
        //cout<<"\n";
    }
    
    Len returnShortest() {
        Len minimum = INFINITY_;
        Len candidate;
        for (int v : processedset_[F]) {
            candidate = distance_[F][v] + distance_[R][v];
            if (minimum > candidate) minimum = candidate;
        }
        for (int v : processedset_[R]) {
            candidate = distance_[F][v] + distance_[R][v];
            if (minimum > candidate) minimum = candidate;
        }
        return minimum;
    }

    // Returns the distance from s to t in the graph.

    Len query(int s, int t) {
        
        if (s==t) return 0;
        
        clear();
        Queue q(2);
        visit(q, 0, s, 0);
        visit(q, 1, t, 0);
        // Implement the rest of the algorithm yourself

        int f,r;
        while (!q[F].empty() || !q[R].empty()) {
            
            if (!q[F].empty()) {
                f = q[F].top().second;q[F].pop();
                if (processedset_[F].count(f)==0)
                {
                    process(q, F, f);
                    if (processedset_[R].count(f)==1) {
                        return returnShortest();
                    }
                }
            }
            
            if (!q[R].empty()) {
                r = q[R].top().second;q[R].pop();
                if (processedset_[R].count(r)==0)
                {
                    process(q, R, r);
                    if (processedset_[F].count(r)==1) {
                        return returnShortest();
                    }
                }
            }
        }

        return -1;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Adj adj(2, vector<vector<int>>(n));
    Adj cost(2, vector<vector<int>>(n));
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u - 1].push_back(v - 1);
        cost[0][u - 1].push_back(c);
        adj[1][v - 1].push_back(u - 1);
        cost[1][v - 1].push_back(c);
    }

    Bidijkstra bidij(n, adj, cost);

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", bidij.query(u - 1, v - 1));
    }
}
