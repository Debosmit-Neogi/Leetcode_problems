class Solution {
public:
    int maxNumberOfBalloons(string text) {

        vector<int>ballon_arr(26,0);

        ballon_arr['b'-'a'] = 1;
        ballon_arr['a'-'a'] = 1;
        ballon_arr['l'-'a'] = 2;
        ballon_arr['o'-'a'] = 1;
        ballon_arr['n'-'a'] = 1;

        vector<int>arr(26,0);

        for(int i=0; i<text.size(); i++){
            arr[text[i] - 'a']++;
        }

        if(arr['b'-'a'] >=1 && arr['a'-'a']>=1 && arr['l'-'a']>=2 && arr['o'-'a']>=2 && arr['n'-'a']>=1){

            return min({arr['b'-'a'], arr['a'-'a'], arr['l'-'a']/2, arr['o'-'a']/2, arr['n'-'a']});
        }

        else{
            return 0;
        }
        

    }
};