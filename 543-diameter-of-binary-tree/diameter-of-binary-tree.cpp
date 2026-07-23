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

    // function to compute height of the binary tree
    int height(TreeNode* root){
        if(root == nullptr){
            return 0;
        }
        
        // calculate the left height of the bin tree

        int lheight = height(root->left);
        int rheight = height(root->right);

        int height = max(lheight, rheight) +1;

        return height;
    
    }

    int diameterOfBinaryTree(TreeNode* root) {

        if(root==nullptr){
            return 0;
        }

        // find height of the left subtree
        int lheight = height(root->left);

        // find height of the right subtree
        int rheight = height(root->right);

        // Get the diameter of left and right sub-trees
        int ldiameter = diameterOfBinaryTree(root->left);
        int rdiameter = diameterOfBinaryTree(root->right);

        // max depth: Max of (lheight + rheight), ldiameter, rdiameter

        return max({(lheight + rheight), ldiameter, rdiameter});
            
    }
};