#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

static int MAX_HOPS = 5;
static int _INFINITY_ = std::numeric_limits<int>::max() / 2;
#define     F       0
#define     R       1
#define     FR      (forward?0:1)
#define     RF      (forward?1:0)

class Graph
{
    typedef int Distance;
    typedef int Vertex;

    // Number of nodes
    int N;
    // Source and target
    int s, t;
    // Estimate of the distance from s to t
    int estimate = _INFINITY_;
    // Lists of edges outgoing from each node
    std::vector<std::vector<std::pair<int, int>>> outgoing_edges;
    // Lists of edges incoming to each node
    std::vector<std::vector<std::pair<int, int>>> incoming_edges;

    //static constexpr int _INFINITY_ = std::numeric_limits<int>::max() / 2;
    // Levels of nodes for node ordering
    std::vector<int> level;
    // Ranks of nodes - positions in the node ordering
    std::vector<int> rank;

    // Distance to node v, bidistance[0][v] - from source in the forward search, bidistance[1][v] - from target
    // in the backward search.
    std::vector<std::vector<Distance>> bidistance;
    
    std::vector<int> hopCount;

    // Wrapper around STL priority_queue
    class StlHeap
    {
    public:
        using T = std::pair<Distance, Vertex>;
        using Queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

        StlHeap() {
            queue.reset(new Queue());
        }

        bool empty() const {
            return queue->empty();
        }

        void update(Vertex v, Distance d) {
            queue->push(std::make_pair(d,v));
        }

        void clear() {
            queue.reset(new Queue());
        }

        std::pair<Distance, Vertex> top() {
            return queue->top();
        }

        std::pair<Distance, Vertex> pop() {
            pair<Distance, Vertex> top = queue->top();
            queue->pop();
            return top;
        }

    private:
        std::unique_ptr<Queue> queue;
    };

    // Priority queues for forward and backward searches
    StlHeap diqueue[2];
public:
    Graph() {
        read_stdin();
        bidistance.resize(2, std::vector<int>(N, _INFINITY_));  
        processed.resize(2,vector<bool>(N,false));
        updated.reserve(N);
        hopCount.resize(N);
    }

    int get_n() { return N;}

    std::vector<std::pair<int, int>>& get_adjacent(int v, bool forward = true) {
        if (forward) {
            return outgoing_edges[v];
        } else {
            return incoming_edges[v];
        }
    }

    void preprocess() {
        //distance.resize(N, INFINITY_);
        // Priority queue will store pairs of (importance, node) with the least important node in the head
        
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int, int>>> queue;
        
        // init queue here
        int level, importance;
        vector<Shortcut> shortcuts;
        while (true) {
            int v = queue.top().second; queue.pop();
            
            auto incoming = get_adjacent(v, false);
            for (int i=0; i< incoming.size(); i++) {
                int incVertex = incoming[i].first;
                int incCost = incoming[i].second;
                
                auto outgoing = get_adjacent(v, true);
                for (int j=0; j<outgoing.size(); j++) {
                    int outVertex = outgoing[j].first;
                    int outCost = outgoing[j].second;
                    
                    int minCost = queryForShorterPath(incVertex, outVertex, MAX_HOPS, incCost+outCost);
                    if (minCost>=0 || min<incCost+outCost) {
                        shortcuts.push_back(Shortcut(incVertex,outVertex,minCost));
                    }
                }
            }
            
            importance = do_shortcut(v, shortcuts, level);
            queue.push(make_pair(importance,v));
            shortcuts.clear();
        }

        // Implement the rest of the algorithm yourself
    }

    // Returns distance from s to t in the graph
    int query(int u, int w) {
        clear();
        update(u, 0, true);
        update(w, 0, false);
        s = u; 
        t = w;
        // Implement the rest of the algorithm yourself
        
        int res;
        while (!diqueue[F].empty() || !diqueue[R].empty()) {
            if ((res = processQueue(true))!=-1 || (res = processQueue(false))!=-1)
                return res;
        }

        return -1;
    }

private:
    
    int queryForShorterPath(int u, int w, int maxHops, int maxCost) {
        clear();
        update(u, 0, true);
        update(w 0, false);
        
        int res, hopCnt;
        hopCount[u] = 0;
        while(!diqueue[F].empty()) {
            auto top = diqueue[F].top();
            if (top.first>maxCost) break;
            if (hopCount[top.second]>maxHops) { diqueue[F].pop(); continue; }
            
            int visitedCount = updated.size();
            if (res = processQueue(true)!=-1) {
                return res;
            }
            for (int i=visitedCount; i<updated.size(); i++) {
                hopCount[i] = hopCount[hopCnt] + 1;
            }
        }
        return -1;
    }
    
    int processQueue(bool forward) {
        while (!diqueue[FR].empty()) {
            int fr = diqueue[FR].pop().second;
            if (!processed[FR][fr]) {
                process(fr, bidistance[FR][fr], forward);
                if (processed[RF][fr]) {
                    return returnShortest();
                }
                break;
            }
        }
        return -1;
    }
    
    void process(int v, int d, bool forward) {
        //cout << "Processing(" << (forward?"F":"R") << "):" << v+1 << "(dist:" << d << ") => Checking:";
        processed[FR][v] = true;
        std::vector<std::pair<int, int>>& edges = get_adjacent(v, forward);
        for (int i = 0; i < edges.size(); ++i) {
            auto& edge = edges[i];
            //cout << " " << edge.first+1 << "(dist:" << (bidistance[FR][edge.first]==_INFINITY_?"INF":to_string(bidistance[FR][edge.first])) << "-cost:" << edge.second << ")";
            if (bidistance[FR][edge.first] > d + edge.second) {
                update(edge.first, d + edge.second, v, forward);
            }
        }
        //cout << "\n";
    }
    
    // Try to relax the node v using distance d either in the forward or in the backward search
    void update(int v, int d, bool forward) {
        // Implement this method yourself
        diqueue[FR].update(v,d);
        bidistance[FR][v] = d;
        updated.push_back(v);
        //cout << "(updated:" << d << ")";
    }
    
    int returnShortest() {
        int minimum = _INFINITY_;
        int candidate;
        for (int v : updated) {
            candidate = bidistance[F][v] + bidistance[R][v];
            if (minimum > candidate) minimum = candidate;
        }
        return minimum;
    }
    
    void clear() {
        for (int v : updated) {
            bidistance[F][v] = bidistance[R][v] = _INFINITY_;
            processed[F][v] = processed[R][v] = false;
        }
        diqueue[F].clear();
        diqueue[R].clear();
        updated.clear();
    }
    vector<int> updated;
    vector<vector<bool>> processed;

    // QEntry = (distance, vertex)
    typedef std::pair<int,int> QEntry;
    std::priority_queue<QEntry, std::vector<QEntry>, std::greater<QEntry>> queue;

    struct Shortcut {
        int from;
        int to;
        int cost;
    };

    // Adds all the shortcuts for the case when node v is contracted, and returns the importance of node v
    // in this case
    int do_shortcut(int v, std::vector<Shortcut>& shortcuts, int& mylevel) {
        // Implement this method yourself

        // Add neighbors and shortcut cover heuristics
        return (shortcuts.size() - outgoing_edges[v].size() - incoming_edges[v].size()) + mylevel;
    }

    void set_n(int n) {
        N = n;
        outgoing_edges.resize(n);
        incoming_edges.resize(n);
    }


    void add_edge_to_list(std::vector<std::pair<int,int>>& list, int w, int c) {
        for (int i = 0; i < list.size(); ++i) {
            std::pair<int, int>& p = list[i];
            if (p.first == w) {
                if (p.second > c) {
                    p.second = c;
                }
                return;
            }
        }
        list.push_back(make_pair(w, c));
    }

    void add_directed_edge(int u, int v, int c) {
        add_edge_to_list(outgoing_edges[u], v, c);
        add_edge_to_list(incoming_edges[v], u, c);
    }

    void add_edge(int u, int v, int c) {
        add_directed_edge(u, v, c);
    }

    void finalize() {
        // Remove unnecessary edges
    }

    bool read_stdin() {
        int u,v,c,n,m;
        assert(scanf("%d %d", &n, &m) == 2);
        set_n(n);
        for (int i = 0; i < m; ++i) {
            assert(scanf("%d %d %d", &u, &v, &c) == 3);
            add_edge(u-1, v-1, c);
        }
        finalize();
        return true;
    }
};

int main() {
    Graph g;
    g.preprocess();
    std::cout << "Ready" << std::endl;

    int t;
    assert(scanf("%d", &t) == 1);
    for (int i = 0; i < t; ++i) {
        int u, v;
        assert(scanf("%d %d", &u, &v) == 2);
        printf("%d\n", g.query(u-1, v-1));
    }
}
