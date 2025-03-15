vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
    // Code here
    unordered_map<int, vector<pair<int, int>>> adj;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];  
        int v = edges[i][1];  
        int wt = edges[i][2]; 
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt}); 
    }
    // do a dijkstra
    // maintain one parent list
    vector<int> parent(n+1,-1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> min_wt(n+1,INT_MAX);
    vector<int> ans;
    min_wt[1]=0;
    pq.push({0,1});
    while(!pq.empty()){
        pair<int,int> top_element=pq.top();
        int accumulated_cost=top_element.first;
        int node=top_element.second;
        pq.pop();
        for(auto it:adj[node]){
            int go_to_node=it.first;
            int go_to_cost=it.second;
            
            if(accumulated_cost+go_to_cost<min_wt[go_to_node]){
                pq.push({accumulated_cost+go_to_cost,go_to_node});
                parent[go_to_node]=node;
                min_wt[go_to_node]=accumulated_cost+go_to_cost;
            }
        }
    }
    // if(n==1) return {-1};
    int last_node=n;
    int total_cost=min_wt[n];
    if(parent[n]==-1) return {-1};
    ans.push_back(n);
    while(last_node!=1){
        ans.push_back(parent[last_node]);
        last_node=parent[last_node];
    }
    ans.push_back(total_cost);
    reverse(ans.begin(),ans.end());
    return ans;
}