class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {

        // Create vector to store frequency of all tasks

        vector<int> freq(26,0);

        for(char i: tasks){
            freq[i - 'A'] ++;
        } 

        // sort the frequency in descending order

        sort(freq.begin(), freq.end(), greater<int>());

        int maxFreq = freq[0]; // this is the max frequency of a task

        //count task with maximum frequency

        int maxFreqCount = 0;  //task with max frequency

        for(int f:freq){
            if(f == maxFreq){
                maxFreqCount ++;
            }

            else{
                break;
            }
        }

        //calculate minimum time needed (idle slots)

        int idleSlots = (maxFreq - 1) * (n + 1);

        // Answer = max(tasks.length, idleSlots + tasks with maxFreq)
        return max((int) tasks.size(), idleSlots + maxFreqCount);


        
    }
};