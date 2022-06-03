/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
 *
 * https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
 *
 * algorithms
 * Medium (71.08%)
 * Likes:    1620
 * Dislikes: 0
 * Total Accepted:    366.1K
 * Total Submissions: 515K
 * Testcase Example:  '[3,9,20,15,7]\n[9,3,15,20,7]'
 *
 * 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历，
 * inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
 * 输出: [3,9,20,null,null,15,7]
 *
 *
 * 示例 2:
 *
 *
 * 输入: preorder = [-1], inorder = [-1]
 * 输出: [-1]
 *
 *
 *
 *
 * 提示:
 *
 *
 * 1 <= preorder.length <= 3000
 * inorder.length == preorder.length
 * -3000 <= preorder[i], inorder[i] <= 3000
 * preorder 和 inorder 均 无重复 元素
 * inorder 均出现在 preorder
 * preorder 保证 为二叉树的前序遍历序列
 * inorder 保证 为二叉树的中序遍历序列
 *
 *
 */

// @lc code=start
// g++ 011.Construct-Binary-Tree-from-Preorder-and-Inorder-Traversal.cpp -std=c++11
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
  unordered_map<int, int> map;

 public:
  // 先序是 [根结点, [左子树的先序], [右子树的先序]]
  // 中序是 [[左子树的中序], 根节点, [右子树的中序]]
  // 1.先找到根节点
  // 2.递归的找左子树和右子树的根节点
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    for (size_t i = 0; i < inorder.size(); i++) {
      map[inorder[i]] = i;
    }
    return recursive(preorder, inorder, 0, preorder.size() - 1, 0,
                     inorder.size() - 1);
  }

  TreeNode* recursive(vector<int>& preorder, vector<int>& inorder, int preLeft,
                      int preRight, int inLeft, int inRight) {
    //递归终止条件
    if (preLeft > preRight) return nullptr;
    int rootVal = preorder[preLeft];
    int rootInPos = map[rootVal];  //根节点在中序序列里的下标
    TreeNode* root = new TreeNode(rootVal);
    int leftTreeLength = rootInPos - inLeft;  //左子树长度
    root->left = recursive(preorder, inorder, preLeft + 1,
                           preLeft + leftTreeLength, inLeft, rootInPos - 1);
    root->right = recursive(preorder, inorder, preLeft + leftTreeLength + 1,
                            preRight, rootInPos + 1, inRight);
    return root;
  }
};

// 层序遍历
void levelOrder(TreeNode* root) {
  queue<TreeNode*> q;
  q.push(root);
  while (!q.empty()) {
    int len = q.size();
    for (int i = 0; i < len; i++) {
      TreeNode* node = q.front();
      cout << node->val << " ";
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
      q.pop();
    }
    cout << endl;
  }
}

int main() {
  vector<int> pre = {3, 9, 20, 15, 7};
  vector<int> in = {9, 3, 15, 20, 7};
  Solution s;
  TreeNode* root = s.buildTree(pre, in);
  levelOrder(root);
  return 0;
}
// @lc code=end

// 思考题
// 1. 为什么先序遍历加后序遍历无法构造出一颗二叉树?