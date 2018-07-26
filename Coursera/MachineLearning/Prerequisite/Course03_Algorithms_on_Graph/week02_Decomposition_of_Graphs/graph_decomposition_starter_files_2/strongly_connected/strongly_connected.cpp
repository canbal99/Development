#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int vertex, vector<vector<int> > &adj, vector<int> &visited, vector<int> &pre, vector<int> &post, int &clock) {
    visited[vertex] = true;
    pre[vertex] = ++clock;
    for (int i=0;i<adj[vertex].size();i++) {
        int next = adj[vertex][i];
        if (!visited[next]) {
            explore(next,adj,visited,pre,post,clock);
        }
    }
    post[vertex] = ++clock;
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;
  
  //write your code here
  vector<vector<int> > radj(adj.size(),vector<int>());
  for (int i=0;i<adj.size();i++) {
      for (int j=0;j<adj[i].size();j++) {
          radj[adj[i][j]].push_back(i);
      }
  }
  
  int clock = 0;
  vector<int> visited(radj.size(),false);
  vector<int> pre(radj.size(),0);
  vector<int> post(radj.size(),0);
  for (int i=0;i<radj.size();i++) {
      if (!visited[i]) {
          explore(i,radj,visited,pre,post,clock);
      }
  }
  /*std::for_each(radj.begin(),radj.end(), [](vector<int> &arr){
      std::for_each(arr.begin(),arr.end(), [](int &i){
        std::cout<<i+1<<" ";
      });
      std::cout<<"\n";
  });*/
  
  vector<int> indices(adj.size());
  int index = 0;
  std::for_each(indices.begin(),indices.end(), [&index](int &i){i=index++;});
  //std::for_each(indices.begin(),indices.end(), [&post](int &i){std::cout<<post[i]<<" ";});
  std::sort(indices.begin(),indices.end(), [&post](int &left,int &right) -> bool {return post[left]>post[right];});
  //std::for_each(indices.begin(),indices.end(), [&post](int &i){std::cout<<post[i]<<" ";});
  //std::for_each(indices.begin(),indices.end(), [&post](int &i){std::cout<<i+1<<" ";});
  
  visited.clear();
  visited.resize(adj.size(),false);
  //std::for_each(visited.begin(),visited.end(), [](int &value){std::cout<< (value?"true":"false") <<" ";});
  for (int i=0;i<indices.size();i++) {
      int vertex = indices[i];
      if (!visited[vertex]) {
          explore(vertex,adj,visited,pre,post,clock);
          result++;
      }
  }
  
  return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}
