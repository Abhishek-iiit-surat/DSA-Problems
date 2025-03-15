class Solution {
    public:
      // Function to find the shortest distance of all the vertices
      // from the source vertex src.
      vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src) {
          // Code here
          // datastructures used
          // 1. priority queue using min heap for storing nodes with efficient cost
          // 2 result array to store result
          
          // APPROACH1
          // 1. pop a node from queue .
          // 2. from node to neighbour calculate the distance
          // 3. if this distance is less than already present in array update the result array
          // 4. push the neighbour node in queue
          // 5. contine till q is empty
          
          // what does approach tells
          // this approach start traversing nodes with minimum cost
          // in this way we will cover every node and the least possible cost
          // a node can be accessed by 2 routes. 1 is shortest 2 is longest
          // approach will traverse by both and compare which is best will be saved
          // ---------------------------------------------------------------------------
          int V=adj.size();
          priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
          q.push({0,src});
          vector<int> res(V,INT_MAX);
          res[src] = 0;
          while(!q.empty()){
              pair<int, int> topElement = q.top();  
              int cost = topElement.first;
              int node = topElement.second;
              q.pop();
              for(auto it:adj[node]){
                  int ng_node=it.first;
                  int ng_cost=it.second;
                  if(cost+ng_cost<res[ng_node]){
                      q.push({cost+ng_cost,ng_node});
                      res[ng_node]=cost+ng_cost;
                  }
              }
          }
          return res;
          // -----------------------------------------------------------------------------
          
          // APPROACH 2 USING SETS
          // using this we can reduce some redundancy lets say (6,0) was there in a set and 
          // we came accross to reach 0, we can have 4 cost which is less than 6
          // earlier in priority queue 6,0 will come and traverse neighbour but here we can rem
          // ove it directly so as to decrease redundant checks with 6,0 instead 4,0 will be used
          int V=adj.size();
          vector<int> res(V,INT_MAX);
          res[src] = 0;
          set<pair<int,int>> st;
          st.insert({0,src});
          while(!st.empty()){
              auto &it=*st.begin();
              int node=it.second;
              int cost=it.first;
              st.erase(it);
              for(auto it:adj[node]){
                  int ng_node=it.first;
                  int ng_cost=it.second;
                  if(cost+ng_cost<res[ng_node]){
                      if(res[ng_node]!=INT_MAX){
                          st.erase({res[ng_node],ng_node});
                      }
                      res[ng_node] = cost + ng_cost;
                      st.insert({cost+ng_cost,ng_node});
                  }
              }
          }
          return res;
          
      }
  };