class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(board[i][j] == word[0] && dfs(board, word, i, j, 0) == true)
                return true;
            }
        }
        return false;
        
    }

    bool dfs(vector<vector<char>>& board, string word, int i, int j, int index){
        // index - > current index of word we're trying to match

        if(index == word.size()) // we have reached end of word 
            return true;
        
        // check boundary conditions
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index]) 
    return false;

    char temp = board[i][j]; // temporary mark visited cell with # so that we dont visit again
    board[i][j] = '#';
    // recursively apply dfs to check all neighbours
    bool found = dfs(board, word, i + 1, j, index + 1) ||  // Move Down
             dfs(board, word, i - 1, j, index + 1) ||  // Move Up
             dfs(board, word, i, j + 1, index + 1) ||  // Move Right
             dfs(board, word, i, j - 1, index + 1);    // Move Left

    // Backtracking
    board[i][j] = temp;
    return found;

    }


};