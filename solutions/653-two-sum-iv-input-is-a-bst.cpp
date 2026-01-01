class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> seen;
        return dfs(root, k, seen);
    }
    
private:
    bool dfs(TreeNode* node, int k, unordered_set<int>& seen) {
        if (!node) return false;
        if (seen.count(k - node->val)) return true;
        seen.insert(node->val);
        return dfs(node->left, k, seen) || dfs(node->right, k, seen);
    }
};
