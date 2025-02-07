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

void inorderhelp(TreeNode* root, vector<int>&sol){
    if(root==NULL) return;
    inorderhelp(root->left, sol);
    sol.push_back(root->val);
    inorderhelp(root->right, sol);
}
    vector<int> inorderTraversal(TreeNode* root) {

        vector<int>sol;
        inorderhelp(root, sol);
        return sol;
        
    }
};