/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

    vector<string> ans;

    void DFS(TreeNode* root, string path){

        if(root == nullptr){ 
            return;
        }

        // Add value of root to ans

        path = path + to_string(root->val);

        // if lef node

        if(root->left == nullptr and root->right == nullptr){
            ans.push_back(path);
            return;
        }
        //else

        path = path + "->";

        //call dfs on left and right child
        DFS(root->left, path);
        DFS(root->right, path);
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        // vector<string>path;
        DFS(root, "");
        return ans;
    }
};