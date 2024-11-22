class Solution {
public:
    bool isPalindrome(int x) {
        if(x <0){
            return false;
        }
        long long int orig = x;
        long long int rev = 0;

        while(x>0){
            int digit = x%10;
            rev = rev*10 + digit;
            x = x/10;
        }

        if(rev == orig)
        return true;

        else
        return false;
        
    }
};