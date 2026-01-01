# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isValidBST(self, root: 'Optional[TreeNode]') -> bool:
        
        def validate(node, low=-float('inf'), high=float('inf')):
            # Empty trees are valid BSTs
            if not node:
                return True
            
            # The current node's value must be within the range (low, high)
            if node.val <= low or node.val >= high:
                return False
            
            # The left subtree's values must be < node.val
            # The right subtree's values must be > node.val
            return (validate(node.left, low, node.val) and
                    validate(node.right, node.val, high))
        
        return validate(root)
