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
    vector<int> rightSideView(TreeNode* root) {
        
        vector<int>ans; // vector to store answer

        if(root==nullptr){
            return ans;
        }

        queue<TreeNode*>q;

        q.push(root);

        while(!q.empty()){

            int q_len = q.size(); // no. of nodes in a level in queue

            vector<int>node_level; // vector to store node vals in a level

            for(int i=0; i<q_len; i++){
                TreeNode* node = q.front();

                //push the value of that node frm stack to vector

                node_level.push_back(node->val);
                q.pop();

                // visit and left and right child of root and push in queue

                if(node->left){
                    q.push(node->left);
                }

                if(node->right){
                    q.push(node->right);
                }

            }

            ans.push_back(node_level[q_len-1]);

        }

        return ans;
    }
};