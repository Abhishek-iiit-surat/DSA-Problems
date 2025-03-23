int largestPathValue(string colors, vector<vector<int>>& edges) {
    unordered_map<int, vector<int>> adj; // Adjacency list representation of the graph
    int N = colors.size(); // Number of nodes
    vector<int> indegree(N, 0); // Stores incoming edge count for each node
    
    // Step 1: Build the graph and calculate indegree
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0]; 
        int v = edges[i][1];
        adj[u].push_back(v); // Create directed edge u -> v
        indegree[v]++; // Increment indegree of node v
    }
    
    // Step 2: Create a DP table to track max color count for each node
    vector<vector<int>> t(N, vector<int>(26, 0)); 
    queue<int> que; // Queue for topological sorting
    int count_nodes = 0; // Count of processed nodes
    int ans = 0; // Stores the maximum frequency of any color in a path

    // Step 3: Push all nodes with indegree 0 into the queue
    for (int i = 0; i < N; i++) {
        if (indegree[i] == 0) {
            que.push(i);
            t[i][colors[i] - 'a'] = 1; // Initialize with color of the current node
        }
    }

    // Step 4: Process nodes using Kahn’s algorithm (Topological Sorting)
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        count_nodes++; // Increase processed node count

        // Step 5: Update color frequency for adjacent nodes
        for (auto v : adj[u]) {
            for (int i = 0; i < 26; i++) {
                // Take the max frequency of each color while moving to child nodes
                t[v][i] = max(t[v][i], t[u][i] + (colors[v] - 'a' == i));
            }
            indegree[v]--; // Reduce indegree since one dependency is processed
            
            // If v has no more dependencies, push to queue
            if (indegree[v] == 0) {
                que.push(v);
            }
        }
    }

    // Step 6: Find the maximum value in the DP table
    for (int i = 0; i < t.size(); i++) {
        for (int j = 0; j < t[0].size(); j++) {
            ans = max(ans, t[i][j]); // Get the maximum color frequency
            cout << t[i][j] << " "; // Debug output
        }
        cout << endl;
    }

    // Step 7: Check for cycles
    if (count_nodes != N) {
        return -1; // Cycle detected, return -1
    }

    return ans; // Return the largest color frequency found
}
