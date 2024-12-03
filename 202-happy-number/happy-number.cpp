class Solution {
public:
    int sq_sum(int n){
        int sum = 0;
        while(n>0){
            int digit = n%10;
            sum += digit*digit;
            n=n/10;

        }
        return sum;
    }
    bool isHappy(int n) {
        // vector<int>visited;
        unordered_set<int> visited;

        if(n==1 || n==10){
            return true;
        }

        // else if (n!=1 && n<10){
        //     return false;
        // }

        while(n!=1 && visited.find(n) == visited.end()){
            visited.insert(n);
            n = sq_sum(n);
        }
        // return n==1;

        if(n==1){
            return true;
        }

        else
        return false;
        
    }
};