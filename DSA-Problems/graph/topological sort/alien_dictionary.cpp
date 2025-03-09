// intution
// something is prerequisite of something and we have to return order (core idea of topological sort)

// Problem
// 1. order is asked for charachters not for numbers
// 2.adj list is directly not given

// Approach
// 1. first make adj list unordered_map<int,vector<int>> (we converted in int because accessing indexes with int is easy)
// 2.in adj list represnt chars with numbers
// 3. make indegree array
// 4. do topological sort

// Edge cases
// 1. ex: aa,a (if there is no difference and larger string occur before smaller hence return "")
// 2. existence of loop (evident)
string findOrder(vector<string> &words) {
    unordered_map<int, vector<int>> adj;  // will store chars and there neighbours in form of int
    unordered_set<int> all_chars; // all unique charachters because indegree will need that
    bool false_flag = false; // directly check if there is edge case of type 1
    
    construct_adj(words, adj, all_chars, false_flag);
    if (false_flag) return "";
    
    string topo_sorted = topological_sort(adj, all_chars);
    return topo_sorted;
    
}
string topological_sort(unordered_map<int, vector<int>> &adj, unordered_set<int> &all_chars){
    unordered_map<int, int> indegree;
    queue<int> q;
    string topo = "";
    for(auto ch:all_chars){
        indegree[ch]=0;
    } 
    // all unique chars have 0 initalized
    for (auto node_pair : adj) {  
        int node = node_pair.first;  // sunce ad is <int,vector> 0->1,2,3 
        vector<int> neighbors = node_pair.second;  // since we have to increment neighbour of node because of directed edge from node to neighbour
        for (auto neighbor : neighbors) {
            indegree[neighbor]++;
        }
    }
    for(int ch:all_chars){
        if(indegree[ch]==0){
            q.push(ch);
        } // all chars whose indegree is 0
    }
    // normal khans algorithm
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo += (node + 'a');

        for (int neighbor : adj[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
     return (topo.size() == all_chars.size()) ? topo : "";

    
}
void construct_adj(vector<string> &words, unordered_map<int, vector<int>> &adj, unordered_set<int> &all_chars, bool &false_flag){
    for(string &word:words){
        for(char &ch:word){
            all_chars.insert(ch-'a');
        }
    }  // store all unique charachters

    for (int i = 0; i < words.size() - 1; i++) {
        string s1 = words[i];
        string s2 = words[i + 1];
        int min_length = min(s1.size(), s2.size());
        bool found_diff = false;
        for(int j=0;j<min_length;j++){
             if (s1[j] != s2[j]) {
                adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                found_diff = true;
                break; // Stop at first difference because you can not say the second differnce will also follow this rule
                    // ex: ["cb", "cba", "a", "bc"] in cb and bc  c will come first but if we dont break b will come before c which is wrong
            }
        }
        if(!found_diff && s1.size()>s2.size()){
            false_flag=true;
            return;
        }
    }
     
    
}