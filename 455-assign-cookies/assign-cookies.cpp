class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {

        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        
        int child_idx = 0;
        int cookie_idx = 0;
        int count = 0; // Track no. of children satisfied by cookie

        while(child_idx < g.size() && cookie_idx < s.size()){

            // cookie can satisfy a child
            if(s[cookie_idx] >= g[child_idx]){

                child_idx ++; // move to next child since this child is satisfied
                cookie_idx ++; // move to next cookie
                count++; 
            }

            // if cookie cannot satisfy the child

            else{
                cookie_idx ++; // move on to the next cookie but not the child 
            }
        }
        return count;
    }
};