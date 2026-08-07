// Brute force solution
class Solution {
public:

    long long int product_nums(int x){
        long long int ans = 1;

        while(x){
            ans = ans*(x%10);
            x = x/10;
        }

        return ans;
    }

    bool zero_free(int x){
        while(x){
            int digit = x%10;

            if(digit == 0){
                return false;
            }

            x = x/10;
        }
        return true;
    }
    string smallestNumber(string num, long long t) {

        long long int num_int = stoi(num);
        long long int ans = num_int;
        while (product_nums(ans) % t != 0 || !zero_free(ans)){
            ans = ans+1;
        }
        string ans_str = to_string(ans);
        return ans_str;
        
    }
};
