int getMaxArea(vector<int> &arr) {
    // Your code here
    // approach
    // find the first occurrence of min from left and right
    // maintain 2 arrays pse and nse
    vector<int> pse=PSE(arr); // this array will contain the nearest element which =is  is smaller than curernt element
    vector<int> nse=NSE(arr);  // this array will contain the nearest element which =is  is greater than curernt element
    int n=arr.size();
    int ans=INT_MIN;
    for(int i=0;i<n;i++){
        int left_ind=pse[i]; // find index of immidiate small on left
        int right_ind=nse[i]; // find index of immediate small on right
        if (left_ind == -1) left_ind = 0; // if no small found on left then range start from 0
        else left_ind += 1; 
        if (right_ind == -1) right_ind = n - 1; // if no small found on right then range start from n-1
        else right_ind -= 1;
        int width = right_ind - left_ind + 1;
        int area = arr[i] * width; // width of rectangle formed by ith element
        ans = max(ans, area);
    }
    return ans;
}
vector<int> PSE(vector<int> nums){
    stack<int> st;
    int n = nums.size();
    vector<int> ans;
    for (int i = 0; i <nums.size(); i++) {
        while (!st.empty() && nums[st.top()] >= nums[i]) {
            st.pop();
        }
        if (st.empty()) {
            ans.push_back(-1);
        } else {
            int elem = st.top();
            ans.push_back(elem);
        }
        st.push(i);
        
    }
    return ans;
}
vector<int> NSE(vector<int> nums){
    stack<int> st;
    int n = nums.size();
    vector<int> ans;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && nums[st.top()] >= nums[i]) {
            st.pop();
        }
        if (st.empty()) {
            ans.push_back(-1);
        } else {
            int elem = st.top();
            ans.push_back(elem);
        }
        st.push(i);
        
    }
    reverse(ans.begin(), ans.end());
    return ans;
}