class Solution {
public:
    int digit_sum(int n){
        int sum = 0;

        while(n){
            sum += n%10;
            n=n/10;
        }

        return sum;
    }

    long long int digit_product(int n){
        long long int prod = 1;

        while(n){
            prod *= n%10;
            n=n/10;
        }

        return prod;
    }
    bool checkDivisibility(int n) {

        if(n% (digit_sum(n) + digit_product(n)) == 0)
            return true;
        else
            return false;
        
    }
};