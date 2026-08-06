class Solution {
public:
    long long int productOfDigits(int a){
        long long int ans = 1;

        while(a){
            ans = ans * (a%10);
            a = a/10;
        }
        return ans;
    }

    int smallestNumber(int n, int t) {

        int i= n;

        while(productOfDigits(i)%t != 0){
            i++;
        }

        return i;
        
    }
};